// gatsby-node.js

const path = require("path");
const fs = require("fs");
const fetch = require("node-fetch");
const cheerio = require("cheerio");
const { createFilePath } = require("gatsby-source-filesystem");
const archiveStructure = require("./static/archive-structure.json");

const fetchWithAbort = async (url, timeout = 10000) => {
  const controller = new AbortController();
  const timer = setTimeout(() => controller.abort(), timeout);

  try {
    const response = await fetch(url, { signal: controller.signal });
    clearTimeout(timer); // Clear the timeout if the request completes
    return response;
  } catch (error) {
    if (error.name === "AbortError") {
      throw new Error("Request timed out");
    }
    throw error;
  }
};

exports.onCreateWebpackConfig = ({ stage, loaders, actions }) => {
  actions.setWebpackConfig({
    resolve: {
      fallback: {
        path: require.resolve("path-browserify"),
        fs: false,
      },
    },
  });
};

exports.onCreateNode = ({ node, actions, getNode }) => {
  const { createNodeField } = actions;

  if (node.internal.type === "MarkdownRemark") {
    let value = createFilePath({ node, getNode });
    value = `/blog${value}`;
    createNodeField({
      name: "slug",
      node,
      value,
    });
  }
};

exports.createPages = async ({ graphql, actions }) => {
  const { createPage } = actions;

  const result = await graphql(`
    {
      allMarkdownRemark(sort: { fields: [frontmatter___date], order: DESC }) {
        edges {
          node {
            fields {
              slug
            }
            frontmatter {
              tags
              title
              date
            }
          }
          next {
            fields {
              slug
            }
            frontmatter {
              title
            }
          }
          previous {
            fields {
              slug
            }
            frontmatter {
              title
            }
          }
        }
      }
    }
  `);

  const data = await graphql(`
    query tagsQuery {
      allMarkdownRemark {
        edges {
          node {
            frontmatter {
              tags
            }
          }
        }
      }
    }
  `);

  if (result.errors) {
    throw result.errors;
  }

  const posts = result.data.allMarkdownRemark.edges;
  const postsPerPage = 4;
  const numPages = Math.ceil((posts.length - 3) / postsPerPage);

  posts.forEach((post, index) => {
    const previous = index === posts.length - 1 ? null : posts[index + 1].node;
    const next = index === 0 ? null : posts[index - 1].node;

    createPage({
      path: post.node.fields.slug,
      component: path.resolve("./src/templates/blogTemplate.js"),
      context: {
        slug: post.node.fields.slug,
        previous,
        next,
      },
    });
  });

  const tags = data.data.allMarkdownRemark.edges.reduce((allTags, edge) => {
    const tagsFromNode = edge.node.frontmatter.tags;
    if (tagsFromNode) {
      allTags = [...allTags, ...tagsFromNode];
    }
    return allTags;
  }, []);
  const uniqueTags = new Set(tags);

  uniqueTags.forEach((tag) => {
    const filteredPosts = posts.filter((edge) =>
      edge.node.frontmatter.tags.includes(tag)
    );
    const filteredNumPages = Math.ceil(filteredPosts.length / postsPerPage);

    Array.from({ length: filteredNumPages }).forEach((_, i) => {
      createPage({
        path: i === 0 ? `/blog/tags/${tag}` : `/blog/tags/${tag}/${i + 1}`,
        component: path.resolve("./src/templates/blogTagsListTemplate.js"),
        context: {
          limit: postsPerPage,
          skip: i * postsPerPage,
          numPages: filteredNumPages,
          currentPage: i + 1,
          tag: tag,
        },
      });
    });
  });

  createPage({
    path: `/blog`,
    component: path.resolve("./src/templates/blogListTemplate.js"),
    context: {
      limit: postsPerPage,
      skip: 0,
      numPages,
      currentPage: 1,
    },
  });

  Array.from({ length: numPages - 1 }).forEach((_, i) => {
    createPage({
      path: `/blog/${i + 2}`,
      component: path.resolve("./src/templates/blogListTemplate.js"),
      context: {
        limit: postsPerPage,
        skip: (i + 1) * postsPerPage,
        numPages,
        currentPage: i + 2,
      },
    });
  });

  const createPagesForDirectory = (directory, basePath) => {
    Object.keys(directory).forEach((dirName) => {
      const dirPath = `${basePath}/${dirName}`;
      createPage({
        path: dirPath,
        component: path.resolve("./src/pages/archive.js"),
        context: {
          directoryName: dirName,
          fullPath: dirPath,
        },
      });

      const subdirectories = directory[dirName];
      if (subdirectories && Object.keys(subdirectories).length > 0) {
        createPagesForDirectory(subdirectories, dirPath);
      }
    });
  };

  createPagesForDirectory(archiveStructure.root, "/archive");
};

exports.sourceNodes = async ({
  actions,
  createNodeId,
  createContentDigest,
}) => {
  const { createNode } = actions;

  const linksFilePath = path.resolve(__dirname, "static", "links.txt");

  if (!fs.existsSync(linksFilePath)) {
    console.error(
      "❌ Error: links.txt file not found in the static directory."
    );
    return;
  }

  const rawLines = fs.readFileSync(linksFilePath, "utf-8");
  const lines = rawLines
    .split("\n")
    .map((line) => line.trim())
    .filter((line) => line);

  const links = [];
  let currentLink = "";

  for (const line of lines) {
    if (line.startsWith("http")) {
      if (currentLink) {
        links.push(currentLink);
      }
      currentLink = line;
    } else {
      currentLink += line;
    }
  }

  if (currentLink) {
    links.push(currentLink);
  }

  console.log(`✅ Found ${links.length} links after reconstruction`);

  for (const linkLine of links) {
    const parts = linkLine.split(",").map((part) => part.trim());
    const url = parts[0];
    const image = parts[1] || ""; // If second part exists, it's the image URL

    try {
      const response = await fetchWithAbort(url, 10000); // Set to 60 seconds

      if (!response.ok) {
        throw new Error(`Failed to fetch ${url}: ${response.statusText}`);
      }

      const contentType = response.headers.get("content-type");
      if (!contentType || !contentType.includes("text/html")) {
        throw new Error(`Unsupported content type for ${url}: ${contentType}`);
      }

      const html = await response.text();
      const $ = cheerio.load(html);
      let title = $("title").text().trim();

      if (!title) {
        const urlParts = url.split("/");
        const lastPart =
          urlParts[urlParts.length - 1] || urlParts[urlParts.length - 2];
        if (lastPart) {
          const words = lastPart.split("-").map((word) => {
            if (word.length === 0) return word;
            return word.charAt(0).toUpperCase() + word.slice(1);
          });
          title = words.join(" ");
        } else {
          title = "No Title Available";
          console.warn(
            `⚠️ Warning: Unable to extract title from URL ${url}. Using fallback title.`
          );
        }
      }

      $("script, style").remove();

      let description =
        $('meta[name="description"]').attr("content") ||
        $('meta[property="og:description"]').attr("content") ||
        $('meta[name="twitter:description"]').attr("content") ||
        "";

      const mainContent = [
        $("article").text(),
        $("section").text(),
        $("div").text(),
        $("p").text(),
        $("body").text(),
      ]
        .join(" ")
        .replace(/\s+/g, " ")
        .trim();

      const matches = [...mainContent.matchAll(/(.{0,50}yohandi.{0,50})/gi)];

      if (matches.length > 0) {
        const lastMatch = matches[matches.length - 1];
        description = `...${lastMatch[0].trim()}...`;
      } else if (mainContent.length > 150) {
        description = mainContent.substring(0, 150).trim() + "...";
      }

      if (
        url.endsWith(
          "empat-siswa-indonesia-siap-berkompetisi-di-ajang-olimpiade-informatika-internasional-2023-2023-sma"
        )
      ) {
        description = `Indonesia," ujar Yohandi. "Semua adalah perjuangan kolektif, sebuah upaya tim untuk membawa kehormatan bagi Indonesia di panggung internasional. Kami siap untuk menghadapi IOI 2023, nantikan kabar baik dari kami," tambah Yohandi.`;
      }

      console.log(`\nURL: ${url}`);
      console.log(`Final Description: ${description}`);

      let finalImage = image;
      if (!finalImage) {
        finalImage =
          $('meta[property="og:image"]').attr("content") ||
          $('link[rel="icon"]').attr("href") ||
          $('link[rel="shortcut icon"]').attr("href") ||
          "";
        if (finalImage && !finalImage.startsWith("http")) {
          try {
            const urlObj = new URL(url);
            finalImage = new URL(finalImage, urlObj.origin).href;
          } catch (err) {
            console.error(
              `⚠️ Warning: Error resolving image URL for ${url}:`,
              err
            );
            finalImage = "";
          }
        }
      }

      const nodeContent = JSON.stringify({
        title,
        description,
        url,
        image: finalImage,
      });

      const nodeMeta = {
        id: createNodeId(`external-link-${url}`),
        parent: null,
        children: [],
        internal: {
          type: `ExternalLink`,
          mediaType: `text/html`,
          content: nodeContent,
          contentDigest: createContentDigest({
            title,
            description,
            url,
            image: finalImage,
          }),
        },
      };

      const node = Object.assign(
        {},
        { title, description, url, image: finalImage },
        nodeMeta
      );
      createNode(node);
      console.log(`✅ Created ExternalLink node for ${url}`);
    } catch (error) {
      console.error(`❌ Error processing ${url}: ${error.message}`);

      const urlParts = url.split("/");
      const lastPart =
        urlParts[urlParts.length - 1] || urlParts[urlParts.length - 2];
      let fallbackTitle = "No Title Available";
      if (lastPart) {
        const words = lastPart.split("-").map((word) => {
          if (word.length === 0) return word;
          return word.charAt(0).toUpperCase() + word.slice(1);
        });
        fallbackTitle = words.join(" ");
      }

      const nodeContent = JSON.stringify({
        title: fallbackTitle,
        description: "Description not available due to timeout.",
        url: url,
        image: "",
      });

      const nodeMeta = {
        id: createNodeId(`external-link-${url}`),
        parent: null,
        children: [],
        internal: {
          type: `ExternalLink`,
          mediaType: `text/html`,
          content: nodeContent,
          contentDigest: createContentDigest({
            title: fallbackTitle,
            description: "Description not available due to timeout.",
            url,
            image: "",
          }),
        },
      };

      const node = Object.assign(
        {},
        {
          title: fallbackTitle,
          description: "Description not available due to timeout.",
          url: url,
          image: "",
        },
        nodeMeta
      );
      createNode(node);
      console.log(
        `✅ Created ExternalLink node for ${url} with fallback due to timeout`
      );
    }
  }
};

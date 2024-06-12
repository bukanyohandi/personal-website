const path = require("path");
const { createFilePath } = require("gatsby-source-filesystem");
const archiveStructure = require("./static/archive-structure.json");

exports.onCreateWebpackConfig = ({ actions }) => {
  actions.setWebpackConfig({
    resolve: {
      fallback: {
        path: require.resolve("path-browserify"),
        fs: false, // Since 'fs' module is not needed in the browser, it can be set to false.
      },
    },
  });
};

exports.onCreateNode = ({ node, actions, getNode }) => {
  const { createNodeField } = actions;

  if (node.internal.type === "MarkdownRemark") {
    let value = createFilePath({ node, getNode });
    value = `/blog${value}`; // This ensures the slug starts with /blog
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

  // Create blog post pages.
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

  for (const tag of uniqueTags) {
    console.log(tag);

    const filteredPosts = posts.filter((edge) => {
      return edge.node.frontmatter.tags.includes(tag);
    });
    const filteredNumPages = Math.ceil(filteredPosts.length / postsPerPage);
    console.log(tag, filteredNumPages);

    // First page for each tag
    createPage({
      path: `/blog/tags/${tag}`,
      component: path.resolve("./src/templates/blogTagsListTemplate.js"),
      context: {
        limit: postsPerPage,
        skip: 0,
        numPages: filteredNumPages,
        currentPage: 1,
        tag: tag,
      },
    });

    // Create remaining paginated pages for each tag
    Array.from({ length: filteredNumPages - 1 }).forEach((_, i) => {
      createPage({
        path: `/blog/tags/${tag}/${i + 2}`,
        component: path.resolve("./src/templates/blogTagsListTemplate.js"),
        context: {
          limit: postsPerPage,
          skip: (i + 1) * postsPerPage,
          numPages: filteredNumPages,
          currentPage: i + 2,
          tag: tag,
        },
      });
    });
  }

  // Explicitly create the first page
  createPage({
    path: `/blog`,
    component: path.resolve("./src/templates/blogListTemplate.js"), // Make sure to move your blog.js to templates and rename appropriately
    context: {
      limit: postsPerPage,
      skip: 0,
      numPages,
      currentPage: 1,
    },
  });

  // Create remaining paginated pages
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

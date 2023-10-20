const path = require("path");
const { createFilePath } = require("gatsby-source-filesystem");

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
  const numPages = Math.ceil(posts.length / postsPerPage);

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

  posts.forEach((post, index) => {
    createPage({
      path: post.node.fields.slug,
      component: path.resolve("./src/templates/blogTemplate.js"),
      context: {
        slug: post.node.fields.slug,
      },
    });
  });
};

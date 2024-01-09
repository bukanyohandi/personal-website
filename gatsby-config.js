/**
 * Configure your Gatsby site with this file.
 *
 * See: https://www.gatsbyjs.com/docs/reference/config-files/gatsby-config/
 */

/**
 * @type {import('gatsby').GatsbyConfig}
 */

module.exports = {
  siteMetadata: {
    title: `Yohandi`,
    description: `A passionate student with a strong interest in algorithms and data structures.`,
    author: `Yohandi`,
    siteUrl: `https://www.yohandi.me`,
  },
  plugins: [
    {
      resolve: `gatsby-plugin-sitemap`,
      options: {},
    },
    `gatsby-plugin-remove-trailing-slashes`,
    `gatsby-plugin-sharp`,
    {
      resolve: `gatsby-transformer-remark`,
      options: {
        extensions: [".mdx", ".md"],
        gatsbyRemarkPlugins: [
          {
            resolve: `gatsby-remark-highlight-code`,
          },
        ],
      },
    },
    {
      resolve: `gatsby-transformer-remark`,
      options: {
        plugins: [
          {
            resolve: `gatsby-remark-prismjs`,
            options: {
              // Class prefix for <pre> tags containing syntax highlighting;
              // defaults to 'language-' (e.g. <pre class="language-js">).
              // If your site loads Prism into the browser at runtime,
              // (e.g. for use with libraries like react-live),
              // you may use this to prevent Prism from re-processing syntax.
              // This is an uncommon use-case though;
              // If you're unsure, it's best to use the default value.
              classPrefix: "language-",
              inlineCodeMarker: null,
              aliases: {},
              showLineNumbers: false,
              noInlineHighlight: false,
            },
          },
        ],
      },
    },
    {
      resolve: `gatsby-source-filesystem`,
      options: {
        name: `markdown-pages`,
        path: `${__dirname}/static/posts`,
      },
    },
    `gatsby-transformer-json`,
    {
      resolve: `gatsby-source-filesystem`,
      options: {
        path: `${__dirname}/static/projects`,
      },
    },
    "gatsby-plugin-web-font-loader",
    {
      resolve: "gatsby-plugin-web-font-loader",
      options: {
        google: {
          families: ["Merriweather"],
        },
      },
    },
    `gatsby-plugin-react-helmet`,
    `gatsby-plugin-styled-components`,
    {
      resolve: `gatsby-plugin-disqus`,
      options: {
        shortname: `yohandi`,
      },
    },
    {
      resolve: "gatsby-plugin-local-search",
      options: {
        name: "pages",
        engine: "flexsearch",
        engineOptions: {
          profile: "speed",
          tokenize: "forward",
        },
        query: `
      {
        allMarkdownRemark {
          nodes {
            id
            fields {
              slug
            }
            frontmatter {
              title
            }
            rawMarkdownBody
          }
        }
      }
    `,
        ref: "id",
        index: ["titleSearch", "bodySearch"],
        store: ["id", "path", "title", "body"],
        normalizer: ({ data }) =>
          data.allMarkdownRemark.nodes.map((node) => ({
            id: node.id,
            path: node.fields.slug,
            title: node.frontmatter.title,
            body: node.rawMarkdownBody,
            titleSearch: node.frontmatter.title.toLowerCase(),
            bodySearch: node.rawMarkdownBody.toLowerCase(),
          })),
      },
    },
  ],
};

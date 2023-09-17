import React from "react";
import { graphql, Link } from "gatsby";
import Layout from "../layouts"; // Assuming you have a layouts component

const BlogListTemplate = ({ data, pageContext }) => {
  const posts = data.allMarkdownRemark.edges;
  const { currentPage, numPages } = pageContext;
  const isFirst = currentPage === 1;
  const isLast = currentPage === numPages;
  const prevPage = currentPage - 1 === 1 ? "/blog" : `/blog/${currentPage - 1}`;
  const nextPage = `/blog/${currentPage + 1}`;

  return (
    <Layout>
      {posts.map(({ node }) => (
        <div key={node.id}>
          <h3>
            <Link to={node.fields.slug}>{node.frontmatter.title}</Link>
          </h3>
          <p>{node.excerpt}</p>
        </div>
      ))}
      <div>
        {!isFirst && (
          <Link to={prevPage} rel="prev">
            ← Previous Page
          </Link>
        )}
        {!isLast && (
          <Link to={nextPage} rel="next">
            Next Page →
          </Link>
        )}
      </div>
    </Layout>
  );
};

export default BlogListTemplate;

export const pageQuery = graphql`
  query blogListQuery($skip: Int!, $limit: Int!) {
    allMarkdownRemark(
      sort: { fields: [frontmatter___date], order: DESC }
      limit: $limit
      skip: $skip
    ) {
      edges {
        node {
          id
          excerpt(pruneLength: 250)
          fields {
            slug
          }
          frontmatter {
            date(formatString: "MMMM DD, YYYY")
            title
          }
        }
      }
    }
  }
`;

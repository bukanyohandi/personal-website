import React from "react";
import { Link, graphql } from "gatsby";
import Layout from "../layouts";
import Header from "../components/Header";

const BlogPage = ({ data }) => {
  return (
    <Layout>
      <h1>Blog</h1>
      {data.allMarkdownRemark.edges.map((post) => (
        <div key={post.node.id}>
          <h3>{post.node.frontmatter.title}</h3>
          <small>
            Posted by {post.node.frontmatter.author} on{" "}
            {post.node.frontmatter.date}
          </small>
          <br />
          <br />
          <Link to={"/blog" + post.node.fields.slug}>Read More</Link>
          <br />
          <br />
          <hr />
        </div>
      ))}
    </Layout>
  );
};

export default BlogPage;

export const pageQuery = graphql`
  query BlogIndexQuery {
    allMarkdownRemark {
      edges {
        node {
          id
          frontmatter {
            title
            date(formatString: "MMMM DD, YYYY")
            author
          }
          fields {
            slug
          }
          excerpt
        }
      }
    }
  }
`;

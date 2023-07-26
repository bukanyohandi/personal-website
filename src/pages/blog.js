import React from "react";
import { Link, graphql } from "gatsby";
import Layout from "../layouts";
import styled from "styled-components";

// Define your styled components
const Post = styled.div`
  margin-bottom: 2em;
`;

const PostTitle = styled.h3`
  font-family: "Roboto", sans-serif;
  color: #2c3e50;
`;

const PostMeta = styled.small`
  font-family: "Open Sans", sans-serif;
  color: #666;
`;

const ReadMore = styled(Link)`
  display: inline-block;
  font-family: "Open Sans", sans-serif;
  color: #3498db;
  text-decoration: none;
  border-bottom: 1px solid #3498db;
`;

const Divider = styled.hr`
  border: 0;
  height: 1px;
  background: #ccc;
  margin-bottom: 1.5em;
`;

const BlogPage = ({ data }) => {
  return (
    <Layout>
      {data.allMarkdownRemark.edges.map((post) => (
        <Post key={post.node.id}>
          <PostTitle>{post.node.frontmatter.title}</PostTitle>
          <PostMeta>
            Posted by {post.node.frontmatter.author} on{" "}
            {post.node.frontmatter.date}
          </PostMeta>
          <ReadMore to={"/blog" + post.node.fields.slug}>Read More</ReadMore>
          <Divider />
        </Post>
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

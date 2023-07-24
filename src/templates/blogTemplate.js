import React from "react";
import { graphql } from "gatsby";
import Layout from "../layouts";
import Header from "../components/Header";

const BlogTemplate = ({ data }) => {
  const post = data.markdownRemark;

  return (
    <Layout>
      <Header />
      <h1>{post.frontmatter.title}</h1>
      <h4>
        Posted by {post.frontmatter.author} on {post.frontmatter.date}
      </h4>
      <div dangerouslySetInnerHTML={{ __html: post.html }} />
    </Layout>
  );
};

export default BlogTemplate;

export const postQuery = graphql`
  query BlogPostBySlug($slug: String!) {
    markdownRemark(fields: { slug: { eq: $slug } }) {
      html
      frontmatter {
        title
        author
        date(formatString: "MMMM DD, YYYY")
      }
    }
  }
`;

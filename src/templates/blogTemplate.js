import React from "react";
import { graphql } from "gatsby";
import styled from "styled-components";
import Layout from "../layouts";
import { Helmet } from "react-helmet";
import ReactMarkdown from "react-markdown";
import { InlineMath, BlockMath } from "react-katex";
import "katex/dist/katex.min.css"; // Import KaTeX CSS
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { dark } from "react-syntax-highlighter/dist/esm/styles/prism";
import remarkMath from "remark-math";
import rehypeKatex from "rehype-katex";

const GlobalStyle = styled.div`
  background-color: #f9f9f9;
`;

const PostContainer = styled.div`
  display: grid;
  grid-template-columns: 1fr 300px;
  gap: 2rem;
  max-width: 1200px;
  margin: 0 auto;
  padding: 2rem;
  background-color: white;
`;

const PostTitle = styled.h1`
  font-size: 2.2rem; /* Slightly bigger font */
  font-weight: 700; /* Bold font weight */
  color: #2c3e50;
  margin-bottom: 0.6rem; /* A bit more space below the title */
  line-height: 1.2; /* Control the height of the line */
  letter-spacing: -0.5px; /* Slightly tighter letter spacing for better readability */
  font-family: "Merriweather", serif;
  text-transform: uppercase;
`;

const PostInfo = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 1.3rem; /* Slightly larger font for better readability */
  text-transform: uppercase;
  color: #666; /* Darker color for better contrast */
  margin-bottom: 1.5rem; /* Keep the same bottom margin */
  font-weight: 400; /* Normal font weight */
  letter-spacing: 0.5px; /* Slightly wider letter spacing */
`;

const PostContent = styled.div`
  font-family: "Roboto", sans-serif;
  font-size: 1.2em;
  line-height: 1.6em;
  color: #444;

  p {
    margin-bottom: 1em;
  }

  a {
    color: #007bff;
  }

  h1,
  h2,
  h3,
  h4,
  h5,
  h6 {
    margin: 1.5rem 0 1rem;
    color: #333;
  }

  .math {
    display: block;
    margin: 1em 0;
    font-size: 1.2em;
  }
`;

const TOCContainer = styled.div`
  font-family: "Roboto", sans-serif;
  font-size: 1.1em;
  line-height: 1.6em;
  color: #666;
  border-left: 1px solid #ccc;
  padding-left: 2rem;

  h4 {
    font-size: 1.2em;
    color: #333;
    margin-bottom: 0.5rem;
  }

  ul {
    list-style: none;
    padding-left: 0;
  }

  li {
    margin-bottom: 0.5rem;
  }

  ul {
    padding-left: 1rem;
    margin-top: 0.5rem;
  }

  a {
    color: inherit;
    text-decoration: none;
  }
`;

const renderers = {
  // This custom renderer handles how headings are rendered
  heading: (props) => {
    const { level, children } = props;
    const size = `h${level}`;
    const id = children[0].props.value.toLowerCase().replace(/\s/g, "-");
    return React.createElement(size, { id }, children);
  },

  // This custom renderer changes how images are rendered
  image: (props) => {
    return <img {...props} style={{ maxWidth: "100%" }} />;
  },

  // This custom renderer handles code blocks
  code: ({ language, value }) => {
    return (
      <SyntaxHighlighter style={dark} language={language} children={value} />
    );
  },

  // This custom renderer handles inline math
  inlineMath: ({ value }) => <InlineMath math={value} />,

  // This custom renderer handles math blocks
  math: ({ value }) => <BlockMath math={value} />,
};

const BlogTemplate = ({ data }) => {
  const post = data.markdownRemark;
  const inlineMathRegex = /\$(.*?)\$/g;
  const blockMathRegex = /\$\$(.*?)\$\$/gs;

  let insideParagraph = false;

  const renderers = {
    text: ({ value }) => {
      if (insideParagraph) {
        const inlineMath = value.split(inlineMathRegex).map((s, i, arr) => {
          if (i % 2 === 1) return <InlineMath key={i}>{s}</InlineMath>;
          return s;
        });
        return <>{inlineMath}</>;
      } else {
        return value;
      }
    },
    paragraph: ({ children }) => {
      insideParagraph = true;
      const newChildren = React.Children.toArray(children);
      insideParagraph = false;

      if (newChildren.length === 1 && typeof newChildren[0] === "string") {
        const match = newChildren[0].match(blockMathRegex);
        if (match) {
          const formula = match[0].slice(2, -2);
          return <BlockMath>{formula}</BlockMath>;
        }
      }
      return <p>{newChildren}</p>;
    },
  };

  return (
    <GlobalStyle>
      <Layout>
        <Helmet>
          <title>{post.frontmatter.title}</title>
          <meta
            name="description"
            content={`Yohandi - ${post.frontmatter.title}`}
          />
        </Helmet>
        <PostContainer>
          <div>
            <PostTitle>{post.frontmatter.title}</PostTitle>
            <PostInfo>{post.frontmatter.date}</PostInfo>
            <PostContent>
              <ReactMarkdown
                components={renderers}
                remarkPlugins={[remarkMath]}
                rehypePlugins={[rehypeKatex]}
                children={post.rawMarkdownBody}
              />
            </PostContent>
          </div>
          <TOCContainer>
            <h4>Table of Contents</h4>
            <div
              className="table-of-contents"
              dangerouslySetInnerHTML={{ __html: post.tableOfContents }}
            />
          </TOCContainer>
        </PostContainer>
      </Layout>
    </GlobalStyle>
  );
};

export default BlogTemplate;

export const postQuery = graphql`
  query BlogPostBySlug($slug: String!) {
    markdownRemark(fields: { slug: { eq: $slug } }) {
      rawMarkdownBody
      tableOfContents(absolute: false)
      frontmatter {
        title
        author
        date(formatString: "MMMM DD, YYYY")
      }
    }
  }
`;

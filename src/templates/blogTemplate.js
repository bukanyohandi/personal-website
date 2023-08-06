import React, { useEffect, useRef, useState } from "react";
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

const Post = styled.div`
  width: 850px;
`;

const PostTitle = styled.h1`
  font-size: 2.2rem; /* Slightly bigger font */
  font-weight: 100; /* Bold font weight */
  color: #2c3e50;
  margin-bottom: 1rem; /* A bit more space below the title */
  line-height: 1.2; /* Control the height of the line */
  letter-spacing: 0.5px; /* Slightly tighter letter spacing for better readability */
  font-family: "Merriweather", serif;
  text-transform: uppercase;
`;

const PostInfo = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 1.3rem; /* Slightly larger font for better readability */
  text-transform: uppercase;
  color: #666; /* Darker color for better contrast */
  margin-top: -0.5em;
  margin-bottom: 1.5rem; /* Keep the same bottom margin */
  font-weight: 400; /* Normal font weight */
  letter-spacing: 0.5px; /* Slightly wider letter spacing */
`;

const PostContent = styled.div`
  font-size: 1.2em;
  line-height: 1.6em;
  color: #444;

  p {
    font-family: "Open Sans", sans-serif; /* Similar to PostInfo */
    font-size: 1.2rem; /* Slightly smaller than h2 */
    margin-bottom: 1em;
    font-weight: 400; /* Normal font weight */
  }

  a {
    color: #007bff;
  }

  h1 {
    font-family: "Merriweather", serif;
    font-size: 2.2rem;
    font-weight: 100;
    color: #2c3e50;
    margin: 1.5rem 0 1rem;
    line-height: 1.2;
    letter-spacing: 0.5px;
    text-transform: uppercase;
  }

  h2 {
    font-size: 1.8rem; /* Gradually decreasing sizes */
  }

  h3 {
    font-size: 1.6rem;
  }

  h4 {
    font-size: 1.4rem;
  }

  h5 {
    font-size: 1.2rem; /* Similar to PostInfo */
  }

  h6 {
    font-size: 1.1rem;
  }

  h2,
  h3,
  h4,
  h5,
  h6 {
    font-family: "Open Sans", sans-serif;
    text-transform: uppercase;
    margin: 1.5rem 0 1rem;
    font-weight: 400;
    letter-spacing: 0.5px;
  }
`;

const TOCContainer = styled.div`
  font-family: "Roboto", sans-serif;
  font-size: 1.1em;
  line-height: 1.6em;
  color: #666;
  border-left: 1px solid #ccc;

  h4 {
    font-size: 1.2em;
    color: #333;
    margin-bottom: 0.5rem;
    text-align: center;
  }

  > ul > li {
    padding-left: 0rem;
  }

  ul {
    list-style: none;
    padding-left: 1.5rem;
  }

  li {
    margin-bottom: 0.2rem;
  }

  a {
    color: inherit;
    text-decoration: none;
  }
`;

const createTOCTree = (headings) => {
  const toc = [];
  let stack = [];

  headings.forEach((heading) => {
    const { level, id, value } = heading;
    const node = { value, id, level, children: [] };

    if (stack.length === 0) {
      toc.push(node);
    } else if (level > stack[stack.length - 1].level) {
      stack[stack.length - 1].children.push(node);
    } else {
      while (stack.length && stack[stack.length - 1].level >= level) {
        stack.pop();
      }
      stack.length
        ? stack[stack.length - 1].children.push(node)
        : toc.push(node);
    }

    stack.push(node);
  });

  return toc;
};

const renderTOC = (toc) => (
  <ul>
    {toc.map((item) => (
      <li key={item.id}>
        <a href={`#${item.id}`}>{item.value}</a>
        {item.children.length > 0 && renderTOC(item.children)}
      </li>
    ))}
  </ul>
);

const BlogTemplate = ({ data }) => {
  const post = data.markdownRemark;
  const [toc, setToc] = useState([]);
  const headingsRef = useRef([]);

  const textContent = (children) => {
    return children.reduce((acc, child) => {
      if (typeof child === "string") return acc + child;
      if (child.props && child.props.children)
        return acc + textContent(child.props.children);
      return acc;
    }, "");
  };

  const customHeadingRenderer = (props, level) => {
    const { children } = props;
    const size = `h${level}`;
    const value = textContent(children);
    const id = value.toLowerCase().replace(/\s/g, "-");
    headingsRef.current.push({ level, id, value });
    return React.createElement(size, { id }, children);
  };

  const renderers = {
    h1: (props) => customHeadingRenderer(props, 1),
    h2: (props) => customHeadingRenderer(props, 2),
    h3: (props) => customHeadingRenderer(props, 3),
    h3: (props) => customHeadingRenderer(props, 4),
    h3: (props) => customHeadingRenderer(props, 5),
    h3: (props) => customHeadingRenderer(props, 6),

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

  useEffect(() => {
    setToc(createTOCTree(headingsRef.current));
  }, [headingsRef.current]);

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
          <Post>
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
          </Post>
          <TOCContainer>
            <h4>Table of Contents</h4>
            {renderTOC(toc)}
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

import React, { useEffect, useRef, useState } from "react";
import { graphql } from "gatsby";
import styled from "styled-components";
import Layout from "../layouts";
import { Helmet } from "react-helmet";
import ReactMarkdown from "react-markdown";
import { InlineMath, BlockMath } from "react-katex";
import "katex/dist/katex.min.css"; // Import KaTeX CSS
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { prism } from "react-syntax-highlighter/dist/esm/styles/prism";
import remarkMath from "remark-math";
import rehypeKatex from "rehype-katex";
import gfm from "remark-gfm";
import { Disqus } from "gatsby-plugin-disqus";

const GlobalStyle = styled.div`
  background-color: #f9f9f9;
`;

const MOBILE_CONST = 0.85;

const PostContainer = styled.div`
  display: column;
  grid-template-columns: 1fr 300px;
  gap: 2rem;
  min-height: 150px;
  max-width: 650px;
  margin: 0 auto 0 auto;
  padding: 2rem;
  background-color: white;

  @media only screen and (max-width: 800px) {
    max-width: 500px;
    margin: 20px auto 0 auto;
    padding: 0.75rem;
  }
`;

const Post = styled.div`
  width: 100%;
`;

const PostTitle = styled.h1`
  font-size: 1.8rem; /* Slightly bigger font */
  font-weight: 100; /* Bold font weight */
  color: #2c3e50;
  margin-bottom: 0.8rem; /* A bit more space below the title */
  line-height: 1; /* Control the height of the line */
  letter-spacing: 0.4px; /* Slightly tighter letter spacing for better readability */
  font-family: "Merriweather", serif;
  text-transform: uppercase;

  @media only screen and (max-width: 800px) {
    font-size: ${1.8 * MOBILE_CONST}rem; /* Adjusted for mobile */
  }
`;

const PostInfo = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 1rem; /* Slightly larger font for better readability */
  text-transform: uppercase;
  color: #666; /* Darker color for better contrast */
  margin-top: -0.4em;
  margin-bottom: 1.2rem; /* Keep the same bottom margin */
  font-weight: 400; /* Normal font weight */
  letter-spacing: 0.4px; /* Slightly wider letter spacing */
`;

const PostContent = styled.div`
  font-size: 1em;
  line-height: 1.3em;
  color: #444;

  ul,
  li,
  p {
    font-family: "Open Sans", sans-serif; /* Similar to PostInfo */
    font-size: 1rem; /* Slightly smaller than h2 */
    margin-bottom: 0.24em;
    font-weight: 400; /* Normal font weight */
  }

  a {
    color: #157a94;
    text-decoration: none;

    &:hover {
      color: #106272;
    }
  }

  h1 {
    font-family: "Merriweather", serif;
    font-size: 1.76rem;
    font-weight: 100;
    color: #2c3e50;
    margin: 1.2rem 0 0.8rem;
    line-height: 1;
    letter-spacing: 0.4px;
    text-transform: uppercase;
  }

  h2 {
    font-size: 1.44rem;
  }

  h3 {
    font-size: 1.28rem;
  }

  h4 {
    font-size: 1.12rem;
  }

  h5 {
    font-size: 0.96rem;
  }

  h6 {
    font-size: 0.88rem;
  }

  h2,
  h3,
  h4,
  h5,
  h6 {
    font-family: "Open Sans", sans-serif;
    text-transform: uppercase;
    margin: 1.2rem 0 0.8rem;
    font-weight: 400;
    letter-spacing: 0.4px;
  }

  @media only screen and (max-width: 800px) {
    h1 {
      font-size: ${1.76 * MOBILE_CONST}rem;
    }

    h2 {
      font-size: ${1.44 * MOBILE_CONST}rem;
    }

    h3 {
      font-size: ${1.28 * MOBILE_CONST}rem;
    }

    h4 {
      font-size: ${1.12 * MOBILE_CONST}rem;
    }

    h5 {
      font-size: ${0.96 * MOBILE_CONST}rem;
    }

    h6 {
      font-size: ${0.88 * MOBILE_CONST}rem;
    }
  }
`;

const FigureCaption = styled.div`
  font-family: "Open Sans", sans-serif; /* Similar to PostInfo */
  font-size: 1rem; /* Slightly smaller than h2 */
  font-weight: 600; /* Normal font weight */
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
    text-align: center;
  }

  > ul > li {
    padding-left: 0rem;
  }

  ul {
    list-style: none;
    padding-left: 0.8rem;
  }

  li {
    margin-bottom: 1.2rem;
  }

  a {
    color: inherit;
    font-size: 0.9em;
    text-decoration: none;
    line-height: 1rem;
  }

  @media only screen and (max-width: 800px) {
    font-size: ${1.1 * MOBILE_CONST}em;

    h4 {
      font-size: ${1.2 * MOBILE_CONST}em;
    }

    a {
      font-size: ${0.9 * MOBILE_CONST}em;
    }
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
    h4: (props) => customHeadingRenderer(props, 4),
    h5: (props) => customHeadingRenderer(props, 5),
    h6: (props) => customHeadingRenderer(props, 6),

    // This custom renderer changes how images are rendered
    img: (props) => {
      return (
        <div style={{ textAlign: "center" }}>
          <img {...props} style={{ maxWidth: "100%" }} />
          <FigureCaption>{props.alt}</FigureCaption>
        </div>
      );
    },

    // This custom renderer handles code blocks
    code: ({ node, inline, className, children, ...props }) => {
      const match = /language-(\w+)/.exec(className || "");

      // Check for window object (may not be available during SSR or in certain environments)
      const windowWidth =
        typeof window !== "undefined" ? window.innerWidth : 1000; // 1000 as default width

      // Set maxWidth based on window width
      const maxWidthValue = windowWidth <= 800 ? "480px" : "630px";

      const codeBlockContainerStyle = {
        maxWidth: maxWidthValue,
        overflowX: "auto",
      };

      if (!inline && match) {
        return (
          <div style={codeBlockContainerStyle}>
            <SyntaxHighlighter style={prism} language={match[1]} {...props}>
              {String(children).replace(/\n$/, "")}
            </SyntaxHighlighter>
          </div>
        );
      } else {
        return (
          <code className={className} {...props}>
            {children}
          </code>
        );
      }
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
                remarkPlugins={[remarkMath, gfm]}
                rehypePlugins={[rehypeKatex]}
                children={post.rawMarkdownBody}
              />
            </PostContent>
          </Post>
          {/* <TOCContainer>
            <h4>Table of Contents</h4>
            {renderTOC(toc)}
          </TOCContainer> */}

          <div className="disqus-container">
            <Disqus
              config={{
                url: `https://yohandi.me/${post.frontmatter.path}`,
                identifier: post.id,
                title: post.frontmatter.title,
              }}
            />
          </div>
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

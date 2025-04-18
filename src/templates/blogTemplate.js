import React, { useEffect, useRef, useState } from "react";
import { graphql } from "gatsby";
import styled, { createGlobalStyle } from "styled-components";
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
import { THEME } from "../constants.js";
import PDFEmbed from "../components/PDFEmbed";
import "../styles/fonts.css";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faClipboard, faCheckCircle } from "@fortawesome/free-solid-svg-icons";

const Style = styled.div`
  background-color: ${THEME.PRIMARY};
`;

const GlobalStyle = createGlobalStyle`
  ::-webkit-scrollbar {
    width: 0 !important;
  }
  
  body {
    -ms-overflow-style: none;
  }
`;

const MOBILE_CONST = 0.85;

const Post = styled.div`
  width: 100%;
`;

const PostTitle = styled.h1`
  font-size: 1.8rem; /* Slightly bigger font */
  font-weight: 100; /* Bold font weight */
  color: #2c3e50;
  margin-top: 0rem;
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
  font-size: 1rem;
  text-transform: uppercase;
  color: #666;
  margin-top: -0.4em;
  margin-bottom: 1.2rem;
  font-weight: 400;
  letter-spacing: 0.4px;
`;

const PostContainer = styled.div`
  display: column;
  grid-template-columns: 1fr 300px;
  gap: 2rem;
  min-height: 150px;
  max-width: 650px;
  margin: 20px auto;
  padding: 2rem;
  background-color: white;

  @media only screen and (max-width: 800px) {
    max-width: 500px;
    margin: 20px auto 0 auto;
    padding: 0.75rem;
  }
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
    // font-weight: 100;
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

const TagLink = styled.a`
  margin-right: 10px;
  background-color: #ebedf0;
  padding: 5px 10px;
  border-radius: 15px;
  text-decoration: none;
  color: #333;
  font-family: "Open Sans", sans-serif;
  font-size: 0.9rem;
  transition: background-color 0.3s;

  &:hover {
    background-color: #d0d3d4;
  }
`;
const TagsWrapper = styled.div`
  display: flex;
  flex-wrap: wrap;
  gap: 5px; // space between tags
  margin-top: 1em; // space above the tag group
`;

const NavigationLink = styled.a`
  display: block;
  padding: 10px 15px;
  margin: 10px 0;
  font-size: 1.2rem;
  text-decoration: none;
  color: #157a94;
  font-family: "Open Sans", sans-serif;
  &:hover {
    color: #106272;
    text-decoration: underline;
  }
  &.previous {
    text-align: left;
  }
  &.next {
    text-align: right;
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

const copyToClipboard = (text) => {
  navigator.clipboard.writeText(text).then(() => {});
};

const CollapsibleCodeBlock = ({ language, children, ...props }) => {
  const [isCollapsed, setIsCollapsed] = useState(true);
  const fullCode = String(children).replace(/\n$/, "");
  const snippet = fullCode.split("\n").slice(0, 5).join("\n") + "\n...";

  const [icon, setIcon] = useState(faClipboard);

  const handleCopyClick = () => {
    copyToClipboard(fullCode);
    setIcon(faCheckCircle);

    setTimeout(() => {
      setIcon(faClipboard);
    }, 2000);
  };

  return (
    <div style={{ position: "relative" }}>
      <button
        onClick={handleCopyClick}
        style={{
          position: "absolute",
          top: 0,
          right: 0,
          zIndex: 10,
          backgroundColor: "transparent",
          border: "none",
          cursor: "pointer",
          padding: "5px 10px",
        }}
      >
        <FontAwesomeIcon
          icon={icon}
          style={{ fontSize: "18px", color: "#EB8686" }}
        />
      </button>
      <SyntaxHighlighter style={prism} language={language} {...props}>
        {isCollapsed ? snippet : fullCode}
      </SyntaxHighlighter>
      <div
        onClick={() => setIsCollapsed(!isCollapsed)}
        style={{
          position: "absolute",
          bottom: 0,
          left: 0,
          right: 0,
          height: "15px",
          background:
            "repeating-linear-gradient(-45deg, #E66868, #E66868 2%, #EB8686 2%, #EB8686 4%)",
          opacity: 0.2,
          cursor: "pointer",
        }}
      />
    </div>
  );
};

const BlogTemplate = ({ data, pageContext }) => {
  const { previous, next } = pageContext;

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

    a: (props) => {
      if (props.href && props.href.endsWith(".pdf")) {
        return <PDFEmbed src={props.href} width={"100%"} height={"600px"} />;
      }
      return <a {...props} />;
    },

    // This custom renderer changes how images are rendered
    img: (props) => {
      return (
        <div style={{ textAlign: "center" }}>
          <img {...props} style={{ maxWidth: "100%" }} />
          <FigureCaption>{props.alt}</FigureCaption>
        </div>
      );
    },

    code: ({ node, inline, className, children, ...props }) => {
      const match = /language-(\w+)/.exec(className || "");
      const isCollapsible = className?.includes("[collapsible]");

      if (!inline && match) {
        if (isCollapsible) {
          return (
            <CollapsibleCodeBlock language={match[1]} {...props}>
              {String(children).replace(/\n$/, "")}
            </CollapsibleCodeBlock>
          );
        } else {
          return (
            <SyntaxHighlighter style={prism} language={match[1]} {...props}>
              {String(children).replace(/\n$/, "")}
            </SyntaxHighlighter>
          );
        }
      } else if (inline) {
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

  const formatAuthors = (authors) => {
    return authors
      .split(",")
      .map((author) =>
        author.trim().toLowerCase() === "yohandi"
          ? `<strong>${author.trim()}</strong>`
          : author.trim()
      )
      .join(", ");
  };

  return (
    <>
      <Style />
      <GlobalStyle />
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
            <PostInfo
              dangerouslySetInnerHTML={{
                __html: `${post.frontmatter.date} by ${formatAuthors(
                  post.frontmatter.author
                )}`,
              }}
            />
            <TagsWrapper>
              {post.frontmatter.tags.map((tag) => (
                <TagLink href={`/blog/tags/${tag}`} key={tag}>
                  {tag}
                </TagLink>
              ))}
            </TagsWrapper>
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

          {previous && (
            <NavigationLink href={previous.fields.slug} className="previous">
              ← {previous.frontmatter.title}
            </NavigationLink>
          )}
          {next && (
            <NavigationLink href={next.fields.slug} className="next">
              {next.frontmatter.title} →
            </NavigationLink>
          )}
        </PostContainer>
      </Layout>
    </>
  );
};

export default BlogTemplate;

export const postQuery = graphql`
  query BlogPostBySlug(
    $slug: String!
    $previousPostId: String
    $nextPostId: String
  ) {
    markdownRemark(fields: { slug: { eq: $slug } }) {
      rawMarkdownBody
      tableOfContents(absolute: false)
      frontmatter {
        title
        author
        date(formatString: "MMMM DD, YYYY")
        tags
      }
    }
    previous: markdownRemark(id: { eq: $previousPostId }) {
      fields {
        slug
      }
      frontmatter {
        title
      }
    }
    next: markdownRemark(id: { eq: $nextPostId }) {
      fields {
        slug
      }
      frontmatter {
        title
      }
    }
  }
`;

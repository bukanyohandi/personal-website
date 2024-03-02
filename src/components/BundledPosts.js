import React, { useState } from "react";
import { Link, useStaticQuery, graphql } from "gatsby";
import styled from "styled-components";
import { THEME } from "../constants.js";

const EDIT_MODE = false;

const MOBILE_CONST = 0.85;

const Card = styled.div`
  border: ${EDIT_MODE ? "1px solid" : "none"};
`;

// Various styled components for posts
const Post = styled.div`
  background-color: white;
  border-radius: 5px;
  padding: 20px;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
  text-decoration: none;
  border: ${EDIT_MODE ? "1px solid" : "none"};
`;
const PostLink = styled(Link)`
  text-decoration: none;
  color: inherit;
`;
const PostTitle = styled.h3`
  font-family: "Merriweather", serif;
  text-transform: uppercase;
  font-size: 1.52em;
  color: #2c3e50;
  margin-bottom: 0.5em;
  margin-top: 0.3em;
  font-weight: 100;

  @media only screen and (max-width: 800px) {
    font-size: ${1.52 * MOBILE_CONST}em;
    margin-top: 0.3em;
  }
`;
const PostMeta = styled.small`
  font-family: "Open Sans", sans-serif;
  color: #666;
  text-transform: uppercase;
  font-size: 1em;
  display: block;
  margin-top: -0.5em;
  margin-bottom: 1em;

  @media only screen and (max-width: 800px) {
    font-size: ${1 * MOBILE_CONST}em;
  }
`;
const PostExcerpt = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 1.05em;
  color: #333;
  margin-bottom: 0.3em;

  @media only screen and (max-width: 800px) {
    font-size: ${1.05 * MOBILE_CONST}em;
    margin-bottom: 0.3em;
  }
`;
const PostTags = styled.div`
  display: flex;
  flex-wrap: wrap;
  font-family: "Open Sans", sans-serif;
  font-size: 0.9em;
  color: #777;
  margin-top: 1em;

  span {
    margin-right: 10px;
    background-color: #ebedf0;
    padding: 5px 10px;
    border-radius: 15px;
  }

  @media only screen and (max-width: 800px) {
    font-size: ${0.9 * MOBILE_CONST}em;
    margin-top: 0.8em;
  }
`;

const PostTagLink = styled(Link)`
  margin-top: 5px;
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

  @media only screen and (max-width: 800px) {
    margin-top: 0.8em;
  }
`;

const NavigationButton = styled.button`
  cursor: pointer;
  border: none;
  background-color: #ebedf0;
  padding: 10px 15px;
  margin: 5px;
  border-radius: 5px;
  font-size: 16px; /* Adjust size as needed */
  &:hover {
    background-color: #d0d3d4;
  }
  &:focus {
    outline: none;
  }
  display: flex;
  align-items: center;
  justify-content: center;
`;

const BundledPostsIndicator = styled.div`
  position: absolute;
  top: 0;
  right: 0;
  width: 0;
  height: 0;
  border-left: 20px solid transparent;
  border-bottom: 20px solid ${THEME.PRIMARY};
  content: "";
  display: inline-block;
`;

const BundledPostsContainer = styled.div`
  margin: 2em 0;
  padding: 15px;
  background-color: #f8f9fa;
  border-radius: 8px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); /* Soft shadow for depth */
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: space-between; /* Adjust content spacing */
  min-height: 400px; /* Fixed height; adjust as necessary */
  overflow: hidden; /* Hide overflow */
`;

const NavigationButtonsContainer = styled.div`
  display: flex;
  justify-content: space-between;
  margin-top: 20px; /* Adjust spacing as needed */
`;

const BundleTitle = styled.h2`
  margin: 0;
  font-size: 1.6em;
  font-weight: 100;
  color: #333;
  font-family: "Merriweather", serif;
  text-align: center;
  text-transform: uppercase;
`;

const TagContainer = styled.div`
  display: flex;
  flex-wrap: wrap;
  margin-top: 1em;
`;

const TriangleButton = styled.button`
  cursor: pointer;
  background-color: transparent;
  border: none;
  font-size: 20px;
  color: #d0d3d4; /* Default color changed to the hover color */
  &:hover {
    color: #333; /* Hover color changed to the default color */
  }
  &:focus {
    outline: none;
  }

  &.prev {
    margin-right: 10px;
    &:before {
      content: "◀"; /* Left-pointing triangle */
    }
  }

  &.next {
    margin-left: 10px;
    &:before {
      content: "▶"; /* Right-pointing triangle */
    }
  }
`;

const NavigationCircles = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
`;

const Circle = styled.div`
  width: 10px;
  height: 10px;
  border-radius: 50%;
  background-color: #bbb;
  margin: 0 5px;
  transition: transform 0.3s ease;

  &.active {
    transform: scale(1.5); /* Make the active circle larger */
    background-color: #333; /* Highlight color for active circle */
  }
`;

const BundledPosts = ({ bundleKey }) => {
  const [activePostIndex, setActivePostIndex] = useState(0);

  const data = useStaticQuery(graphql`
    query BundledPostsQuery {
      allMarkdownRemark(
        filter: { frontmatter: { type: { eq: "bundle" } } }
        sort: { fields: [frontmatter___date], order: DESC }
      ) {
        edges {
          node {
            id
            frontmatter {
              title
              date(formatString: "MMMM DD, YYYY")
              author
              tags
              type
            }
            fields {
              slug
            }
            excerpt(pruneLength: 200)
          }
        }
      }
    }
  `);

  let bundledPostsSlugs = [];
  let bundleTitle = "";

  if (
    bundleKey ==
    "/blog/natural-parallelism-advancing-machine-learning-with-openacc/"
  ) {
    bundledPostsSlugs = [
      "/blog/natural-parallelism-advancing-machine-learning-with-openacc/",
      "/blog/natural-parallelism-disclosing-efficient-techniques-for-image-processing/",
      "/blog/natural-parallelism-in-distributed-and-parallel-sorting-algorithms/",
      "/blog/natural-parallelism-the-paradigm-of-refined-matrix-multiplication/",
    ];
    bundleTitle = "Parallel Programming";
  }

  const bundledPosts = data.allMarkdownRemark.edges.filter((edge) =>
    bundledPostsSlugs.includes(edge.node.fields.slug)
  );

  console.log(bundledPosts);

  const handleNext = () => {
    setActivePostIndex((prevIndex) => (prevIndex + 1) % bundledPosts.length);
  };

  const handlePrev = () => {
    setActivePostIndex(
      (prevIndex) => (prevIndex - 1 + bundledPosts.length) % bundledPosts.length
    );
  };

  const renderNavigationCircles = () => (
    <NavigationCircles>
      {bundledPosts.map((_, index) => (
        <Circle
          key={index}
          className={activePostIndex === index ? "active" : ""}
          onClick={() => setActivePostIndex(index)}
        />
      ))}
    </NavigationCircles>
  );

  return (
    <BundledPostsContainer>
      {bundledPosts.length > 0 && (
        <>
          <BundleTitle>{bundleTitle}</BundleTitle>
          <Card>
            <PostLink to={bundledPosts[activePostIndex].node.fields.slug}>
              <Post>
                <PostLink to={bundledPosts[activePostIndex].node.fields.slug}>
                  <PostTitle>
                    {bundledPosts[activePostIndex].node.frontmatter.title}
                  </PostTitle>
                </PostLink>
                <PostMeta>{`${bundledPosts[activePostIndex].node.frontmatter.date}`}</PostMeta>
                <PostExcerpt>
                  {bundledPosts[activePostIndex].node.excerpt}
                </PostExcerpt>
                <TagContainer>
                  {bundledPosts[activePostIndex].node.frontmatter.tags.map(
                    (tag, index) => (
                      <PostTagLink
                        key={index}
                        to={`tags/${tag.toLowerCase().replace(/ /g, "_")}`}
                      >
                        {tag}
                      </PostTagLink>
                    )
                  )}
                </TagContainer>
              </Post>
            </PostLink>
          </Card>
          <NavigationButtonsContainer>
            <TriangleButton className="prev" onClick={handlePrev} />
            {renderNavigationCircles()}
            <TriangleButton className="next" onClick={handleNext} />
          </NavigationButtonsContainer>
        </>
      )}
    </BundledPostsContainer>
  );
};

export default BundledPosts;

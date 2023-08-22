import React, { useState, useRef } from "react";
import { Link, graphql } from "gatsby";
import Layout from "../layouts";
import styled from "styled-components";
import { Helmet } from "react-helmet";

const EDIT_MODE = false;

const monthNames = [
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December",
];

function getMonthName(monthIndex) {
  return monthNames[monthIndex];
}

function getMax(contributions) {
  let max = -Infinity;
  Object.values(contributions).forEach((yearContributions) => {
    const yearMax = Math.max(...yearContributions);
    if (yearMax > max) {
      max = yearMax;
    }
  });
  if (max === 1) {
    max += 0.25;
  }
  return max;
}

const MOBILE_CONST = 0.85;

const Container = styled.div`
  width: 90%;
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  justify-content: center;
  background-color: #eef2f7;
  padding: 0 0;
  margin: 20px auto;
  max-width: 950px;
  border: ${EDIT_MODE ? "1px solid" : "none"};

  @media only screen and (max-width: 800px) {
    width: 100%;
    max-width: 450px;
  }
`;

const LeftContainer = styled.div`
  display: inline-block;
  float: left;
  width: 60%;
  padding: 20px;
  box-sizing: border-box;
  border: ${EDIT_MODE ? "1px solid" : "none"};

  @media only screen and (max-width: 800px) {
    width: 100%;
    padding: 10px;
  }
`;

const RightContainer = styled.div`
  display: inline-block;
  float: right;
  width: 40%;
  padding: 20px;
  box-sizing: border-box;
  border: ${EDIT_MODE ? "1px solid" : "none"};

  @media only screen and (max-width: 800px) {
    width: 100%;
    padding: 10px;
  }
`;

const Card = styled.div`
  border: ${EDIT_MODE ? "1px solid" : "none"};
`;

// Various styled components for posts
const Post = styled.div`
  background-color: white;
  border-radius: 5px;
  padding: 20px;
  margin-bottom: 2em;
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

// Styled components for contributions card and tooltip
const ContributionsCard = styled.div`
  position: relative;
  max-width: 800px;
  display: grid;
  grid-template-columns: repeat(12, 1fr); // Grid of 12 columns for each month
  grid-gap: 4px;
  padding: 10px;
  background-color: #fff;
  border-radius: 5px;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
`;
const Month = styled.div`
  width: 100%;
  padding-bottom: 100%; // This keeps the month squares aspect ratio 1:1
  border-radius: 2px;
  background-color: #ebedf0; // The default color of day squares
`;
const Tooltip = styled.div`
  position: fixed;
  background-color: #2c3e50;
  color: #fff;
  padding: 10px;
  border-radius: 5px;
  font-size: 12px;
  display: ${(props) => (props.show ? "block" : "none")};
  left: ${(props) => props.left || "0"}px;
  top: ${(props) => props.top || "0"}px;
  transform: translate(-50%, -150%); // Adjust the tooltip position
  transition: all 0.3s ease-in-out;
  white-space: nowrap;
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);

  &::after {
    content: "";
    position: absolute;
    top: 100%; // Arrow will appear at the bottom of tooltip
    left: 50%;
    margin-left: -5px;
    border-width: 5px;
    border-style: solid;
    border-color: #2c3e50 transparent transparent transparent;
  }
`;

const TagsContainer = styled.div`
  border: ${EDIT_MODE ? "1px solid" : "none"};
  margin-top: 20px;
  display: flex;
  flex-wrap: wrap;
  gap: 5px;
`;
const TagsCard = styled.div`
  border: ${EDIT_MODE ? "1px solid" : "none"};
  background-color: #fff;
  border-radius: 5px;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
  padding: 15px;
  margin-top: 20px;
`;
const TagsTitle = styled.h3`
  font-family: "Merriweather", serif;
  text-transform: uppercase;
  text-align: center;
  font-size: 1.8em;
  color: #2c3e50;
  margin-top: 0;
  margin-bottom: 15px;
  border-bottom: 1px solid #ddd;
  padding-bottom: 10px;
`;
const TagLink = styled(Link)`
  margin-right: 10px;
  background-color: #ebedf0;
  padding: 5px 10px;
  border-radius: 15px;
  text-decoration: none;
  color: #333;
  transition: background-color 0.3s;
  display: inline;

  &:hover {
    background-color: #d0d3d4;
  }

  @media only screen and (max-width: 800px) {
    margin-top: 0.8em;
  }
`;

const BlogPage = ({ data }) => {
  // Initialize a structure to store post counts per month per year
  const contributions = {
    2023: new Array(12).fill(0),
    2024: new Array(12).fill(0),
    2025: new Array(12).fill(0),
  };

  // Extract all post dates
  const postDates = data.allMarkdownRemark.edges.map(
    (edge) => edge.node.frontmatter.date
  );

  // Process post dates
  postDates.forEach((date) => {
    const dateObj = new Date(date);
    const year = dateObj.getFullYear();
    const month = dateObj.getMonth(); // getMonth() returns the month (0-11)

    if (contributions[year]) {
      contributions[year][month]++;
    }
  });

  // Calculate the max number of contributions for scaling
  const maxContributions = getMax(contributions);

  // Extract all tags and create a unique set
  const allTags = data.allMarkdownRemark.edges
    .map((edge) => edge.node.frontmatter.tags)
    .flat();
  const uniqueTagsSet = new Set(allTags);
  const uniqueTags = [...uniqueTagsSet].sort(); // Convert Set to Array and sort alphabetically

  const [tooltipInfo, setTooltipInfo] = useState({
    show: false,
    text: "",
  });

  return (
    <Layout>
      <Helmet>
        <title>Blog - Yohandi</title>
      </Helmet>
      <Container>
        <LeftContainer>
          <Card>
            {data.allMarkdownRemark.edges.map((post) => (
              <PostLink
                key={post.node.id}
                to={post.node.fields.slug.replace(/\/$/, "")}
              >
                <Post>
                  <PostTitle>{post.node.frontmatter.title}</PostTitle>
                  <PostMeta>{post.node.frontmatter.date}</PostMeta>
                  <PostExcerpt>{post.node.excerpt}</PostExcerpt>
                  <PostTags>
                    {post.node.frontmatter.tags.map((tag) => (
                      <PostTagLink
                        key={tag}
                        to={`tags/${tag.toLowerCase().replace(/ /g, "_")}`}
                      >
                        {tag}
                      </PostTagLink>
                    ))}
                  </PostTags>
                </Post>
              </PostLink>
            ))}
          </Card>
        </LeftContainer>
        <RightContainer>
          <Card>
            <ContributionsCard>
              {Object.entries(contributions).map(
                ([year, contributionsForYear]) =>
                  contributionsForYear.map((postCount, i) => (
                    <Month
                      key={i}
                      style={{
                        backgroundColor:
                          postCount > 0
                            ? `rgba(25, 97, 39, ${
                                (1 + Math.log(postCount)) /
                                (1 + Math.log(maxContributions))
                              })`
                            : "#ebedf0",
                      }}
                      onMouseEnter={(e) => {
                        const rect = e.target.getBoundingClientRect();
                        setTooltipInfo({
                          show: true,
                          text: `${postCount} post${
                            postCount === 0 || postCount === 1 ? "" : "s"
                          } in ${getMonthName(i)} ${year}`,
                          top: rect.top,
                          left: rect.left + rect.width / 2,
                        });
                      }}
                      onMouseLeave={() => {
                        setTooltipInfo({ ...tooltipInfo, show: false });
                      }}
                    />
                  ))
              )}
              <Tooltip
                style={{
                  top: tooltipInfo.top + "px",
                  left: tooltipInfo.left + "px",
                }}
                show={tooltipInfo.show}
              >
                {tooltipInfo.text}
              </Tooltip>
            </ContributionsCard>
          </Card>
          <TagsCard>
            <TagsTitle>Tags</TagsTitle>
            <TagsContainer>
              {uniqueTags.map((tag) => (
                <TagLink
                  key={tag}
                  to={`tags/${tag.toLowerCase().replace(/ /g, "_")}`}
                >
                  {tag}
                </TagLink>
              ))}
            </TagsContainer>
          </TagsCard>
        </RightContainer>
      </Container>
    </Layout>
  );
};

export default BlogPage;

export const pageQuery = graphql`
  query BlogIndexQuery {
    allMarkdownRemark(sort: { fields: [frontmatter___date], order: DESC }) {
      edges {
        node {
          id
          frontmatter {
            title
            date(formatString: "MMMM DD, YYYY")
            author
            tags
          }
          fields {
            slug
          }
          excerpt(pruneLength: 200)
        }
      }
    }
  }
`;

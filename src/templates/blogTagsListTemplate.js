import React, { useState, useRef } from "react";
import { Link, graphql } from "gatsby";
import Layout from "../layouts";
import styled from "styled-components";
import { Helmet } from "react-helmet";
import { ContributionsComponent } from "../components/ContributionsCard.js";
import TagsComponent from "../components/TagsCard.js";

const EDIT_MODE = false;

const MOBILE_CONST = 0.85;

const Container = styled.div`
  width: 90%;
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  justify-content: center;
  background-color: #eef2f7;
  padding: 0 0;
  margin: 25px auto 0 auto;
  max-width: 950px;
  border: ${EDIT_MODE ? "1px solid" : "none"};

  @media only screen and (max-width: 800px) {
    width: 100%;
    max-width: 450px;
  }
`;

const ButtonContainer = styled.div`
  display: flex;
  justify-content: center;
  align-items: center;
  height: 50px;
  width: 100%;
  border: ${EDIT_MODE ? "1px solid" : "none"};
`;

const PageButton = styled(Link)`
  margin: 0 5px;
  padding: 10px 16px;
  font-family: "Merriweather", serif;
  font-size: 1.2em;
  text-decoration: none;
  color: #333;
  background-color: #fff;
  border: 2px solid #ddd;
  border-radius: 5px;
  font-weight: bold; /* Make text bold for better visibility */
  transition: background-color 0.3s;
  cursor: pointer;

  &:hover {
    background-color: #f6f6f6;
  }

  &.disabled {
    pointer-events: none;
    background-color: #ccc;
    color: #666;
  }
`;

const renderPageButtons = (currentPage, numPages, tag) => {
  const buttons = [];
  for (let i = 1; i <= numPages; i++) {
    buttons.push(
      <PageButton
        key={i}
        to={i === 1 ? `/blog/tags/${tag}` : `/blog/tags/${tag}/${i}`}
        className={i === currentPage ? "disabled" : ""} // Add the "disabled" class conditionally
      >
        {i}
      </PageButton>
    );
  }
  return buttons;
};

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
  // background-color: #f9f9f9;

  @media only screen and (max-width: 800px) {
    width: 100%;
    padding: 10px;
    margin: 0 0 25px 0;
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

const ResultsHeading = styled.div`
  font-family: "Merriweather", serif;
  text-align: center;
  font-size: 1em;
  color: #2c3e50;
  width: 100%;
  text-align: center;
  padding: 10px;
  background-color: #eef2f7;
  margin: 5px;
`;

const BlogPage = ({ data, pageContext }) => {
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

  const { currentPage, numPages, tag } = pageContext;

  return (
    <Layout>
      <Helmet>
        <title>Blog - Yohandi</title>
      </Helmet>
      <Container>
        <ResultsHeading>Showing all posts with a tag: {tag}</ResultsHeading>
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
                        to={`/blog/tags/${tag
                          .toLowerCase()
                          .replace(/ /g, "_")}`}
                      >
                        {tag}
                      </PostTagLink>
                    ))}
                  </PostTags>
                </Post>
              </PostLink>
            ))}
          </Card>
          <ButtonContainer>
            {renderPageButtons(currentPage, numPages, tag)}
          </ButtonContainer>
        </LeftContainer>
        <RightContainer>
          <Card>
            <ContributionsComponent />
          </Card>
          <TagsComponent />
        </RightContainer>
      </Container>
    </Layout>
  );
};

export default BlogPage;

export const pageQuery = graphql`
  query blogPageQuery($skip: Int, $limit: Int, $tag: String) {
    allMarkdownRemark(
      sort: [{ frontmatter: { date: DESC } }]
      limit: $limit
      skip: $skip
      filter: { frontmatter: { tags: { in: [$tag] } } }
    ) {
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

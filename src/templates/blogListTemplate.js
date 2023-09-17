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
  justify-content: space-between; // This will push children to the opposite sides
  align-items: center;
  height: 50px;
  width: 100%;
  margin: -35px 0 0 0;
  padding: 0 10px; // adding horizontal padding
  border: ${EDIT_MODE ? "1px solid" : "none"};
`;

const PaginationLink = styled(Link)`
  margin: 25px 0;
  padding: 10px 20px;
  text-decoration: none;
  color: #333;
  border: 1px solid #ddd;
  border-radius: 5px;
  transition: background-color 0.3s;

  &:hover {
    background-color: #f6f6f6;
  }

  &[rel="prev"] {
    float: left;
  }

  &[rel="next"] {
    float: right;
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

  const { currentPage, numPages } = pageContext;
  const isFirst = currentPage === 1;
  const isLast = currentPage === numPages;
  const prevPage = currentPage - 1 === 1 ? "/blog" : `/blog/${currentPage - 1}`;
  const nextPage = `/blog/${currentPage + 1}`;

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
            <ContributionsComponent />
          </Card>
          <TagsComponent />
        </RightContainer>
        <ButtonContainer>
          {!isFirst && (
            <PaginationLink to={prevPage} rel="prev">
              ← Previous Page
            </PaginationLink>
          )}
          {!isLast && (
            <PaginationLink to={nextPage} rel="next">
              Next Page →
            </PaginationLink>
          )}
        </ButtonContainer>
      </Container>
    </Layout>
  );
};

export default BlogPage;

export const pageQuery = graphql`
  query blogPageQuery($skip: Int, $limit: Int) {
    allMarkdownRemark(
      sort: [{ frontmatter: { date: DESC } }]
      limit: $limit
      skip: $skip
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

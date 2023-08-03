import React from "react";
import { Link, graphql } from "gatsby";
import Layout from "../layouts";
import styled from "styled-components";
import { Helmet } from "react-helmet";
import { useState } from "react";
import { usePopper } from "react-popper";

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
  return max;
}

// define styled components
const Container = styled.div`
  display: flex;
  justify-content: center;
  background-color: #f9f9f9;
  padding: 20px 0;
`;

const Card = styled.div`
  margin: 20px;
  width: ${typeof window !== "undefined"
    ? `${window.screen.width * 0.4}px`
    : "40%"};
`;

const Post = styled.div`
  background-color: white;
  border-radius: 5px;
  padding: 20px;
  margin-bottom: 2em;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
  text-decoration: none;
`;

const PostLink = styled(Link)`
  text-decoration: none;
  color: inherit;
`;

const PostTitle = styled.h3`
  font-family: "Merriweather", serif;
  text-transform: uppercase;
  font-size: 1.6em;
  color: #2c3e50;
  margin-bottom: 0.5em;
  font-weight: 100;
`;

const PostMeta = styled.small`
  font-family: "Open Sans", sans-serif;
  color: #666;
  text-transform: uppercase;
  font-size: 1em;
  display: block;
  margin-top: -0.5em;
  margin-bottom: 1em;
`;

const PostExcerpt = styled.p`
  font-family: "Open Sans", sans-serif;
  color: #333;
`;

const ContributionsCard = styled.div`
  position: relative;
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

// Tooltip styled component
const Tooltip = styled.div`
  position: fixed;
  background-color: #2c3e50;
  color: #fff;
  padding: 10px;
  border-radius: 5px;
  font-size: 12px;
  display: ${(props) => (props.show ? "block" : "none")};
  transform: translate(-35%, -150%); // adjust the tooltip position
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

const TooltipTarget = styled.div`
  position: relative;

  &:hover ${Tooltip} {
    opacity: 0.7;
    visibility: visible;
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

  const [tooltipInfo, setTooltipInfo] = useState({
    show: false,
    text: "",
  });

  const [referenceElement, setReferenceElement] = useState(null);
  const [popperElement, setPopperElement] = useState(null);
  const { styles, attributes } = usePopper(referenceElement, popperElement, {
    placement: "top",
    strategy: "absolute",
  });

  // Get the width/height of a grid item
  const monthSize = referenceElement ? referenceElement.offsetWidth / 12 : 0; // We assume that all Months are square and have the same size

  return (
    <Layout>
      <Helmet>
        <title>Blog - Yohandi</title>
      </Helmet>
      <Container>
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
              </Post>
            </PostLink>
          ))}
        </Card>
        <Card>
          <ContributionsCard ref={setReferenceElement}>
            {Object.entries(contributions).map(([year, contributionsForYear]) =>
              contributionsForYear.map((postCount, i) => (
                <Month
                  ref={setReferenceElement}
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
                      left: rect.left,
                    });
                  }}
                  onMouseLeave={() => {
                    setTooltipInfo({ ...tooltipInfo, show: false });
                  }}
                />
              ))
            )}
            <Tooltip
              ref={setPopperElement}
              style={{
                top: tooltipInfo.top + "px",
                left: tooltipInfo.left + "px",
              }}
              {...attributes.popper}
              show={tooltipInfo.show}
            >
              {tooltipInfo.text}
            </Tooltip>
          </ContributionsCard>
        </Card>
      </Container>
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
          excerpt(pruneLength: 200)
        }
      }
    }
  }
`;

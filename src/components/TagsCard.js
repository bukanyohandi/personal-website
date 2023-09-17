// TagsCard.js

import React from "react";
import { graphql, useStaticQuery, Link } from "gatsby";
import styled from "styled-components";

const EDIT_MODE = false;

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

const TagsContainer = styled.div`
  border: ${EDIT_MODE ? "1px solid" : "none"};
  margin-top: 20px;
  display: flex;
  flex-wrap: wrap;
  gap: 5px;
`;

const TagsComponent = () => {
  const data = useStaticQuery(graphql`
    query tagsQuery {
      allMarkdownRemark {
        edges {
          node {
            frontmatter {
              tags
            }
          }
        }
      }
    }
  `);

  const allTags = data.allMarkdownRemark.edges
    .map((edge) => edge.node.frontmatter.tags)
    .flat();
  const uniqueTagsSet = new Set(allTags);
  const uniqueTags = [...uniqueTagsSet].sort();

  return (
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
  );
};

export default TagsComponent;

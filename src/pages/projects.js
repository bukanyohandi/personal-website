import React from "react";
import { Helmet } from "react-helmet";
import { graphql } from "gatsby";
import Layout from "../layouts";
import styled, { createGlobalStyle } from "styled-components";

const EDIT_MODE = false;

const GlobalStyle = createGlobalStyle`
::-webkit-scrollbar {
  width: 0 !important;
}

body {
  -ms-overflow-style: none;
}
`;

const Container = styled.div`
  width: 90%;
  gap: 3%;
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  justify-content: center;
  background-color: #eef2f7;
  padding: 0 0;
  margin: 25px auto 0 auto;
  max-width: 950px;
  border: ${EDIT_MODE ? "1px solid" : "none"};

  @media only screen and (max-width: 950px) {
    gap: 6%;
  }
`;

// Various styled components for posts
const Project = styled.a`
  min-width: 200px;
  max-width: 25%;
  background-color: white;
  border-radius: 5px;
  padding: 20px;
  margin: 15px 0 15px 0;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
  text-decoration: none;
  border: ${EDIT_MODE ? "1px solid" : "none"};
  flex-direction: column;
  justify-content: space-between;
  position: relative;

  cursor: pointer; // Add a pointer cursor to indicate it's clickable
  text-decoration: none; // Remove the default underline

  @media only screen and (max-width: 950px) {
    max-width: 36%;
  }

  @media only screen and (max-width: 650px) {
    max-width: 80%;
  }

  &:hover {
    transform: scale(1.03); /* Increase the size by 5% on hover */
    transition: transform 0.2s ease; /* Add a smooth transition effect */
  }
`;

const ProjectTitle = styled.div`
  font-family: "Merriweather", serif;
  text-transform: uppercase;
  font-size: 1.2em;
  text-align: center;
  color: #2c3e50;
  margin-bottom: 0.5em;
  margin-top: 0.3em;
  font-weight: 100;
  border: ${EDIT_MODE ? "1px solid" : "none"};
`;

const ProjectImage = styled.img`
  width: 100%;
  aspect-ratio: 3/2;
`;

const ProjectContent = styled.div`
  flex-grow: 1; /* Content takes up remaining space */
`;

const ProjectDescription = styled.div`
  font-family: "Open Sans", sans-serif;
  font-size: 1.01em;
  text-align: center;
  color: #333;
  margin-bottom: 0.3em;
  border: ${EDIT_MODE ? "1px solid" : "none"};
`;

const ProjectYear = styled.div`
  font-family: "Open Sans", sans-serif;
  color: #666;
  text-transform: uppercase;
  font-size: 0.9em;
  display: block;
  text-align: right;
  border: ${EDIT_MODE ? "1px solid" : "none"};
  position: absolute;
  bottom: 6px;
  right: 9px;
`;

const TemporaryInformation = styled.div`
  font-family: "Merriweather", serif;
  text-align: center;
  font-size: 1em;
  color: #2c3e50;
  width: 100%;
  text-align: center;
  padding: 10px;
  background-color: #eef2f7;
  margin: 5px;
  user-select: none;
`;

export default function ProjectPage({ data }) {
  const projects = data.allProjectsJson.edges;

  return (
    <>
      <GlobalStyle />
      <Layout>
        <Helmet>
          <title>Yohandi</title>
          <meta
            name="description"
            content={`
            Yohandi. A passionate student with a strong interest in algorithms and data structures.
          `}
          />
        </Helmet>
        <Container>
          <TemporaryInformation>
            {" "}
            More will be added soon! I'm still searching through all my local
            repositories.
          </TemporaryInformation>
          {projects.map(({ node }) => (
            <Project key={node.title} href={node.url}>
              <ProjectImage src={node.img} />
              <ProjectContent>
                <ProjectTitle>{node.title}</ProjectTitle>
                <ProjectDescription>{node.desc}</ProjectDescription>
              </ProjectContent>
              <ProjectYear>{node.year}</ProjectYear>
            </Project>
          ))}
        </Container>
      </Layout>
    </>
  );
}

export const pageQuery = graphql`
  {
    allProjectsJson {
      edges {
        node {
          title
          img
          url
          desc
          year
        }
      }
    }
  }
`;

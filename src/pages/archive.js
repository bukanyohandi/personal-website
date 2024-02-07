import React from "react";
import { Router } from "@reach/router";
import Layout from "../layouts";
import ArchiveDirectory from "../components/ArchiveDirectory";
import styled, { createGlobalStyle } from "styled-components";
import { THEME } from "../constants.js";

const EDIT_MODE = true;

const GlobalStyle = createGlobalStyle`
::-webkit-scrollbar {
  width: 0;
}

body {
  -ms-overflow-style: none;
}
`;
const Container = styled.div`
  display: flex;
  flex-direction: row;
  align-items: flex-start;
  padding: 0;
  margin: 25px auto 0 auto;
  min-width: 90%;

  @media only screen and (max-width: 800px) {
    flex-direction: column;
    align-items: center;
  }
`;

const ArchiveDirectoryContainer = styled.div`
  width: 400px;
  height: 70vh; // Default height
  background-color: #f0f0f0;
  overflow-y: auto;
  border-radius: 20px 0 0 20px;
  border: 1px solid;
  border-color: #b8b4b4;

  &::-webkit-scrollbar {
    width: 12px;
  }

  &::-webkit-scrollbar-track {
    background: #f1f1f1;
  }

  &::-webkit-scrollbar-thumb {
    background: #d6d4d4;
  }

  &::-webkit-scrollbar-thumb:hover {
    background: #d6d4d4;
  }

  @media only screen and (max-width: 800px) {
    width: 100%;
    height: 30vh;
    border-radius: 0;
  }
`;

const DisplayContainer = styled.div`
  flex-grow: 1;
  flex-shrink: 1;
  height: 70vh;
  width: 100%;
  background-color: #f0f0f0;
  border: 1px solid;
  border-color: #b8b4b4;
  margin: 0;
`;

const ArchiveTemplate = () => {
  return (
    <>
      <GlobalStyle />
      <Layout>
        <Container>
          <ArchiveDirectoryContainer>
            <Router basepath="/archive">
              <ArchiveDirectory path="/*" />
            </Router>
          </ArchiveDirectoryContainer>
          <DisplayContainer>
            <p>(i'm still implementing ...)</p>
          </DisplayContainer>
        </Container>
      </Layout>
    </>
  );
};

export default ArchiveTemplate;

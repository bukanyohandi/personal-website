import React, { useState, useEffect } from "react";
import { Router } from "@reach/router";
import Layout from "../layouts";
import ArchiveDirectory from "../components/ArchiveDirectory";
import styled, { createGlobalStyle } from "styled-components";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { prism } from "react-syntax-highlighter/dist/esm/styles/prism";

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
  width: 90%;

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
    border-radius: 20px 0 0 0;
  }
`;

const DisplayContainer = styled.div`
  flex-grow: 1;
  flex-shrink: 1;
  height: 70vh;
  width: 100%;
  max-width: 99vw;
  background-color: #f0f0f0;
  border: 1px solid;
  border-color: #b8b4b4;
  margin: 0;

  @media only screen and (max-width: 800px) {
    height: 30vh;
    border-radius: 0;
  }
`;

const ContentWrapper = styled.div`
  height: inherit; // Adjust the height as needed
  overflow-y: auto; // Enable vertical scrolling
  overflow-x: auto;
  padding: 10px;

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
`;

const ArchiveTemplate = () => {
  const [selectedFile, setSelectedFile] = useState(null);
  const [fileContent, setFileContent] = useState("");

  const handleFileSelect = (file) => {
    setSelectedFile(file);
  };

  useEffect(() => {
    if (selectedFile && selectedFile.publicURL) {
      fetch(selectedFile.publicURL)
        .then((response) => response.text())
        .then((text) => setFileContent(text))
        .catch((error) => console.error("Error fetching file content:", error));
    }
  }, [selectedFile]);

  // Determine the language from the file extension
  const getLanguageFromExtension = (extension) => {
    switch (extension) {
      case "js":
        return "javascript";
      case "cpp":
        return "cpp";
      case "py":
        return "python";
      // Add more cases as needed
      default:
        return "plaintext";
    }
  };

  return (
    <>
      <GlobalStyle />
      <Layout>
        <Container>
          <ArchiveDirectoryContainer>
            <Router basepath="/archive">
              <ArchiveDirectory path="/*" onFileSelect={handleFileSelect} />
            </Router>
          </ArchiveDirectoryContainer>
          <DisplayContainer>
            {selectedFile ? (
              <ContentWrapper>
                <SyntaxHighlighter
                  language={getLanguageFromExtension(selectedFile.extension)}
                  style={{
                    ...prism,
                    hljs: { ...prism.hljs, background: "inherit" },
                  }}
                >
                  {fileContent}
                </SyntaxHighlighter>
              </ContentWrapper>
            ) : (
              <p></p>
            )}
          </DisplayContainer>
        </Container>
      </Layout>
    </>
  );
};

export default ArchiveTemplate;

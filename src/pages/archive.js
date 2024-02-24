import React, { useState, useEffect } from "react";
import { Router } from "@reach/router";
import Layout from "../layouts";
import ArchiveDirectory from "../components/ArchiveDirectory";
import styled, { createGlobalStyle } from "styled-components";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { prism } from "react-syntax-highlighter/dist/esm/styles/prism";
import PDFEmbed from "../components/PDFEmbed";

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

  @media only screen and (max-width: 1000px) {
    flex-direction: column;
    align-items: center;
    margin: 25px auto 0 auto;
  }
`;

const ArchiveDirectoryContainer = styled.div`
  width: 400px;
  min-width: 400px;
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

  @media only screen and (max-width: 1000px) {
    width: 100%;
    height: 20vh;
    border-radius: 20px 0 0 0;
  }
`;

const DisplayContainer = styled.div`
  flex-grow: 1;
  flex-shrink: 1;
  height: 70vh;
  width: 100%;
  max-width: 60vw;
  background-color: #f0f0f0;
  border: 1px solid;
  border-color: #b8b4b4;
  margin: 0;

  @media only screen and (max-width: 1000px) {
    height: 48vh;
    border-radius: 0;
    max-width: 100vw;
  }
`;

const ContentWrapper = styled.div`
  height: inherit;
  overflow-y: auto;
  overflow-x: scroll; // Changed to scroll to always show horizontal scrollbar
  padding: 0 10px;
  max-width: 100%;

  & pre {
    white-space: pre-wrap;
    word-wrap: break-word;
    overflow-wrap: break-word;
    max-width: 100%;
  }

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
  const [isLoading, setIsLoading] = useState(false);
  const [lastSelectedFileURL, setLastSelectedFileURL] = useState("");

  const handleFileSelect = (file) => {
    if (file.publicURL === lastSelectedFileURL) {
      setIsLoading(false);
    } else {
      setSelectedFile(file);
      setIsLoading(true);
      setLastSelectedFileURL(file.publicURL);
    }
  };

  useEffect(() => {
    if (selectedFile && selectedFile.publicURL) {
      fetch(selectedFile.publicURL)
        .then((response) => response.text())
        .then((text) => {
          setFileContent(text);
          setIsLoading(false);
        })
        .catch((error) => {
          console.error("Error fetching file content:", error);
          setIsLoading(false);
        });
    } else {
      setIsLoading(false);
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
            {isLoading ? (
              <p>Loading...</p>
            ) : selectedFile && selectedFile.extension === "pdf" ? (
              <PDFEmbed src={selectedFile.publicURL} height="100%" />
            ) : selectedFile ? (
              <ContentWrapper>
                <SyntaxHighlighter
                  language={getLanguageFromExtension(selectedFile.extension)}
                  style={{
                    ...prism,
                    hljs: { ...prism.hljs, background: "inherit" },
                    overflowX: "auto",
                    maxWidth: "100%",
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

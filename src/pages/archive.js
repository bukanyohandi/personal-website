import React, { useState, useEffect } from "react";
import { Router } from "@reach/router";
import Layout from "../layouts";
import ArchiveDirectory from "../components/ArchiveDirectory";
import styled, { keyframes, createGlobalStyle } from "styled-components";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { prism } from "react-syntax-highlighter/dist/esm/styles/prism";
import PDFEmbed from "../components/PDFEmbed";
import * as XLSX from "xlsx";

const rotate = keyframes`
  from {
    transform: rotate(0deg);
  }

  to {
    transform: rotate(360deg);
  }
`;

const LoadingSpinner = styled.div`
  border: 4px solid rgba(0, 0, 0, 0.1);
  width: 36px;
  height: 36px;
  border-radius: 50%;
  border-left-color: #f1f1f1;
  animation: ${rotate} 1s infinite linear;
  display: inline-block;
  margin: 0 auto;
`;

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
  display: flex;
  flex-direction: column;
  justify-content: ${({ isLoading }) => (isLoading ? "center" : "flex-start")};
  align-items: ${({ isLoading }) => (isLoading ? "center" : "stretch")};
  flex-grow: 1;
  flex-shrink: 1;
  height: 70vh;
  width: 100%;
  max-width: 60vw;
  background-color: #f0f0f0;
  border: 1px solid;
  border-color: #b8b4b4;
  margin: 0;
  overflow: auto;

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
    const readXLSXData = async (blob) => {
      const data = await blob.arrayBuffer();
      const workbook = XLSX.read(data, { type: "buffer" });
      const sheetName = workbook.SheetNames[0];
      const worksheet = workbook.Sheets[sheetName];
      // Parse the worksheet to an array of arrays
      return XLSX.utils.sheet_to_json(worksheet, { header: 1, defval: "" });
    };

    if (selectedFile && selectedFile.publicURL) {
      setIsLoading(true);
      fetch(selectedFile.publicURL)
        .then((response) => response.blob())
        .then((blob) => {
          if (selectedFile.extension === "xlsx") {
            readXLSXData(blob).then((dataArray) => {
              setFileContent(dataArray); // Directly set the parsed array
              setIsLoading(false);
            });
          } else {
            blob.text().then((text) => {
              setFileContent(text); // Set the text content for non-.xlsx files
              setIsLoading(false);
            });
          }
        })
        .catch((error) => {
          console.error("Error:", error);
          setIsLoading(false);
        });
    } else {
      setIsLoading(false);
    }
  }, [selectedFile]);

  const renderTable = (dataArray) => {
    return (
      <ContentWrapper>
        <table>
          <tbody>
            {dataArray.map((row, rowIndex) => (
              <tr key={`row-${rowIndex}`}>
                {row.map((cell, cellIndex) => (
                  <td key={`cell-${rowIndex}-${cellIndex}`}>{cell}</td>
                ))}
              </tr>
            ))}
          </tbody>
        </table>
      </ContentWrapper>
    );
  };

  // Determine the language from the file extension
  const getLanguageFromExtension = (extension) => {
    switch (extension) {
      case "js":
        return "javascript";
      case "c":
      case "h":
        return "c";
      case "cu":
      case "cpp":
      case "hpp":
        return "cpp";
      case "py":
        return "python";
      case "java":
        return "java";
      case "ts":
        return "typescript";
      case "cs":
        return "csharp";
      case "rb":
        return "ruby";
      case "php":
        return "php";
      case "html":
      case "htm":
        return "html";
      case "css":
        return "css";
      case "json":
        return "json";
      case "md":
        return "markdown";
      case "sh":
        return "bash";
      case "v":
      case "vvp":
        return "verilog";
      // Add more cases as needed for additional file types
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
          <DisplayContainer isLoading={isLoading}>
            {isLoading ? (
              <LoadingSpinner />
            ) : selectedFile && selectedFile.extension === "pdf" ? (
              <PDFEmbed src={selectedFile.publicURL} height="100%" />
            ) : selectedFile && selectedFile.extension === "xlsx" ? (
              renderTable(fileContent)
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

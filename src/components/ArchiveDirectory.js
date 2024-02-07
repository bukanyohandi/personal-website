import React, { useEffect, useState } from "react";
import { navigate, graphql, useStaticQuery } from "gatsby";
import directoryStructure from "/static/archive-structure.json";
import styled from "styled-components";
import { Link } from "gatsby";

const DirectoryList = styled.ul`
  list-style: none;
  padding: 0;
  margin: 0;
`;

const DirectoryItem = styled.li`
  display: flex;
  align-items: center;
  cursor: pointer;
  padding: 4px;

  &:hover {
    background-color: #c2e7ff;
  }
`;

const StyledLink = styled(Link)`
  display: flex;
  align-items: center;
  text-decoration: none;
  color: inherit;
  width: 100%;
  box-sizing: border-box;
`;

const Text = styled.span`
  margin-left: 8px;
  user-select: none;
  flex: 1;
  text-align: left;
  white-space: normal;
  overflow-wrap: break-word;
`;

const ArchiveDirectory = ({ location, onFileSelect }) => {
  const [subfolders, setSubfolders] = useState([]);
  const [files, setFiles] = useState([]);

  const currentPath = location.pathname
    .replace("/archive/", "")
    .replace(/\/$/, "");
  const paths = currentPath.split("/").filter(Boolean);

  const data = useStaticQuery(graphql`
    query {
      allFile(filter: { sourceInstanceName: { eq: "archive" } }) {
        nodes {
          relativePath
          name
          extension
          publicURL
        }
      }
    }
  `);

  useEffect(() => {
    const findCurrentDirectory = (pathSegments, directory) => {
      if (pathSegments.length === 0) return directory;
      const nextSegment = pathSegments.shift();
      if (directory[nextSegment]) {
        return findCurrentDirectory(pathSegments, directory[nextSegment]);
      }
      return {};
    };

    const currentDirectory = findCurrentDirectory(
      [...paths],
      directoryStructure.root
    );
    setSubfolders(Object.keys(currentDirectory));

    const currentDirectoryFiles = data.allFile.nodes.filter((file) => {
      const fileDirectoryPath = file.relativePath.substring(
        0,
        file.relativePath.lastIndexOf("/")
      );
      return currentPath === fileDirectoryPath;
    });
    setFiles(currentDirectoryFiles);
  }, [currentPath]);

  const handleNavigation = (path) => {
    navigate(`/archive/${currentPath ? `${currentPath}/` : ""}${path}`);
  };

  const handleFileClick = (file) => {
    onFileSelect(file);
  };

  return (
    <div>
      <DirectoryList>
        {subfolders.map((folderName) => (
          <DirectoryItem
            key={folderName}
            onClick={() => handleNavigation(folderName)}
          >
            <StyledLink
              to={`/archive/${
                currentPath ? `${currentPath}/` : ""
              }${folderName}`}
            >
              <div className="folder-icon" />
              <Text>{folderName}</Text>
            </StyledLink>
          </DirectoryItem>
        ))}
        {files
          .sort((a, b) => a.name.localeCompare(b.name))
          .map((file) => (
            <DirectoryItem
              key={file.name}
              onClick={() => handleFileClick(file)}
            >
              <div className="file-icon" />
              <Text>{`${file.name}.${file.extension}`}</Text>
            </DirectoryItem>
          ))}
      </DirectoryList>
    </div>
  );
};

export default ArchiveDirectory;

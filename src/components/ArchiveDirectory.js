import React, { useEffect, useState } from "react";
import { navigate, graphql, useStaticQuery } from "gatsby";
import directoryStructure from "/static/archive-structure.json";
import styled, { css } from "styled-components";
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

  ${(props) =>
    props.isSelected &&
    css`
      background-color: #c2bebe;
    `}
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

const BackButton = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  width: 30px;
  height: 30px;
  margin: 0;
  padding: 4px;
  background-color: inherit;
  border: none;
  cursor: pointer;
  font-size: 16px;

  &:hover {
    background-color: #c2e7ff;
  }
`;

const DirectoryName = styled.div`
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
  max-width: 100%;
  margin-left: 8px;
  margin-right: 8px;
  font-size: 15px;
  user-select: none;
  flex: 1;
  font-weight: normal;
  font-family: "Open Sans", sans-serif;
`;

const NavigationHeader = styled.div`
  display: flex;
  align-items: center;
  position: sticky;
  top: 0;
  z-index: 1000;
  background-color: #f0f0f0;
`;

const ArchiveDirectory = ({ location, onFileSelect }) => {
  const [subfolders, setSubfolders] = useState([]);
  const [files, setFiles] = useState([]);
  const [selectedFile, setSelectedFile] = useState(null); // New state for tracking the selected file

  const handleBack = () => {
    const pathSegments = currentPath.split("/").filter(Boolean);
    if (pathSegments.length > 0) {
      pathSegments.pop();
      const parentPath = pathSegments.join("/");
      navigate(`/archive/${parentPath}`);
    }
  };

  const currentPath = location.pathname
    .replace("/archive/", "")
    .replace(/\/$/, "");
  const paths = currentPath.split("/").filter(Boolean);
  const currentDirectoryName = paths.length > 0 ? paths[paths.length - 1] : "";

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
  }, [currentPath, data.allFile.nodes]);

  const handleNavigation = (path) => {
    navigate(`/archive/${currentPath ? `${currentPath}/` : ""}${path}`);
  };

  const handleFileClick = (file) => {
    onFileSelect(file);
    setSelectedFile(file.name);
  };

  return (
    <div>
      <NavigationHeader>
        {paths.length > 0 && (
          <BackButton onClick={handleBack} aria-label="Go back">
            <div className="back-icon" />{" "}
          </BackButton>
        )}
        <DirectoryName title={currentDirectoryName}>
          {currentDirectoryName}
        </DirectoryName>
      </NavigationHeader>
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
              isSelected={selectedFile === file.name}
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

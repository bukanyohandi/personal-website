import React, { useState, useEffect, useRef } from "react";
import styled from "styled-components";
import { useStaticQuery, graphql } from "gatsby";
import { useFlexSearch } from "react-use-flexsearch";
import { Link } from "gatsby";
import { useLocation } from "@reach/router";
import { FiX } from "react-icons/fi";
import archiveStructure from "/static/archive-structure.json";

const placeholderSentences = [
  "Searching for answers as deep as a Dark Roast...",
  "Looking for that secret ingredient in your Pumpkin Spice Latte?",
  "Did someone say FRAPPUCCINO? It's a search party now!",
  "Typing... fueled by a venti Caramel Macchiato.",
  "ESPRESSO yourself and search away!",
  "Finding the perfect answer, one Cold Brew at a time...",
  "Brewing up some search results with a touch of Mocha madness...",
  "Looking for more than just the foam on your Cappuccino?",
  "Pouring over results like a barista making a Flat White...",
  "Need answers fast? Double-shot of search coming up!",
  "Spicing up your search with a hint of Chai Latte humor...",
  "Searching for something smoother than a Vanilla Latte...",
  "On a quest for results as bold as your Americano?",
  "Mixing up your search like a perfect Iced Caramel Macchiato...",
  "Exploring results one sip of White Chocolate Mocha at a time...",
  "Adding some Pumpkin Cream Cold Brew vibes to your search...",
  "Searching with the energy of a Triple Espresso shot!",
  "Finding that hidden gem like a secret menu Pink Drink...",
  "Brewing results as carefully as a Nitro Cold Brew...",
  "Stirring up answers with the smoothness of a Honey Oat Latte...",
];

const extractFiles = (node, path = []) => {
  let files = [];
  for (const key in node) {
    const currentPath = [...path, key];
    if (Object.keys(node[key]).length === 0) {
      files.push({
        id: currentPath.join("/"),
        title: key,
        path: `/archive/${currentPath.join("/")}`,
        type: "archive-file",
      });
    } else {
      files = files.concat(extractFiles(node[key], currentPath));
    }
  }
  return files;
};

const ClearButton = styled.button`
  position: absolute;
  right: 0px;
  top: 50%;
  transform: translateY(-50%);
  background: none;
  border: none;
  cursor: pointer;
  color: #333;

  &:hover {
    color: #ccc;
  }
`;

const SearchBarContainer = styled.div`
  min-width: 300px;
  max-width: 440px;
  width: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  margin-bottom: 20px; // Added margin to separate from navigation links
  position: relative; // Needed for absolute positioning of results
`;

const StyledInput = styled.input`
  padding: 12px;
  padding-right: 40px; /* Increased right padding to make room for the clear button */
  width: calc(100% - 40px); /* Reduce width to account for the button */
  border-radius: 5px;
  border: 1px solid #ccc;
  font-size: 16px;

  &:focus {
    outline: none;
    border-color: #7f8c8d;
  }

  @media only screen and (max-width: 800px) {
    width: calc(80% - 40px); /* Adjust width on smaller screens */
    padding-right: 35px; /* Adjust right padding on smaller screens */
  }
`;

const ResultsContainer = styled.div`
  width: 100%;
  max-height: 30vh;
  overflow-y: scroll;
  background-color: #fff;
  // border: 1px solid #ccc;
  border-radius: 5px;
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.5);
  position: absolute;
  top: 50px;
  z-index: 1000;
  display: ${({ show }) => (show ? "block" : "none")};
  user-select: none;

  @media only screen and (max-width: 800px) {
    width: 80%;
  }
`;

const ResultTitle = styled.h3`
  font-family: "Open Sans", sans-serif;
  font-size: 1.1em; // Make the title larger
  margin: 0;
  padding-bottom: 5px; // Space between title and content snippet
`;

const ContentSnippetBlog = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 0.9em;
  color: #666;
  margin: 0;
  margin-bottom: 10px;
  padding: 5px 0;

  mark {
    background-color: yellow;
    // color: black;
  }
`;

const ContentSnippetArchive = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 0.9em;
  color: #666;
  margin: 0;
  margin-bottom: 10px;
  padding: 5px 0;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
`;

const BlogLabel = styled.span`
  position: absolute;
  bottom: 5px; // Adjust as needed
  right: 5px; // Adjust as needed
  background: #3498db; // Use your blog's theme color
  color: white;
  padding: 2px 6px;
  font-size: 0.7em;
  border-radius: 3px;
  text-transform: uppercase;
`;

const ArchiveLabel = styled.span`
  position: absolute;
  bottom: 5px;
  right: 5px;
  background: #e67e22; // Choose a distinct color
  color: white;
  padding: 2px 6px;
  font-size: 0.7em;
  border-radius: 3px;
  text-transform: uppercase;
`;

const ResultItem = styled(Link)`
  display: block;
  padding: 10px;
  border-bottom: 1px solid #eee;
  color: #333;
  text-decoration: none;
  position: relative; // Position relative to allow absolute positioning of BlogLabel

  &:last-child {
    border-bottom: none;
  }

  &:hover {
    background-color: #f8f8f8;
  }

  a {
    text-decoration: none;
    color: inherit; // This ensures that the link has the same color as the ResultItem
  }
`;

const formatPath = (path, limit = 45) => {
  if (!path) return "";

  const parts = path.split("/");
  // if (parts.length <= 2) {
  // If the path has two or fewer parts, return it as is
  // return path.length <= limit ? path : `${parts[0]}/.../${parts[parts.length -1]}`;
  // }

  const first = parts[0];
  const last = parts[parts.length - 1];

  // Calculate the length available for the first and last parts
  const ellipsis = "...";
  const available = limit - ellipsis.length - 2; // 2 for the slashes

  // if (first.length + last.length + ellipsis.length + 2 <= limit) {
  //   return `${first}/.../${last}`;
  // }

  // Determine how much of the first and last parts can be displayed
  let remaining = available - last.length;
  if (remaining < 3) {
    remaining = 3;
  }

  const firstPart =
    first.length > remaining ? `${first.slice(0, remaining)}…` : first;

  const lastPart = last;

  return `${firstPart}/.../${lastPart}`;
};

const SearchBar = ({ condition, placeholderVersion }) => {
  const [query, setQuery] = useState("");
  const [showResults, setShowResults] = useState(false);
  const location = useLocation();
  const searchBarRef = useRef(); // Ref for the search bar container
  const [placeholder, setPlaceholder] = useState(""); // State for the placeholder

  useEffect(() => {
    const randomSentence =
      placeholderSentences[
        Math.floor(Math.random() * placeholderSentences.length)
      ];
    setPlaceholder(randomSentence);
  }, [placeholderVersion]); // Empty dependency array ensures this runs only once when the component mounts

  // Use the useStaticQuery hook to query for your data
  const data = useStaticQuery(graphql`
    query SearchQuery {
      localSearchPages {
        index
        store
      }
      allFile(filter: { sourceInstanceName: { eq: "archive" } }) {
        nodes {
          relativeDirectory
          relativePath
          name
          base
        }
      }
      allDirectory(filter: { sourceInstanceName: { eq: "archive" } }) {
        nodes {
          relativePath
          name
        }
      }
    }
  `);

  const getParentDirectory = (path) => {
    const parts = path.split("/");
    parts.pop();
    const parent = parts.join("/");
    return parent || "";
  };

  const archiveFiles = data.allFile.nodes.map((node) => ({
    id: node.relativePath,
    title: node.base,
    path: `/archive/${node.relativeDirectory}`,
    type: "archive-file",
    description: formatPath(node.relativeDirectory) || "",
  }));

  const archiveDirectories = data.allDirectory.nodes.map((node) => ({
    id: node.relativePath,
    title: node.name,
    path: `/archive/${node.relativePath}`,
    type: "archive-folder",
    description: formatPath(getParentDirectory(node.relativePath)),
  }));

  const archiveItems = [...archiveFiles, ...archiveDirectories];

  // Extract the index and store from the query result
  const { index, store } = data.localSearchPages;

  const blogResults = useFlexSearch(query, index, store).map((result) => ({
    ...result,
    type: "blog",
    hasSnippet: result.body.toLowerCase().includes(query.toLowerCase()),
  }));

  const archiveResults = archiveItems.filter((file) =>
    file.title.toLowerCase().includes(query.toLowerCase())
  );

  const combinedResults = [...blogResults, ...archiveResults];

  const handleInputChange = (event) => {
    const input = event.target.value.toLowerCase();
    setQuery(input);
    setShowResults(input.length > 0);
  };

  const clearSearch = () => {
    setQuery("");
    setShowResults(false);
  };

  // Click outside the search bar to close results
  const handleClickOutside = (event) => {
    if (searchBarRef.current && !searchBarRef.current.contains(event.target)) {
      setShowResults(false);
    }
  };

  useEffect(() => {
    document.addEventListener("mousedown", handleClickOutside);
    return () => {
      document.removeEventListener("mousedown", handleClickOutside);
    };
  }, []);

  const sortResults = (results, query) => {
    const queryLower = query.toLowerCase();

    return results.sort((a, b) => {
      const getPriority = (result) => {
        if (result.type === "blog" && result.hasSnippet) return 1;
        if (result.type === "archive-folder") return 2;
        if (result.type === "archive-file") return 3;
        if (result.type === "blog" && !result.hasSnippet) return 4;
        return 5; // Just in case
      };

      const priorityA = getPriority(a);
      const priorityB = getPriority(b);

      if (priorityA !== priorityB) {
        return priorityA - priorityB; // Lower priority number comes first
      }

      // If priorities are the same, sort by relevance in title
      const titleIndexA = a.title.toLowerCase().indexOf(queryLower);
      const titleIndexB = b.title.toLowerCase().indexOf(queryLower);

      if (titleIndexA !== titleIndexB) {
        return titleIndexA - titleIndexB;
      }

      // If still the same, sort alphabetically
      return a.title.localeCompare(b.title);
    });
  };

  const getRelevantSnippet = (content, query) => {
    content = content.replace(/###/g, "");

    if (content && query) {
      const contentLower = content.toLowerCase();
      const queryLower = query.toLowerCase();

      const index = contentLower.indexOf(queryLower);

      if (index !== -1) {
        let start = content.lastIndexOf(".", index) + 1;
        if (start < 0) start = 0;

        let end = content.indexOf(".", index);
        if (end === -1) end = content.length;

        const snippet = content.slice(start, end + 1).trim();

        return "..." + highlightQuery(snippet, query) + "...";
      }
    }
    return "No relevant snippet available...";
  };

  const escapeRegExp = (string) => {
    return string.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
  };

  const highlightQuery = (snippet, query) => {
    if (typeof snippet !== "string") {
      return "";
    }

    const escapedQuery = escapeRegExp(query);
    const regex = new RegExp(`(${escapedQuery})`, "gi");
    const highlighted = snippet.replace(regex, `<mark>$1</mark>`);

    return highlighted;
  };

  const sortedResults = sortResults(combinedResults, query);

  if (!condition) {
    return null;
  }

  return (
    <SearchBarContainer ref={searchBarRef}>
      <>
        <StyledInput
          type="text"
          placeholder={placeholder}
          value={query}
          onChange={handleInputChange}
          onFocus={() => query.length > 0 && setShowResults(true)}
        />
        {query && (
          <ClearButton onClick={clearSearch}>
            <FiX size={18} />
          </ClearButton>
        )}
      </>
      <ResultsContainer show={showResults}>
        {sortedResults.map((result) => (
          <ResultItem key={result.id} to={result.path}>
            {result.type === "blog" && <BlogLabel>BLOG</BlogLabel>}
            {(result.type === "archive-file" ||
              result.type === "archive-folder") && (
              <ArchiveLabel>ARCHIVE</ArchiveLabel>
            )}
            <ResultTitle>{result.title}</ResultTitle>
            {result.type === "blog" && (
              <ContentSnippetBlog
                dangerouslySetInnerHTML={{
                  __html: getRelevantSnippet(result.body, query),
                }}
              />
            )}
            {(result.type === "archive-file" ||
              result.type === "archive-folder") && (
              <ContentSnippetArchive
                dangerouslySetInnerHTML={{
                  __html: result.description,
                }}
              />
            )}
          </ResultItem>
        ))}
      </ResultsContainer>
    </SearchBarContainer>
  );
};

export default SearchBar;

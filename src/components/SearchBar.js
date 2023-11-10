import React, { useState, useEffect, useRef } from "react";
import styled from "styled-components";
import { useStaticQuery, graphql } from "gatsby";
import { useFlexSearch } from "react-use-flexsearch";
import { Link } from "gatsby";
import { useLocation } from "@reach/router";
import { FiX } from "react-icons/fi";

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
  width: 25%;
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
  border: 1px solid #ccc;
  border-radius: 5px;
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
  position: absolute;
  top: 50px; // Adjusted to fit the new input height
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

const ContentSnippet = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 0.9em;
  color: #666;
  margin: 0;
  padding: 5px 0;

  mark {
    background-color: yellow;
    // color: black;
  }
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

const SearchBar = () => {
  const [query, setQuery] = useState("");
  const [showResults, setShowResults] = useState(false);
  const location = useLocation();
  const searchBarRef = useRef(); // Ref for the search bar container

  // Use the useStaticQuery hook to query for your data
  const data = useStaticQuery(graphql`
    query SearchQuery {
      localSearchPages {
        index
        store
      }
    }
  `);

  // Extract the index and store from the query result
  const { index, store } = data.localSearchPages;
  const results = useFlexSearch(query, index, store);

  const handleInputChange = (event) => {
    setQuery(event.target.value.toLowerCase());
    if (event.target.value.length > 0) {
      setShowResults(true);
    } else {
      setShowResults(false);
    }
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
    // Convert the query to lowercase for case-insensitive comparison
    const queryLower = query.toLowerCase();

    // Sort the results array
    return results.sort((a, b) => {
      // Check if title contains the query for both results
      const titleMatchA = a.title.toLowerCase().includes(queryLower);
      const titleMatchB = b.title.toLowerCase().includes(queryLower);

      // If both have a match in the title or neither have, sort by the index of the match in the title
      if (titleMatchA && titleMatchB) {
        return (
          a.title.toLowerCase().indexOf(queryLower) -
          b.title.toLowerCase().indexOf(queryLower)
        );
      } else if (titleMatchA) {
        return -1; // Prioritize result A with title match
      } else if (titleMatchB) {
        return 1; // Prioritize result B with title match
      }

      // If neither result has a title match, sort by the index of the match in the body
      return (
        a.body.toLowerCase().indexOf(queryLower) -
        b.body.toLowerCase().indexOf(queryLower)
      );
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

  const highlightQuery = (snippet, query) => {
    const regex = new RegExp(`\\b${query}`, "gi");
    const highlighted = snippet.replace(regex, `<mark>${query}</mark>`);

    return highlighted;
  };

  const sortedResults = sortResults(results, query);

  return location.pathname === "/" ? (
    <SearchBarContainer ref={searchBarRef}>
      <>
        <StyledInput
          type="text"
          placeholder="Looking for something?"
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
            <BlogLabel>BLOG</BlogLabel> {/* This is the new label */}
            <ResultTitle>{result.title}</ResultTitle>
            <ContentSnippet
              dangerouslySetInnerHTML={{
                __html: getRelevantSnippet(result.body, query),
              }}
            />
          </ResultItem>
        ))}
      </ResultsContainer>
    </SearchBarContainer>
  ) : null;
};

export default SearchBar;

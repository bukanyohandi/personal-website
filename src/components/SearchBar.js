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

const ResultItem = styled(Link)`
  display: block;
  padding: 10px;
  border-bottom: 1px solid #eee;
  color: #333;
  text-decoration: none;

  &:last-child {
    border-bottom: none;
  }

  &:hover {
    background-color: #f8f8f8;
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

  // Custom sorting function to sort results by relevance
  const sortResults = (results) => {
    return results;
  };

  const getRelevantSnippet = (content, query) => {
    content = content.replace(/###/g, "");

    // Check if content is not undefined or null and query is not empty
    if (content && query) {
      // Find the index of the first occurrence of the query
      const index = content.indexOf(query);

      // If the query is found in the content
      if (index !== -1) {
        // Find the start of the sentence containing the query
        let start = content.lastIndexOf(".", index) + 1;
        if (start < 0) start = 0; // In case the sentence is at the beginning of the content

        // Find the end of the sentence containing the query
        let end = content.indexOf(".", index);
        if (end === -1) end = content.length; // In case the sentence is at the end of the content

        // Extract the sentence containing the query
        const snippet = content.slice(start, end + 1).trim();

        // Now you would highlight the search term within the snippet
        return "..." + highlightQuery(snippet, query) + "...";
      }
    }
    // If content is not available or the query is not found, return a default message
    return "No relevant snippet available...";
  };

  // Function to highlight the query term in the snippet
  const highlightQuery = (snippet, query) => {
    const highlighted = snippet.replace(
      new RegExp(query, "gi"),
      `<mark>${query}</mark>`
    );
    return highlighted;
  };

  // Use the custom sort function
  const sortedResults = sortResults(results);

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

// src/components/ExternalLinks.js

import React, { useEffect, useRef } from "react";
import styled from "styled-components";
import { useStaticQuery, graphql } from "gatsby";

const ExternalLinksContainer = styled.div`
  width: 100%;
  padding: 20px 0; /* Increased padding for better spacing */
  display: flex;
  justify-content: center;
    
  @media only screen and (max-width: 800px) {
    max-width: 590px;
  }

  @media only screen and (max-width: 700px) {
    max-width: 440px;
  }

  @media only screen and (max-width: 650px) {
    max-width: 410px;
  }

  @media only screen and (max-width: 600px) {
    max-width: 390px;
`;

const LinksWrapper = styled.div`
  display: flex;
  overflow-x: auto; /* Allows horizontal scrolling */
  scroll-snap-type: x mandatory;
  -webkit-overflow-scrolling: touch;
  max-width: 800px; /* Maximum width to contain multiple cards */
  width: 60%;
  margin: 0 auto;
  margin-top: -50px;
  padding: 10px;

  /* Hide scrollbar */
  -ms-overflow-style: none;
  scrollbar-width: none;
  &::-webkit-scrollbar {
    display: none;
`;

const LinkCard = styled.a`
  flex: 0 0 250px; /* Fixed width for each card */
  scroll-snap-align: center;
  background-color: #ffffff;
  border-radius: 8px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
  margin-right: 20px; /* Spacing between cards */
  padding: 15px;
  text-decoration: none;
  color: #2c3e50;
  transition: transform 0.3s ease, box-shadow 0.3s ease;
  display: flex;
  flex-direction: column;
  align-items: center;
  box-sizing: border-box; /* Include padding and borders in width */
  max-width: 450px; /* Ensure max-width matches flex-basis */

  &:last-child {
    margin-right: 0;
  }

  &:hover {
    transform: scale(1.05);
    box-shadow: 0 8px 12px rgba(0, 0, 0, 0.2);
  }

  @media only screen and (max-width: 800px) {
    flex: 0 0 250px; /* Adjust width for medium screens */
    padding: 8px;
    max-width: 280px;
  }

  @media only screen and (max-width: 600px) {
    flex: 0 0 250px; /* Adjust width for medium screens */
    padding: 8px;
    max-width: 200px;
  }

  @media only screen and (max-width: 480px) {
    flex: 0 0 200px; /* Adjust width for small screens */
    padding: 6px;
    max-width: 150px;
  }
`;

const LinkImage = styled.img`
  width: 200px; /* Adjusted to fit within the smaller card */
  height: 40px;
  object-fit: contain;
  margin-bottom: 10px;

  @media only screen and (max-width: 600px) {
    width: 80px;
    height: 35px;
  }

  @media only screen and (max-width: 480px) {
    width: 60px;
    height: 30px;
  }
`;

const LinkTitle = styled.h4`
  margin: 0 0 10px 0;
  font-size: 16px;
  text-align: center;
  white-space: nowrap; /* Prevent title from wrapping */
  overflow: hidden; /* Hide overflow text */
  text-overflow: ellipsis; /* Add ellipsis for overflowing text */
  width: 100%;
  border-bottom: 1px solid #e0e0e0;
  padding-bottom: 5px;
  box-sizing: border-box; /* Include padding and borders in width */
  word-break: break-word; /* Allow breaking long words if necessary */

  @media only screen and (max-width: 600px) {
    font-size: 10px;
  }

  @media only screen and (max-width: 480px) {
    font-size: 8px;
  }
`;

const LinkDescription = styled.p`
  margin: 10px 0 0 0;
  font-size: 12px;
  text-align: center;
  color: #555555;
  overflow: hidden;
  text-overflow: ellipsis;
  display: -webkit-box;
  -webkit-line-clamp: 3; /* Limit to 3 lines */
  -webkit-box-orient: vertical;
  box-sizing: border-box; /* Include padding and borders in width */

  @media only screen and (max-width: 600px) {
    font-size: 8px;
    // -webkit-line-clamp: 2; /* Limit to 2 lines on medium screens */
  }

  @media only screen and (max-width: 480px) {
    font-size: 6px;
    // -webkit-line-clamp: 2; /* Limit to 2 lines on small screens */
  }
`;

const ExternalLinks = () => {
  const data = useStaticQuery(graphql`
    query {
      allExternalLink {
        nodes {
          title
          description
          url
          image
        }
      }
    }
  `);

  const links = data.allExternalLink.nodes;

  const wrapperRef = useRef(null);

  useEffect(() => {
    // Scroll to the second card to center it upon component mount
    if (wrapperRef.current && links.length >= 2) {
      const secondCard = wrapperRef.current.children[1]; // Zero-based index
      if (secondCard) {
        secondCard.scrollIntoView({ behavior: "auto", inline: "center" });
      }
    }
  }, [links]);

  return (
    <ExternalLinksContainer>
      <LinksWrapper ref={wrapperRef}>
        {links.map((link, index) => (
          <LinkCard
            key={index}
            href={link.url}
            target="_blank"
            rel="noopener noreferrer"
          >
            {link.image && (
              <LinkImage
                src={link.image}
                alt={`${link.title || "No Title"} logo`}
              />
            )}
            <LinkTitle title={link.title || "No Title"}>
              {link.title || "No Title"}
            </LinkTitle>
            <LinkDescription>{link.description}</LinkDescription>
          </LinkCard>
        ))}
      </LinksWrapper>
    </ExternalLinksContainer>
  );
};

export default ExternalLinks;

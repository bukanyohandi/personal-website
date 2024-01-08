import React from "react";
import { Link } from "gatsby";
import styled from "styled-components";
import { useLocation } from "@reach/router";
import { THEME } from "../constants.js";
import "../styles/fonts.css";
import SearchBar from "./SearchBar.js";

const Container = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  height: ${({ Location }) => (Location.inHomePage ? "90vh" : "17vh")};
  background-color: ${THEME.PRIMARY};
`;

const TitlePart = styled.span`
  color: ${({ isMarked }) => (isMarked ? "#c0392b" : "#2c3e50")};
`;

const Title = styled.div`
  text-align: center;
  font-size: ${({ Location }) => (Location.inHomePage ? "55px" : "55px")};
  color: #2c3e50;
  margin: ${({ Location }) => (Location.inHomePage ? "0px" : "20px 0")};
  font-weight: 300;
  font-family: "Pixelify Sans", sans-serif;
  letter-spacing: 2px;
  margin-top: 0px;
  user-select: none;
  display: flex;
  align-items: center; // Vertically centers the items
  justify-content: center; // Horizontally centers the items

  @media only screen and (max-width: 800px) {
    font-size: 60px;
  }

  opacity: ${({ Location }) => (Location.inHomePage ? "0" : "1")};
  transform: translateY(
    ${({ Location }) =>
      Location.inProjectsPage || Location.inBlogPage
        ? "0vh"
        : Location.inHomePage
        ? "-8vh"
        : "0"}
  );
  animation: fadeInMoveUp 0.4s forwards 0s; // starts after 0.5s, lasts 1s

  @keyframes fadeInMoveUp {
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }

  width: 200px;
  justify-content: flex-end;

  &:hover {
    cursor: pointer;
  }
`;

const Description = styled.div`
  display: ${({ Location }) => (Location.inHomePage ? "block" : "none")};
  margin: 10px 0 25px 0;
  max-width: 450px;
  width: 95%;
  line-height: 1.5;
  font-size: 23px;
  font-family: "Open Sans", sans-serif;
  font-weight: lighter;
  text-align: center;
  color: #333;

  @media only screen and (max-width: 800px) {
    font-size: 18px;
  }

  opacity: ${({ Location }) => (Location.inHomePage ? "0" : "1")};
  transform: translateY(
    ${({ Location }) => (Location.inHomePage ? "-12vh" : "0")}
  );
  animation: fadeInMoveUp 0.4s forwards 0s; // starts after 0.5s, lasts 1s

  @keyframes fadeInMoveUp {
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }
`;

const Navigation = styled.nav`
  display: flex;
  justify-content: center;
  width: 120px;
  gap: 30px;
  margin-top: -10px;
  padding-top: 0px;

  opacity: ${({ Location }) =>
    Location.inProjectsPage || Location.inBlogPage || Location.inHomePage
      ? "0"
      : "1"};
  transform: translateY(
    ${({ Location }) =>
      Location.inProjectsPage || Location.inBlogPage
        ? "1vh"
        : Location.inHomePage
        ? "-15vh"
        : "0"}
  );
  animation: fadeInMoveUp 0.1s forwards 0s; // starts after 0.5s, lasts 1s

  @keyframes fadeInMoveUp {
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }
`;

const NavLink = styled(Link)`
  position: relative;
  text-decoration: none;
  color: #2b3d4f;
  font-size: 18px;
  font-family: "Roboto", sans-serif;
  text-transform: uppercase;
  transition: all 0.3s cubic-bezier(0.25, 0.1, 0.25, 1);
  font-weight: 400;

  user-select: none;
`;

const activeLinkStyle = {
  color: "#c0392b",
  fontWeight: 400,
};

const Header = () => {
  const [isHovered, setIsHovered] = React.useState(false);

  const inHomePage = useLocation().pathname === "/";
  const inBlogPage = useLocation().pathname === "/blog/";
  const inProjectsPage = useLocation().pathname === "/projects/";

  React.useEffect(() => {
    console.log("Hover State: ", isHovered);
  }, [isHovered]);

  return (
    <>
      <Container
        THEME={THEME}
        Location={{ inHomePage, inBlogPage, inProjectsPage }}
      >
        <Title
          Location={{ inHomePage, inBlogPage, inProjectsPage }}
          onMouseEnter={() => setIsHovered(true)}
          onMouseLeave={() => setIsHovered(false)}
        >
          {isHovered ? (
            <>
              <TitlePart key="1">it's </TitlePart>
              <TitlePart key="2" isMarked>
                yoh{" "}
              </TitlePart>
              <TitlePart key="3">and </TitlePart>
              <TitlePart key="4" isMarked>
                i
              </TitlePart>
            </>
          ) : (
            "yohandi"
          )}
        </Title>
        <Description Location={{ inHomePage, inBlogPage, inProjectsPage }}>
          A passionate student with a strong interest in algorithms and data
          structures.
        </Description>
        <SearchBar inHomePage={inHomePage} />
        <Navigation Location={{ inHomePage, inBlogPage, inProjectsPage }}>
          <NavLink to="/" activeStyle={activeLinkStyle}>
            Home
          </NavLink>
          <NavLink to="/projects" activeStyle={activeLinkStyle}>
            Projects
          </NavLink>
          <NavLink
            to="/blog"
            activeStyle={activeLinkStyle}
            partiallyActive={true}
          >
            Blog
          </NavLink>
          {/* <NavLink to="/resume" activeStyle={activeLinkStyle}>
          Resume
        </NavLink> */}
        </Navigation>
      </Container>
    </>
  );
};

export default Header;

import React from "react";
import { Link } from "gatsby";
import styled from "styled-components";
import { useLocation } from "@reach/router";
import { THEME } from "../constants.js";
import "../styles/fonts.css";
import SearchBar from "./SearchBar.js";

const HeaderContent = styled.div`
  display: flex;
  flex-direction: ${({ condition }) => (condition ? "column" : "row")};
  align-items: center;
  width: 100%;
  max-width: ${({ condition }) => (condition ? "500px" : "100%")};
  padding: ${({ condition }) => (condition ? "0" : "0 20px")};

  @media (max-width: 800px) {
    flex-direction: column;
    max-width: 100%;
  }
`;

const SearchBarWrapper = styled.div`
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  width: 100%; /* Optional: Adjust width as needed */
  max-width: 450px; /* Optional: Limit the maximum width */
  padding: 0 20px; /* Optional: Add padding if necessary */

  @media (max-width: 800px) {
    max-width: 90%;
  }
`;

// Existing Container component
const Container = styled.div`
  position: relative; /* Added to establish a containing block */
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  // border: 2px solid red;
  margin-top: ${({ Location }) => (Location.inHomePage ? "13vh" : "0vh")};
  height: ${({ Location }) => (Location.inHomePage ? "35vh" : "15vh")};
  background-color: ${THEME.PRIMARY};

  @media (max-width: 800px) {
    margin-top: ${({ Location }) => (Location.inHomePage ? "10vh" : "0vh")};
    height: ${({ Location }) => (Location.inHomePage ? "35vh" : "15vh")};
  }
`;

const TitlePart = styled.span`
  color: ${({ isMarked }) => (isMarked ? "#c0392b" : "#2c3e50")};
`;

const Title = styled.div`
  text-align: center;
  font-size: ${({ Location }) => (Location.inHomePage ? "55px" : "0px")};
  color: #2c3e50;
  margin: ${({ Location }) => (Location.inHomePage ? "0px" : "0")};
  font-weight: 300;
  font-family: "Pixelify Sans", sans-serif;
  letter-spacing: 2px;
  margin-top: ${({ Location }) => (Location.inHomePage ? "0px" : "20px")};
  user-select: none;
  display: flex;
  align-items: center;
  justify-content: center;

  @media only screen and (max-width: 800px) {
    font-size: ${({ Location }) => (Location.inHomePage ? "60px" : "px")};
  }

  opacity: ${({ Location }) => (Location.inHomePage ? "1" : "1")};
  transform: translateY(
    ${({ Location }) =>
      Location.inProjectsPage ||
      Location.inBlogPage ||
      Location.inArchivePage ||
      Location.inRecruitmentPage
        ? "0vh"
        : Location.inHomePage
        ? "0vh"
        : "0"}
  );
  // animation: fadeInMoveUp 0.4s forwards 0s;

  // @keyframes fadeInMoveUp {
  //   to {
  //     opacity: 1;
  //     transform: translateY(0);
  //   }
  // }

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
  font-size: 21px;
  font-family: "Open Sans", sans-serif;
  font-weight: lighter;
  text-align: center;
  color: #333;

  @media only screen and (max-width: 800px) {
    font-size: 18px;
  }

  opacity: ${({ Location }) => (Location.inHomePage ? "1" : "1")};
  transform: translateY(${({ Location }) => (Location.inHomePage ? "0" : "0")});
  // animation: fadeInMoveUp 0.4s forwards 0s; // starts after 0.5s, lasts 1s

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
  width: 100%;
  gap: 30px;
  // margin-top: -10px;
  padding-top: 0px;
  flex-wrap: wrap; /* Allows buttons to wrap into multiple lines */

  opacity: ${({ Location }) =>
    Location.inProjectsPage ||
    Location.inBlogPage ||
    Location.inArchivePage ||
    Location.inRecruitmentPage ||
    Location.inHomePage
      ? "1"
      : "1"};
  transform: translateY(
    ${({ Location }) =>
      Location.inProjectsPage ||
      Location.inBlogPage ||
      Location.inArchivePage ||
      Location.inRecruitmentPage
        ? "1vh"
        : Location.inHomePage
        ? "0vh"
        : "0"}
  );
  // animation: fadeInMoveUp 0.1s forwards 0s;

  @keyframes fadeInMoveUp {
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }

  @media (max-width: 800px) {
    gap: 13px; /* Reduce gap for smaller screens */
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
`;

const activeLinkStyle = {
  color: "#c0392b",
  fontWeight: 400,
};

const Header = () => {
  const [isHovered, setIsHovered] = React.useState(false);
  const [placeholderVersion, setPlaceholderVersion] = React.useState(0); // Added state

  const inHomePage = useLocation().pathname === "/";
  const inBlogPage = useLocation().pathname === "/blog/";
  const inProjectsPage = useLocation().pathname === "/projects/";
  const inArchivePage = useLocation().pathname === "/archive/";
  const inRecruitmentPage = useLocation().pathname === "/recruitment/";

  const handleTitleClick = () => {
    setPlaceholderVersion((prev) => prev + 1);
  };

  React.useEffect(() => {
    console.log("Hover State: ", isHovered);
  }, [isHovered]);

  return (
    <>
      <Container
        THEME={THEME}
        Location={{
          inHomePage,
          inBlogPage,
          inProjectsPage,
          inArchivePage,
          inRecruitmentPage,
        }}
      >
        <HeaderContent condition={inHomePage}>
          <Title
            Location={{
              inHomePage,
              inBlogPage,
              inProjectsPage,
              inArchivePage,
              inRecruitmentPage,
            }}
            onClick={handleTitleClick}
          >
            yohandi
          </Title>
          <Description
            Location={{
              inHomePage,
              inBlogPage,
              inProjectsPage,
              inArchivePage,
              inRecruitmentPage,
            }}
          >
            A recent graduate with a strong interest in algorithms and data
            structures (and coffee).
          </Description>
          <SearchBar
            condition={inHomePage}
            placeholderVersion={placeholderVersion}
          />
        </HeaderContent>
        {/* <SearchBarWrapper> */}
        <SearchBar
          condition={!inHomePage}
          placeholderVersion={placeholderVersion}
        />
        {/* </SearchBarWrapper> */}
        <Navigation
          Location={{
            inHomePage,
            inBlogPage,
            inProjectsPage,
            inArchivePage,
            inRecruitmentPage,
          }}
        >
          <NavLink to="/" activeStyle={activeLinkStyle}>
            Home
          </NavLink>
          <NavLink
            to="/blog"
            activeStyle={activeLinkStyle}
            partiallyActive={true}
          >
            Blog
          </NavLink>
          <NavLink to="/projects" activeStyle={activeLinkStyle}>
            Projects
          </NavLink>
          <NavLink
            to="/archive"
            activeStyle={activeLinkStyle}
            partiallyActive={true}
          >
            Archive
          </NavLink>
          <NavLink to="/recruitment" activeStyle={activeLinkStyle}>
            Recruitment
          </NavLink>
        </Navigation>
      </Container>
    </>
  );
};

export default Header;

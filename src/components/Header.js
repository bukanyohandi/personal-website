import React from "react";
import { Link } from "gatsby";
import styled from "styled-components";
import { useLocation } from "@reach/router";

const Container = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  height: ${({ inHomePage }) => (inHomePage ? "90vh" : "17vh")};
  background-color: #f9f9f9;
  transition: height 1s ease-in-out;
`;

const Title = styled.div`
  text-align: center;
  font-size: ${({ inHomePage }) => (inHomePage ? "70px" : "70px")};
  color: #2c3e50;
  margin: ${({ inHomePage }) => (inHomePage ? "0px" : "20px 0")};
  font-weight: 300;
  font-family: "Satisfy", cursive;
  letter-spacing: 2px;
  margin-top: 0px;
`;

const Description = styled.div`
  display: ${({ inHomePage }) => (inHomePage ? "block" : "none")};
  margin: 10px 0 25px 0;
  max-width: 450px;
  width: 95%;
  line-height: 1.5;
  font-size: 23px;
  font-family: "Open Sans", sans-serif;
  font-weight: lighter;
  text-align: center;
  color: #333;
`;

const Navigation = styled.nav`
  display: flex;
  justify-content: center;
  width: 120px;
  gap: 30px;
  margin-top: -10px;
  padding-top: 0px;
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

  &:hover {
  }
`;

const activeLinkStyle = {
  color: "#c0392b",
  fontWeight: 400,
};

const Header = () => {
  const inHomePage = useLocation().pathname === "/";

  return (
    <Container inHomePage={inHomePage}>
      <Title inHomePage={inHomePage}>yohandi</Title>
      <Description inHomePage={inHomePage}>
        A passionate student with a strong interest in algorithms and data
        structures.
      </Description>
      <Navigation>
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
      </Navigation>
    </Container>
  );
};

export default Header;

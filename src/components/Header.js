import React from "react";
import { Link } from "gatsby";
import styled from "styled-components";
import { useLocation } from "@reach/router";

const Container = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: ${({ inHomePage }) =>
    inHomePage ? "center" : "flex-start"};
  align-items: center;
  height: ${({ inHomePage }) => (inHomePage ? "95vh" : "17vh")};
  background-color: #f9f9f9;
  transition: transform 0.3s ease-in-out;
  gap: 0px;
`;

const Title = styled.div`
  text-align: center;
  font-size: ${({ inHomePage }) => (inHomePage ? "70px" : "60px")};
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
  color: #2c3e50;
  font-size: 18px;
  font-family: "Roboto", sans-serif;
  text-transform: uppercase;
  transition: all 0.3s ease-in-out;

  &:hover {
    color: #c0392b;
  }
`;

const activeLinkStyle = {
  color: "#c0392b",
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

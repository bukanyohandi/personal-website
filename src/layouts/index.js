import React from "react";
import PropTypes from "prop-types";
import Header from "../components/Header";
import Footer from "../components/Footer";
import styled from "styled-components";
import { createGlobalStyle } from "styled-components";
import { Helmet } from "react-helmet";
import { THEME } from "../constants.js";

const GlobalStyle = createGlobalStyle`
  body {
    margin: 0;
    padding: 0;
    overflow: auto;
    display: flex;
    flex-direction: column;
    background-color: ${THEME.PRIMARY};
  }
`;

const Container = styled.div`
  display: grid;
  grid-template-rows: auto 1fr auto;
`;

const Layout = ({ children }) => {
  return (
    <>
      <link rel="icon" href="/static/favicon.ico"></link>
      <GlobalStyle />
      <Container>
        <Helmet>
          <title>Yohandi</title>
          <meta
            name="description"
            content={`
                Yohandi. A recent graduate with a strong interest in algorithms and data structures.
            `}
          />
        </Helmet>
        <Header />
        {children}
        <Footer />
      </Container>
    </>
  );
};

Layout.propTypes = {
  children: PropTypes.node.isRequired,
};

export default Layout;

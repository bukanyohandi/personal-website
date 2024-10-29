import React from "react";
import { Helmet } from "react-helmet";
import Layout from "../layouts";
import styled, { createGlobalStyle } from "styled-components";
import ExternalLinks from "../components/ExternalLinks";

const GlobalStyle = createGlobalStyle`
  ::-webkit-scrollbar {
    width: 0 !important;
  }

  body {
    -ms-overflow-style: none;
  }
`;

const ContentWrapper = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  box-sizing: border-box;
`;

export default function HomePage() {
  return (
    <>
      <GlobalStyle />
      <Layout>
        <Helmet>
          <title>Yohandi</title>
          <meta
            name="description"
            content="Yohandi. A recent graduate with a strong interest in algorithms and data structures."
          />
        </Helmet>
        <ContentWrapper>
          <ExternalLinks />
        </ContentWrapper>
      </Layout>
    </>
  );
}

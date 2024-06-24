import React from "react";
import { Helmet } from "react-helmet";
import Layout from "../layouts";
import styled, { createGlobalStyle } from "styled-components";

const GlobalStyle = createGlobalStyle`
::-webkit-scrollbar {
  width: 0 !important;
}

body {
  -ms-overflow-style: none;
}
`;

const HeightLimiter = styled.div`
  height: 100vh;
`;

export default function HomePage() {
  return (
    <>
      <GlobalStyle />
      <HeightLimiter>
        <Layout>
          <Helmet>
            <title>Yohandi</title>
            <meta
              name="description"
              content={`
                Yohandi. A recent graduate with a strong interest in algorithms and data structures.
              `}
            />
          </Helmet>
        </Layout>
      </HeightLimiter>
    </>
  );
}

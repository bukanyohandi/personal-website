import React from "react";
import { Helmet } from "react-helmet";
import Layout from "../layouts";
import styled from "styled-components";

const HeightLimiter = styled.div`
  height: 100vh;
`;

export default function ProjectPage() {
  return (
    <HeightLimiter>
      <Layout>
        <Helmet>
          <title>Yohandi</title>
          <meta
            name="description"
            content={`
            Yohandi. A passionate student with a strong interest in algorithms and data structures.
          `}
          />
        </Helmet>
      </Layout>
    </HeightLimiter>
  );
}

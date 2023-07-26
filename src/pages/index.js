import React from "react";
import { Helmet } from "react-helmet";
import Layout from "../layouts";

export default function HomePage() {
  return (
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
  );
}

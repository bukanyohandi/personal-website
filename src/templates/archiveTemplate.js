import React from "react";
import { Router } from "@reach/router";
import ArchiveDirectory from "../components/ArchiveDirectory";
import Layout from "../layouts";

const ArchiveDirectoryTemplate = () => {
  return (
    <Layout>
      <Router basepath="/archive">
        <ArchiveDirectory path="/*" />
      </Router>
    </Layout>
  );
};

export default ArchiveDirectoryTemplate;

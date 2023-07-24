import React from "react";
import { Link } from "gatsby";

const Header = () => {
  return (
    <>
      <h1> Yohandi </h1>
      <nav>
        <Link to="/">Home</Link>
        <Link to="/blog">Blog</Link>
      </nav>
    </>
  );
};

export default Header;

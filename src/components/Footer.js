import React from "react";
import { Link } from "gatsby";
import styled from "styled-components";

const Container = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  background-color: #f4f4f4;
`;

const MakeoverMessage = styled.div`
  font-size: 20px;
  font-family: "Open Sans", sans-serif;
  padding-bottom: 5px;
`;

const Footer = () => {
  return (
    <Container>
      <MakeoverMessage>
        Whoops! caught me in the middle of a makeover 😳
      </MakeoverMessage>
    </Container>
  );
};

export default Footer;

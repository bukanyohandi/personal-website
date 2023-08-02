import React from "react";
import styled from "styled-components";

const Container = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  background-color: #f9f9f9;
  height: 5vh;
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

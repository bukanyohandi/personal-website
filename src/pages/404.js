import React from "react";
import { Link } from "gatsby";
import styled, { createGlobalStyle } from "styled-components";

const GlobalStyle = createGlobalStyle`
  body {
    background-color: #eef2f7;
  }
`;

const Container = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 90vh;
`;

const MessageCard = styled.div`
  background-color: #ffffff;
  border-radius: 8px;
  padding: 30px;
  box-shadow: 0 5px 10px rgba(0, 0, 0, 0.1);
  text-align: center;
`;

const Heading = styled.h1`
  font-family: "Merriweather", serif;
  text-transform: uppercase;
  font-size: 2.2em;
  color: #273c75; /* deep blue */
  margin-bottom: 0.5em;
  margin-top: 0.3em;
  font-weight: 100;
`;

const MessageText = styled.p`
  font-family: "Open Sans", sans-serif;
  font-size: 1.05em;
  color: #333;
  max-width: 450px;
  margin-bottom: 1.5em;
`;

const ButtonLink = styled(Link)`
  text-decoration: none;
  color: #ffffff;
  font-size: 1.2em;
  background-color: #1abc9c; /* teal */
  padding: 8px 12px;
  border-radius: 5px;
  transition: background-color 0.2s;
  &:hover {
    background-color: #16a085; /* slightly darker teal on hover */
  }
`;

const NotFoundPage = () => {
  return (
    <>
      <GlobalStyle />
      <Container>
        <MessageCard>
          <Heading>404 Not Found</Heading>
          <MessageText>
            Oops! If you are here, either you are lost or I haven't implemented
            the feature yet :>
          </MessageText>
          <ButtonLink to="/">yohandi.me</ButtonLink>
        </MessageCard>
      </Container>
    </>
  );
};

export default NotFoundPage;

import React from "react";
import styled from "styled-components";
import { AiOutlineMail } from "react-icons/ai";

const Container = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  background-color: #f9f9f9;
  height: 10vh;
`;

const EmailWrapper = styled.a`
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 20px;
  font-family: "Open Sans", sans-serif;
  padding-bottom: 10px;
  color: inherit;
  text-decoration: none; // optional, if you want to remove the default link underline
`;

const EmailIcon = styled(AiOutlineMail)``;

const Footer = () => {
  return (
    <Container>
      <EmailWrapper href="mailto:yohandi.0903@gmail.com">
        <EmailIcon size={30} />
      </EmailWrapper>
    </Container>
  );
};

export default Footer;

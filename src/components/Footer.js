import React from "react";
import styled from "styled-components";
import { FaEnvelope, FaLinkedin, FaGithub } from "react-icons/fa";
import { THEME } from "../constants.js";

const Container = styled.div`
  display: flex;
  flex-direction: row;
  gap: 30px;
  justify-content: center;
  align-items: center;
  background-color: ${THEME.PRIMARY};
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
  text-decoration: none;
`;
const EmailIcon = styled(FaEnvelope)``;

const LinkedInWrapper = styled.a`
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 20px;
  font-family: "Open Sans", sans-serif;
  padding-bottom: 10px;
  color: inherit;
  text-decoration: none;
`;
const LinkedInIcon = styled(FaLinkedin)``;

const GitHubWrapper = styled.a`
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 20px;
  font-family: "Open Sans", sans-serif;
  padding-bottom: 10px;
  color: inherit;
  text-decoration: none;
`;
const GitHubIcon = styled(FaGithub)``;

const Footer = () => {
  return (
    <Container>
      <EmailWrapper href="mailto:yohandi.0903@gmail.com">
        <EmailIcon size={25} />
      </EmailWrapper>
      {/* <LinkedInWrapper href="https://linkedin.com/in/yohandi">
        <FaLinkedin size={25} />
      </LinkedInWrapper> */}
      <GitHubWrapper href="https://github.com/bukanyohandi">
        <FaGithub size={25} />
      </GitHubWrapper>
    </Container>
  );
};

export default Footer;

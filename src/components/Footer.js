import React from "react";
import styled from "styled-components";
import { useLocation } from "@reach/router";
import { FaEnvelope, FaLinkedin, FaGithub, FaInstagram } from "react-icons/fa";
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

const Wrapper = styled.a`
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 20px;
  font-family: "Open Sans", sans-serif;
  padding-bottom: 10px;
  color: inherit;
  text-decoration: none;

  opacity: 1;
  transform: ${({ Location }) =>
    Location.inHomePage ? "translateY(10vh)" : "translateY(0vh)"};
  // animation: fadeInMoveUp 1s forwards 0.5s; // starts after 0.5s, lasts 1s

  @keyframes fadeInMoveUp {
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }
`;

const InstagramIcon = styled(FaInstagram)``;
const EmailIcon = styled(FaEnvelope)``;
const LinkedInIcon = styled(FaLinkedin)``;
const GitHubIcon = styled(FaGithub)``;

const Footer = () => {
  const inHomePage = useLocation().pathname === "/";

  return (
    <Container>
      <Wrapper Location={{ inHomePage }} href="mailto:yohandi.0903@gmail.com">
        <EmailIcon size={25} />
      </Wrapper>
      <Wrapper Location={{ inHomePage }} href="https://linkedin.com/in/yohandi">
        <FaLinkedin size={25} />
      </Wrapper>
      <Wrapper Location={{ inHomePage }} href="https://github.com/bukanyohandi">
        <GitHubIcon size={25} />
      </Wrapper>
      <Wrapper
        Location={{ inHomePage }}
        href="https://www.instagram.com/yohandii/"
      >
        <InstagramIcon size={28} />
      </Wrapper>
    </Container>
  );
};

export default Footer;

import React, { useState } from "react";
import { Helmet } from "react-helmet";
import { graphql } from "gatsby";
import Layout from "../layouts";
import styled, { createGlobalStyle } from "styled-components";
import { THEME } from "../constants.js";

const GlobalStyle = createGlobalStyle`
  ::-webkit-scrollbar {
    width: 0 !important;
  }

  body {
    -ms-overflow-style: none;
    user-select: none;
  }
`;

const Brief = styled.div`
  background-color: ${THEME.SECONDARY};
  padding: 20px;
  margin-bottom: -20px;
  color: #333;
  font-family: "Merriweather", serif;
  font-size: 1.2em;
  line-height: 1.5;

  h2 {
    color: #c0392b;
  }
`;

const Container = styled.div`
  width: 100%;
  max-width: 800px;
  margin: 0 auto;
  background-color: ${THEME.SECONDARY};
  padding: 0 20px;
  margin-top: 25px;

  @media (max-width: 800px) {
    width: 95%;
    padding: 0 10px;
    margin-top: 25px;
  }
`;

const JobContainer = styled.div`
  width: 95%;
  background-color: white;
  border-radius: 5px;
  margin: 10px auto;
  padding: 15px;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
  cursor: pointer;
  position: relative; /* Make it relative for positioning the mark */

  &:hover .availability-tooltip {
    visibility: visible; /* Show the tooltip on hover */
  }
`;

const JobTitleContainer = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: center;
`;

const JobTitle = styled.h2`
  font-family: "Merriweather", serif;
  font-size: 1.3em;
  color: #2c3e50;
  margin: 0;
`;

const AvailabilityMark = styled.div`
  width: 10px;
  height: 10px;
  background-color: ${(props) =>
    props.available
      ? "#27ae60"
      : "#c0392b"}; /* Green for available, red for not available */
  border-radius: 50%;
  position: absolute;
  top: 10px;
  right: 10px;
`;

const Tooltip = styled.div`
  visibility: hidden;
  width: 150px;
  background-color: ${(props) =>
    props.available
      ? "#27ae60"
      : "#c0392b"}; /* Tooltip background based on availability */
  color: #fff;
  text-align: center;
  border-radius: 6px;
  padding: 5px;
  position: absolute;
  top: 0px;
  right: -175px; /* Default position for larger screens */
  z-index: 1;
  font-size: 0.9em;

  /* Arrow */
  &:after {
    content: "";
    position: absolute;
    top: 50%;
    right: 100%;
    margin-top: -5px;
    border-width: 5px;
    border-style: solid;
    border-color: transparent
      ${(props) => (props.available ? "#27ae60" : "#c0392b")} transparent
      transparent;
  }

  @media (max-width: 1200px) {
    right: 10px; /* Adjust the right position for smaller screens */
    top: -30px; /* Adjust the top position for smaller screens */

    &:after {
      right: auto; /* Reposition the arrow for smaller screens */
      left: 50%; /* Adjust for center */
      transform: translateX(-50%);
      margin-top: 12px;
      border-color: ${(props) => (props.available ? "#27ae60" : "#c0392b")}
        transparent transparent transparent; /* Change arrow position */
    }
  }
`;

const RedMark = styled.div`
  width: 10px;
  height: 10px;
  background-color: #c0392b;
  border-radius: 50%;
  position: absolute;
  top: 10px;
  right: 10px;
  visibility: ${(props) => (props.available ? "hidden" : "visible")};
`;

const JobAvailability = styled.span`
  font-family: "Open Sans", sans-serif;
  font-size: 0.9em;
  color: ${(props) =>
    props.available
      ? "#27ae60"
      : "#c0392b"}; /* Green for available, red for not available */
`;

const JobDetails = styled.div`
  margin-top: 15px;
`;

const SectionTitle = styled.h3`
  font-family: "Open Sans", sans-serif;
  font-size: 1.2em;
  color: #333;
  margin-bottom: 10px;
`;

const List = styled.ul`
  list-style-type: disc;
  margin-left: 20px;
`;

const ListItem = styled.li`
  font-family: "Open Sans", sans-serif;
  font-size: 0.9em; /* Reduced from 1em */
  color: #333;
  margin-bottom: 5px;
`;

const RecruitmentPage = ({ data }) => {
  const jobs = data.allJobsJson.edges;

  return (
    <>
      <GlobalStyle />
      <Layout>
        <Helmet>
          <title>Recruitment</title>
          <meta name="description" />
        </Helmet>
        <Container>
          <Brief>
            <h2>Start-up About</h2>
            <p>
              ⁤Established with a commitment to innovate in quantitative
              finance, our investment strategy uses advanced machine learning
              techniques as its foundation.
            </p>
            <p>
              We take a data-driven approach, grounded in thorough research
              across all our strategies. We are dedicated to deepening our
              research efforts to drive performance.
            </p>
            <p>
              We seek talented individuals with a passion for computer science,
              data science, and quantitative finance research to join our team
              and contribute to the future of automated investing.
            </p>

            <h2>Jobs</h2>
          </Brief>

          {jobs.map(({ node }) => (
            <Job key={node.title} job={node} />
          ))}
        </Container>
      </Layout>
    </>
  );
};

const Job = ({ job }) => {
  const [isOpen, setIsOpen] = useState(false);

  return (
    <JobContainer onClick={() => setIsOpen(!isOpen)}>
      <JobTitleContainer>
        <JobTitle>{job.title}</JobTitle>
        <AvailabilityMark available={job.availability === "Available"} />
        <Tooltip
          className="availability-tooltip"
          available={job.availability === "Available"}
        >
          {job.availability === "Available"
            ? "Job is available"
            : "Job is not available"}
        </Tooltip>
      </JobTitleContainer>
      {isOpen && (
        <JobDetails>
          <SectionTitle>Responsibilities:</SectionTitle>
          <List>
            {job.responsibilities.map((item, index) => (
              <ListItem key={index}>{item}</ListItem>
            ))}
          </List>
          <SectionTitle>Skills and Qualifications:</SectionTitle>
          <List>
            {job.requirements.map((item, index) => (
              <ListItem key={index}>{item}</ListItem>
            ))}
          </List>
          {/* Display Salary Range as normal text */}
          <p>
            <strong>Salary Range: </strong>
            {job.salaryRange}
          </p>
        </JobDetails>
      )}
    </JobContainer>
  );
};

export default RecruitmentPage;

export const pageQuery = graphql`
  {
    allJobsJson {
      edges {
        node {
          title
          responsibilities
          requirements
          salaryRange
          availability
        }
      }
    }
  }
`;

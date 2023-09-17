import React, { useState } from "react";
import styled from "styled-components";
import { useStaticQuery, graphql } from "gatsby";

const monthNames = [
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December",
];

function getMonthName(monthIndex) {
  return monthNames[monthIndex];
}

function getMax(contributions) {
  let max = -Infinity;
  Object.values(contributions).forEach((yearContributions) => {
    const yearMax = Math.max(...yearContributions);
    if (yearMax > max) {
      max = yearMax;
    }
  });
  if (max === 1) {
    max += 0.25;
  }
  return max;
}

const ContributionsCard = styled.div`
  position: relative;
  max-width: 800px;
  display: grid;
  grid-template-columns: repeat(12, 1fr); // Grid of 12 columns for each month
  grid-gap: 4px;
  padding: 10px;
  background-color: #fff;
  border-radius: 5px;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
`;

const Month = styled.div`
  width: 100%;
  padding-bottom: 100%; // This keeps the month squares aspect ratio 1:1
  border-radius: 2px;
  background-color: #ebedf0; // The default color of day squares
`;

const Tooltip = styled.div`
  position: fixed;
  background-color: #2c3e50;
  color: #fff;
  padding: 10px;
  border-radius: 5px;
  font-size: 12px;
  display: ${(props) => (props.show ? "block" : "none")};
  left: ${(props) => props.left || "0"}px;
  top: ${(props) => props.top || "0"}px;
  transform: translate(-50%, -150%); // Adjust the tooltip position
  transition: all 0.3s ease-in-out;
  white-space: nowrap;
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);

  &::after {
    content: "";
    position: absolute;
    top: 100%; // Arrow will appear at the bottom of tooltip
    left: 50%;
    margin-left: -5px;
    border-width: 5px;
    border-style: solid;
    border-color: #2c3e50 transparent transparent transparent;
  }
`;

export const ContributionsComponent = () => {
  const data = useStaticQuery(graphql`
    query getAllPostDates {
      allMarkdownRemark(sort: [{ frontmatter: { date: ASC } }]) {
        edges {
          node {
            frontmatter {
              date(formatString: "YYYY-MM-DD")
            }
          }
        }
      }
    }
  `);

  const postDates = data.allMarkdownRemark.edges.map(
    (edge) => edge.node.frontmatter.date
  );

  let contributions = {
    [2023]: new Array(12).fill(0),
    [2024]: new Array(12).fill(0),
    [2025]: new Array(12).fill(0),
  };

  postDates.forEach((date) => {
    const dateObj = new Date(date);
    const year = dateObj.getFullYear();
    const month = dateObj.getMonth();

    if (!contributions[year]) {
      contributions[year] = new Array(12).fill(0);
    }
    contributions[year][month]++;
  });

  const maxContributions = getMax(contributions);
  const [tooltipInfo, setTooltipInfo] = useState({
    show: false,
    text: "",
    top: 0,
    left: 0,
  });

  return (
    <ContributionsCard>
      {Object.entries(contributions).map(([year, contributionsForYear]) =>
        contributionsForYear.map((postCount, monthIndex) => (
          <Month
            key={monthIndex}
            style={{
              backgroundColor:
                postCount > 0
                  ? `rgba(25, 97, 39, ${
                      (1 + Math.log(postCount)) /
                      (1 + Math.log(maxContributions))
                    })`
                  : "#ebedf0",
            }}
            onMouseEnter={(e) => {
              const rect = e.target.getBoundingClientRect();
              setTooltipInfo({
                show: true,
                text: `${postCount} post${
                  postCount === 1 ? "" : "s"
                } in ${getMonthName(monthIndex)} ${year}`,
                top: rect.top,
                left: rect.left + rect.width / 2,
              });
            }}
            onMouseLeave={() => {
              setTooltipInfo((prev) => ({ ...prev, show: false }));
            }}
          />
        ))
      )}
      <Tooltip
        style={{
          top: tooltipInfo.top + "px",
          left: tooltipInfo.left + "px",
        }}
        show={tooltipInfo.show}
      >
        {tooltipInfo.text}
      </Tooltip>
    </ContributionsCard>
  );
};

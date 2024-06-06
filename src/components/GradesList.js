import React, { useState } from "react";
import styled from "styled-components";

const ContentWrapper = styled.div`
  width: 100%;
  padding: 20px;
  box-sizing: border-box;
  font-family: Arial, sans-serif;
  -webkit-touch-callout: none;
  -webkit-user-select: none;
  -khtml-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
`;

const HeaderCell = styled.div`
  cursor: pointer;
  background-color: inherit;
  padding: 10px;
  font-weight: bold;
  border-bottom: 2px solid #ddd;
  font-family: Helvetica, sans-serif;
  font-size: 16px;
  color: inerhti;
  display: flex;
  justify-content: center;
  align-items: center;
  user-select: none;

  &:hover {
    background-color: #e0e0e0;
  }

  &::after {
    content: ${({ sortOrder }) =>
      sortOrder === "asc"
        ? '"\\25B2"'
        : sortOrder === "desc"
        ? '"\\25BC"'
        : '""'};
    margin-left: 5px;
  }
`;

const GradeCell = styled.div`
  padding: 10px;
  text-align: center;
  border-bottom: 1px solid #ddd;
  font-family: Helvetica, sans-serif;
  font-size: 14px;
  color: #555;
`;

const HighlightedGrade = styled.div`
  display: inline-block;
  padding: 2px 6px;
  border-radius: 4px;
  background-color: ${({ percentage }) => {
    if (percentage >= 75) return "#d4edda"; // Green for high grades
    if (percentage >= 50) return "#fff3cd"; // Yellow for medium grades
    return "#f8d7da"; // Red for low grades
  }};
  user-select: none;
`;

const GradesList = ({ grades, onSort }) => {
  const [sortOrder, setSortOrder] = useState({
    task: null,
    dueDate: null,
    grade: null,
  });

  const handleSort = (column) => {
    const newSortOrder = sortOrder[column] === "asc" ? "desc" : "asc";
    onSort(column, newSortOrder);
    setSortOrder({
      task: column === "task" ? newSortOrder : null,
      dueDate: column === "dueDate" ? newSortOrder : null,
      grade: column === "grade" ? newSortOrder : null,
    });
  };

  const calculatePercentage = (gradeString) => {
    const [mark, fullMark] = gradeString.split("/").map(Number);
    return (mark / fullMark) * 100;
  };

  return (
    <ContentWrapper>
      <div
        style={{
          display: "grid",
          gridTemplateColumns: "repeat(3, 1fr)",
          textAlign: "center",
        }}
      >
        <HeaderCell
          onClick={() => handleSort("task")}
          sortOrder={sortOrder.task}
        >
          Task
        </HeaderCell>
        <HeaderCell
          onClick={() => handleSort("dueDate")}
          sortOrder={sortOrder.dueDate}
        >
          Due Date
        </HeaderCell>
        <HeaderCell
          onClick={() => handleSort("grade")}
          sortOrder={sortOrder.grade}
        >
          Grade
        </HeaderCell>
      </div>
      {grades.map((item, index) => (
        <div
          key={index}
          style={{
            display: "grid",
            gridTemplateColumns: "repeat(3, 1fr)",
            textAlign: "center",
          }}
        >
          <GradeCell>{item.task}</GradeCell>
          <GradeCell>{item.dueDate}</GradeCell>
          <GradeCell>
            <HighlightedGrade percentage={calculatePercentage(item.grade)}>
              {item.grade}
            </HighlightedGrade>
          </GradeCell>
        </div>
      ))}
    </ContentWrapper>
  );
};

export default GradesList;

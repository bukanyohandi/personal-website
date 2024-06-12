import React from "react";
import { isMobile } from "react-device-detect";
import styled from "styled-components";

const IFrameContainer = styled.div`
  margin: 2px;
`;

const PDFEmbed = ({ src, width, height }) => {
  const containerStyle = {
    width: width,
    height: height,
    minHeight: "400px",
    border: "1px solid #ccc",
    overflow: "hidden",
  };

  if (isMobile) {
    return (
      <IFrameContainer>
        <p>
          If the PDF doesn't load, you can download it{" "}
          <a href={src} download>
            here
          </a>
          .
        </p>
        <IFrameContainer>
          <iframe src={src} style={containerStyle}></iframe>
        </IFrameContainer>
      </IFrameContainer>
    );
  }

  return <embed src={src} type="application/pdf" style={containerStyle} />;
};

export default PDFEmbed;

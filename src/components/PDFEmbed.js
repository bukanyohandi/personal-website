import React from "react";
import { isMobile } from "react-device-detect";

const PDFEmbed = ({ src, width = "100%", height = "100%" }) => {
  const containerStyle = {
    width: width,
    height: height,
    minHeight: "400px",
    border: "1px solid #ccc", // Adjust as needed
    overflow: "hidden",
  };

  if (isMobile) {
    return (
      <div>
        <iframe src={src} style={containerStyle}></iframe>
        <p>
          <a href={src} download>
            Download PDF
          </a>
        </p>
      </div>
    );
  }

  return <embed src={src} type="application/pdf" style={containerStyle} />;
};

export default PDFEmbed;

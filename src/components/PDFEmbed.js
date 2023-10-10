import React from "react";

const PDFEmbed = ({ src, width = "100%", height = "800px" }) => {
  const containerStyle = {
    // minWidth: "900px",
    width: width,
    height: height,
    border: "none",
    overflow: "hidden",
    border: "1px",
  };

  return <embed src={src} type="application/pdf" style={containerStyle} />;
};

export default PDFEmbed;

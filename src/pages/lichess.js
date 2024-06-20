import React, { useEffect, useState, useRef } from "react";
import { Line } from "react-chartjs-2";
import { Chart, registerables } from "chart.js";
import "chartjs-adapter-date-fns";
import pgnParser from "pgn-parser";
import zoomPlugin from "chartjs-plugin-zoom";
import { Chessboard } from "react-chessboard";
import { Chess } from "chess.js";
import "../styles/lichess.css";

Chart.register(...registerables, zoomPlugin);

function getRatingTitle(rating) {
  if (rating >= 2700) return "Super Grandmaster";
  else if (rating >= 2500) return "Grandmaster (GM)";
  else if (rating >= 2400) return "International Master (IM)";
  else if (rating >= 2300) return "FIDE Master (FM)";
  else if (rating >= 2200) return "Candidate Master (CM)";
  else if (rating >= 2000) return "Expert";
  else if (rating >= 1800) return "Class A";
  else if (rating >= 1600) return "Class B";
  else if (rating >= 1400) return "Class C";
  else if (rating >= 1200) return "Class D";
  else if (rating >= 1000) return "Class E";
  else return "Novice";
}

const Lichess = () => {
  const [ratingsData, setRatingsData] = useState([]);
  const [minDate, setMinDate] = useState(null);
  const [maxDate, setMaxDate] = useState(null);
  const [selectedGame, setSelectedGame] = useState(null);
  const [currentMoveIndex, setCurrentMoveIndex] = useState(-1);
  const [fen, setFen] = useState("start");
  const [orientation, setOrientation] = useState("white");
  const chartRef = useRef(null);
  const chess = useRef(new Chess());

  useEffect(() => {
    if (typeof window !== "undefined") {
      console.log("Selected game updated", selectedGame);
      if (selectedGame) {
        setOrientation(
          selectedGame.whitePlayer === "bukanYohandi" ? "white" : "black"
        );
        chess.current.reset();
        setFen(chess.current.fen());
      }
    }
  }, [selectedGame]);

  useEffect(() => {
    if (typeof window !== "undefined") {
      const pgnFilePath = "/content/lichess_bukanYohandi_2024-06-12.pgn";
      fetch(pgnFilePath)
        .then((response) => {
          if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
          }
          return response.text();
        })
        .then((data) => {
          try {
            const parsedGames = pgnParser.parse(data);
            const bulletGames = parsedGames.filter((game) => {
              const timeControlHeader = game.headers.find(
                (header) => header.name === "TimeControl"
              );
              return timeControlHeader && timeControlHeader.value === "60+0";
            });

            const gameRatingsData = bulletGames
              .map((game) => {
                const dateHeader = game.headers.find(
                  (header) => header.name === "Date"
                );
                const timeHeader = game.headers.find(
                  (header) => header.name === "UTCTime"
                );
                const whitePlayerHeader = game.headers.find(
                  (header) => header.name === "White"
                );
                const blackPlayerHeader = game.headers.find(
                  (header) => header.name === "Black"
                );
                const whiteEloHeader = game.headers.find(
                  (header) => header.name === "WhiteElo"
                );
                const blackEloHeader = game.headers.find(
                  (header) => header.name === "BlackElo"
                );

                if (
                  !dateHeader ||
                  !timeHeader ||
                  !whitePlayerHeader ||
                  !blackPlayerHeader ||
                  !whiteEloHeader ||
                  !blackEloHeader
                ) {
                  return null;
                }

                const date = new Date(
                  `${dateHeader.value.replace(/\./g, "-")}T${timeHeader.value}Z`
                );
                const whitePlayer = whitePlayerHeader.value;
                const blackPlayer = blackPlayerHeader.value;
                const isUserWhite = whitePlayer === "bukanYohandi";
                const userRating = isUserWhite
                  ? parseInt(whiteEloHeader.value)
                  : parseInt(blackEloHeader.value);
                const sequence = game.moves;
                return {
                  date,
                  rating: userRating,
                  sequence,
                  whitePlayer,
                  blackPlayer,
                };
              })
              .filter((game) => game !== null); // Filter out any null values

            const ratingsByDate = {};
            gameRatingsData.forEach((data) => {
              const dateStr = data.date.toISOString().split("T")[0];
              if (
                !ratingsByDate[dateStr] ||
                ratingsByDate[dateStr].rating < data.rating
              ) {
                ratingsByDate[dateStr] = data;
              }
            });

            gameRatingsData.forEach((game, index) => {
              game.ratingChange =
                index === 0
                  ? 0
                  : game.rating - gameRatingsData[index - 1].rating;
            });

            console.log(ratingsByDate);

            const aggregatedRatingsData = Object.values(ratingsByDate);
            aggregatedRatingsData.sort((a, b) => a.date - b.date);

            const minDateVal = new Date(
              Math.min(...aggregatedRatingsData.map((d) => d.date))
            );
            const maxDateVal = new Date(
              Math.max(...aggregatedRatingsData.map((d) => d.date))
            );

            setMinDate(minDateVal);
            setMaxDate(maxDateVal);
            setRatingsData(aggregatedRatingsData);
          } catch (error) {
            console.error("Error parsing PGN data:", error);
          }
        })
        .catch((error) => {
          console.error("Fetch error:", error);
        });
    }
  }, []);

  const plugins = [
    {
      id: "backgroundColor",
      beforeDraw: (chart) => {
        const ctx = chart.ctx;
        const yAxis = chart.scales.y;
        const xAxis = chart.scales.x;
        const intervals = [
          { min: 2700, color: "#FF3333" },
          { min: 2500, max: 2699, color: "#FF7777" },
          { min: 2400, max: 2499, color: "#FFBB55" },
          { min: 2300, max: 2399, color: "#FFCC88" },
          { min: 2200, max: 2299, color: "#FF88FF" },
          { min: 2000, max: 2199, color: "#AAAAFF" },
          { min: 1800, max: 1999, color: "#76DDBB" },
          { min: 1600, max: 1799, color: "#76FF77" },
          { min: 0, max: 1599, color: "#CCCCCC" },
        ];

        ctx.save();
        ctx.beginPath();
        ctx.rect(xAxis.left, yAxis.top, xAxis.width, yAxis.height);
        ctx.clip();

        intervals.forEach((interval) => {
          const yStart = yAxis.getPixelForValue(
            interval.max ? interval.max + 1 : yAxis.max
          );
          const yEnd = yAxis.getPixelForValue(interval.min);
          ctx.fillStyle = interval.color;
          ctx.fillRect(
            xAxis.left,
            yStart,
            xAxis.right - xAxis.left,
            yEnd - yStart
          );
        });

        ctx.restore();
      },
    },
  ];

  const handlePointClick = (event, elements, chart) => {
    console.log("click");
    if (typeof window !== "undefined" && elements.length > 0) {
      const elementIndex = elements[0].index;
      const game = ratingsData[elementIndex];
      setSelectedGame(ratingsData[elementIndex]);
      setCurrentMoveIndex(-1);
      chess.current.reset();
      setFen(chess.current.fen());
      setOrientation(game.whitePlayer === "bukanYohandi" ? "white" : "black");
    }
  };

  const handleMoveChange = (direction) => {
    console.log("move");
    if (!selectedGame) return;

    if (direction === -1) {
      if (currentMoveIndex >= 0) {
        chess.current.undo();
        setCurrentMoveIndex(currentMoveIndex - 1);
        setFen(chess.current.fen());
      }
      return;
    }

    const newIndex = currentMoveIndex + direction;
    console.log(newIndex);
    if (newIndex >= 0 && newIndex < selectedGame.sequence.length) {
      const moveObject = selectedGame.sequence[newIndex];
      const move = moveObject.move;

      console.log(chess.current.moves());
      console.log(move);

      if (!chess.current.moves().includes(move)) return;

      chess.current.move(move);
      console.log(chess.current.moves());
      //   chess.move("e5");
      //   if (result === null) {
      //     console.error(`Invalid move attempted: ${move}`);
      //     alert(`Invalid move: ${move}`);
      //     return;
      //   }
      setFen(chess.current.fen());
      setCurrentMoveIndex(newIndex);
    }
  };

  const options = {
    maintainAspectRatio: false,
    responsive: true,
    aspectRatio: 2,
    scales: {
      x: {
        type: "time",
        time: {
          unit: "year",
          displayFormats: {
            year: "yyyy",
          },
        },
        title: {
          display: false, // Remove X-axis title
        },
      },
      y: {
        title: {
          display: false, // Remove Y-axis title
        },
        grid: {
          drawOnChartArea: true,
        },
        ticks: {
          callback: function (value) {
            return value.toFixed(0);
          },
        },
      },
    },
    plugins: {
      title: {
        display: true,
        text: "bukanYohandi's lichess (last updated 12 June 2024)",
      },
    },
    interaction: {
      mode: "nearest",
      axis: "xy",
      intersect: false,
    },
    onClick: handlePointClick,
    plugins: {
      legend: {
        display: false,
      },
      title: {
        display: false,
      },
      tooltip: {
        callbacks: {
          title: (tooltipItems) => {
            return new Date(tooltipItems[0].parsed.x)
              .toISOString()
              .split("T")[0];
          },
          label: (tooltipItem) => {
            const currentRating = tooltipItem.raw.y;
            const ratingChange = tooltipItem.raw.ratingChange;
            const changeSign = ratingChange >= 0 ? "+" : "";
            const title = getRatingTitle(currentRating);

            return `${currentRating} (${changeSign}${ratingChange}), ${title}`;
          },

          labelColor: function (context) {
            const value = context.parsed.y;
            let backgroundColor = "#FFFFFF";
            const intervals = [
              { min: 2700, color: "#FF3333" },
              { min: 2500, max: 2699, color: "#FF7777" },
              { min: 2400, max: 2499, color: "#FFBB55" },
              { min: 2300, max: 2399, color: "#FFCC88" },
              { min: 2200, max: 2299, color: "#FF88FF" },
              { min: 2000, max: 2199, color: "#AAAAFF" },
              { min: 1800, max: 1999, color: "#76DDBB" },
              { min: 1600, max: 1799, color: "#76FF77" },
              { min: 0, max: 1599, color: "#CCCCCC" },
            ];
            intervals.forEach((range) => {
              if (value >= range.min && (!range.max || value <= range.max)) {
                backgroundColor = range.color;
              }
            });
            return {
              borderColor: "transparent",
              backgroundColor: backgroundColor,
            };
          },
        },
      },
      zoom: {
        pan: {
          enabled: true,
          mode: "xy",
        },
        zoom: {
          enabled: true,
          mode: "xy",
        },
      },
    },
    elements: {
      point: {
        radius: 5,
        hoverRadius: 7,
        hitRadius: 10,
      },
    },
    hover: {
      mode: "index",
      intersect: false,
      axis: "xy",
    },
  };

  const data = {
    datasets: [
      {
        data: ratingsData.map((data, index) => ({
          x: data.date,
          y: data.rating,
          ratingChange:
            index > 0 ? data.rating - ratingsData[index - 1].rating : 0,
        })),
        fill: false,
        borderColor: "rgba(75, 192, 192, 1)",
        tension: 0.1,
      },
    ],
  };

  return (
    <div
      style={{
        display: "flex",
        flexDirection: "column",
        width: "100%",
        background: "linear-gradient(0deg, #161512 50vh, #2C2822)",
        color: "#999999",
        fontFamily: "Open Sans, sans-serif",
      }}
    >
      <div
        style={{
          textAlign: "center",
          padding: "20px",
        }}
      >
        <h1>bukanYohandi's lichess (last updated 12 June 2024)</h1>
      </div>
      <div
        style={{
          display: "flex",
          justifyContent: "space-around",
          flexWrap: "wrap",
        }}
      >
        <div
          style={{
            flex: 1,
            minWidth: "300px",
            height: "400px",
            margin: "10px",
          }}
        >
          <Line
            ref={chartRef}
            data={data}
            options={options}
            plugins={plugins}
          />
        </div>
        <div
          style={{
            flex: 1,
            minWidth: "300px",
            maxWidth: "400px",
            minHeight: "300px",
            maxHeight: "400px",
            margin: "10px",
            display: "flex",
            flexDirection: "column",
            justifyContent: "center",
            alignItems: "center",
          }}
        >
          {selectedGame ? (
            <>
              <Chessboard
                position={fen}
                orientation={orientation}
                key="always-black"
              />
              <div style={{ display: "flex", marginTop: "10px" }}>
                <button
                  onClick={() => handleMoveChange(-1)}
                  disabled={currentMoveIndex < 0}
                  style={{
                    marginRight: "40px",
                    border: "none",
                    background: "none",
                    color: "#999999",
                    fontSize: "40px",
                    cursor: "pointer",
                    padding: "0",
                  }}
                >
                  {"<"}
                </button>
                <button
                  onClick={() => handleMoveChange(1)}
                  disabled={
                    currentMoveIndex >= selectedGame.sequence.length - 1
                  }
                  style={{
                    border: "none",
                    background: "none",
                    color: "#999999",
                    fontSize: "40px",
                    cursor: "pointer",
                    padding: "0",
                  }}
                >
                  {">"}
                </button>
              </div>
            </>
          ) : (
            <p>No game selected.</p>
          )}
        </div>
      </div>
    </div>
  );
};

export default Lichess;

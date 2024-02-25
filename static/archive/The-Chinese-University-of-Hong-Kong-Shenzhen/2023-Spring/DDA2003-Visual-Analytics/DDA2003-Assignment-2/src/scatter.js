async function drawScatter() {
  // 1. Access data

  const dataset = await d3.json("./data/my_weather_data.json");

  // set data constants

  // Get data attributes, i.e. xAccessor for max temperature and yAccessor for min temperature (5 pts)
  xAccessor = (d) => d.temperatureMin;
  yAccessor = (d) => d.temperatureMax;

  const colorScaleYear = 2018;
  const parseDate = d3.timeParse("%Y-%m-%d");
  const colorAccessor = (d) => parseDate(d.date).setYear(colorScaleYear);

  // Create chart dimensions

  const width = d3.min([window.innerWidth * 0.75, window.innerHeight * 0.75]);
  let dimensions = {
    width: width,
    height: width,
    margin: {
      top: 90,
      right: 90,
      bottom: 50,
      left: 50,
    },
    legendWidth: 250,
    legendHeight: 26,
    marginalWidth: 14,
    marginalHeight: 90,
  };
  dimensions.boundedWidth =
    dimensions.width - dimensions.margin.left - dimensions.margin.right;
  dimensions.boundedHeight =
    dimensions.height - dimensions.margin.top - dimensions.margin.bottom;

  // Draw

  const wrapper = d3
    .select("#wrapper")
    .append("svg")
    .attr("width", dimensions.width)
    .attr("height", dimensions.height);

  const bounds = wrapper
    .append("g")
    .style(
      "transform",
      `translate(${dimensions.margin.left}px, ${dimensions.margin.top}px)`
    );

  const boundsBackground = bounds
    .append("rect")
    .lower()
    .attr("class", "bounds-background")
    .attr("x", 0)
    .attr("width", dimensions.boundedWidth)
    .attr("y", 0)
    .attr("height", dimensions.boundedHeight)
    .style("opacity", 0.15);

  // Create scales (10 pts)

  // Create scales for x, y, and color (i.e., xScale, yScale, and colorScale)

  xScale = d3
    .scaleLinear()
    .domain([0, 100])
    .range([0, dimensions.boundedWidth]);
  yScale = d3
    .scaleLinear()
    .domain([0, 100])
    .range([dimensions.boundedHeight, 0]);
  colorScale = d3
    .scaleSequential()
    .domain(d3.extent(dataset, colorAccessor))
    .interpolator(d3.interpolateRainbow);

  // 5. Draw data

  const svg = d3
    .select("svg")
    .append("g")
    .lower()
    .attr("width", dimensions.boundedWidth)
    .attr("height", dimensions.boundedHeight);

  // draw data into a scatter plot (15 pts)

  dotsGroup = svg
    .selectAll("circle")
    .data(dataset)
    .enter()
    .append("circle")
    .attr("class", "dot")
    .attr("cx", (day) => xScale(day.temperatureMin) + dimensions.margin.left)
    .attr("cy", (day) => yScale(day.temperatureMax) + dimensions.margin.top)
    .attr("r", 4)
    .style("fill", (day) => colorScale(colorAccessor(day)));

  // draw data into a density plot

  var xDensityScale = d3
    .scaleLinear()
    .domain([0, 100])
    .range([0, dimensions.boundedWidth]);
  var xDensityScale2 = d3
    .scaleLinear()
    .domain([0, 100])
    .range([dimensions.boundedHeight, 0]);
  var yDensityScale = d3.scaleLinear().domain([0, 0.02507]).range([80, 0]);
  var yDensityScale2 = d3.scaleLinear().domain([0, 0.02163]).range([80, 0]);
  var ySubDensityScale = d3.scaleLinear().domain([0, 0.35]).range([80, 0]);
  var ySubDensityScale2 = d3.scaleLinear().domain([0, 0.35]).range([80, 0]);

  function kernelDensityEstimator(kernel, X) {
    return function (V) {
      return X.map(function (x) {
        return [
          x,
          d3.mean(V, function (v) {
            return kernel(x - v);
          }),
        ];
      });
    };
  }

  function kernelEpanechnikov(k) {
    return function (v) {
      return Math.abs((v /= k)) <= 1 ? (0.75 * (1 - v * v)) / k : 0;
    };
  }

  var kde1 = kernelDensityEstimator(
    kernelEpanechnikov(5),
    xDensityScale.ticks(50)
  );
  var density = kde1(
    dataset.map(function (d) {
      return xAccessor(d);
    })
  );

  var kde2 = kernelDensityEstimator(
    kernelEpanechnikov(5),
    xDensityScale2.ticks(50)
  );
  var density2 = kde2(
    dataset.map(function (d) {
      return yAccessor(d);
    })
  );

  svg
    .append("path")
    .datum(density)
    .attr("fill", "#c0c2c2")
    .attr("stroke", "#acb0b0")
    .attr("stroke-width", 1)
    .attr("stroke-linejoin", "round")
    .attr("opacity", ".8")
    .attr(
      "d",
      d3
        .line()
        .curve(d3.curveBasis)
        .x(function (d) {
          return xDensityScale(d[0]);
        })
        .y(function (d) {
          return yDensityScale(d[1]);
        })
    )
    .style(
      "transform",
      `translate(${dimensions.margin.left}px, ${dimensions.margin.top - 90}px)`
    );

  svg
    .append("path")
    .datum(density2)
    .attr("fill", "#c0c2c2")
    .attr("stroke", "#acb0b0")
    .attr("stroke-width", 1)
    .attr("stroke-linejoin", "round")
    .attr("opacity", ".8")
    .attr(
      "d",
      d3
        .line()
        .curve(d3.curveBasis)
        .x(function (d) {
          return -xDensityScale(d[0]);
        })
        .y(function (d) {
          return yDensityScale2(d[1]);
        })
    )
    .style(
      "transform",
      `translate(
        ${dimensions.width}px,
        ${dimensions.height - dimensions.margin.bottom}px)
        rotate(90deg)`
    );

  // 6. Draw peripherals

  const xAxisGenerator = d3.axisBottom().scale(xScale).ticks(4);

  const xAxis = bounds
    .append("g")
    .call(xAxisGenerator)
    .style("transform", `translateY(${dimensions.boundedHeight}px)`);

  const xAxisLabel = xAxis
    .append("text")
    .attr("class", "x-axis-label")
    .attr("x", dimensions.boundedWidth / 2)
    .attr("y", dimensions.margin.bottom - 10)
    .html("Minimum Temperature (&deg;F)");

  const yAxisGenerator = d3.axisLeft().scale(yScale).ticks(4);

  const yAxis = bounds.append("g").call(yAxisGenerator);

  const yAxisLabel = yAxis
    .append("text")
    .attr("class", "y-axis-label")
    .attr("x", -dimensions.boundedHeight / 2)
    .attr("y", -dimensions.margin.left + 10)
    .html("Maximum Temperature (&deg;F)");

  // Set up interactions

  // create voronoi for tooltips
  const delaunay = d3.Delaunay.from(
    dataset,
    (d) => xScale(xAccessor(d)),
    (d) => yScale(yAccessor(d))
  );
  const voronoiPolygons = delaunay.voronoi();
  voronoiPolygons.xmax = dimensions.boundedWidth;
  voronoiPolygons.ymax = dimensions.boundedHeight;

  const voronoi = bounds
    .append("g")
    .selectAll(".voronoi")
    .data(dataset)
    .join("path")
    .attr("class", "voronoi")
    .attr("d", (d, i) => voronoiPolygons.renderCell(i));

  // add two mouse events in the tooltip

  voronoi
    .on("mouseenter", onVoronoiMouseEnter)
    .on("mouseleave", onVoronoiMouseLeave);

  const tooltip = d3.select("#tooltip");
  const hoverElementsGroup = bounds.append("g").attr("opacity", 0);

  const dayDot = hoverElementsGroup
    .append("circle")
    .attr("class", "tooltip-dot");

  const marginalHighlightGroup = bounds.append("g").attr("opacity", 0);
  const marginalHighlightBarX = marginalHighlightGroup
    .append("rect")
    .attr("class", "marginal-highlight-bar")
    .attr("width", dimensions.marginalWidth)
    .attr("height", dimensions.marginalHeight + 10)
    .style(
      "transform",
      `translate(
        ${0}px,
        ${-(dimensions.marginalHeight + 10)}px
      )`
    );
  const marginalHighlightBarY = marginalHighlightGroup
    .append("rect")
    .attr("class", "marginal-highlight-bar")
    .attr("width", dimensions.marginalHeight + 10)
    .attr("height", dimensions.marginalWidth)
    .style(
      "transform",
      `translate(
          ${dimensions.boundedWidth}px,
          ${0}px
        )`
    );

  function onVoronoiMouseEnter(e, datum) {
    //Given the mouse event and a datum, you are asked to highlight the data by adding an addtional circle and display its information (such as date and temperature).

    hoverElementsGroup.style("opacity", 1);
    tooltip.style("opacity", 1);
    marginalHighlightGroup.style("opacity", 1);

    dayDot.attr("r", "7.5").style(
      "transform",
      `translate(
        ${xScale(xAccessor(datum))}px,
        ${yScale(yAccessor(datum))}px
      )`
    );

    tooltip.style(
      "transform",
      `translate(
        ${xScale(xAccessor(datum)) - 90}px,
        ${yScale(yAccessor(datum) - 5)}px
      )`
    );

    // Related information is displayed when the mouse hovers to the point. (25 pts)
    tooltip
      .select("#date")
      .text(d3.timeFormat("%A, %B %e, %Y")(parseDate(datum.date)));
    tooltip.select("#min-temperature").text(datum.temperatureMin);
    tooltip.select("#max-temperature").text(datum.temperatureMax);

    marginalHighlightBarX.style(
      "transform",
      `translate(
        ${xScale(xAccessor(datum)) - 6.5}px,
        ${-(dimensions.marginalHeight + 10)}px
      )`
    );
    marginalHighlightBarY.style(
      "transform",
      `translate(
          ${dimensions.boundedWidth}px,
          ${yScale(yAccessor(datum) + 1.5)}px
        )`
    );
  }

  function onVoronoiMouseLeave(e, datum) {
    hoverElementsGroup.style("opacity", 0);
    tooltip.style("opacity", 0);
    marginalHighlightGroup.style("opacity", 0);
  }

  const legendGroup = bounds
    .append("g")
    .attr(
      "transform",
      `translate(${dimensions.boundedWidth - dimensions.legendWidth - 9},${
        dimensions.boundedHeight - 37
      })`
    );

  const defs = wrapper.append("defs");

  const numberOfGradientStops = 10;
  const stops = d3
    .range(numberOfGradientStops)
    .map((i) => i / (numberOfGradientStops - 1));
  const legendGradientId = "legend-gradient";
  const gradient = defs
    .append("linearGradient")
    .attr("id", legendGradientId)
    .selectAll("stop")
    .data(stops)
    .join("stop")
    .attr("stop-color", (d) => d3.interpolateRainbow(d))
    .attr("offset", (d) => `${d * 100}%`);

  const legendGradient = legendGroup
    .append("rect")
    .attr("height", dimensions.legendHeight)
    .attr("width", dimensions.legendWidth)
    .style("fill", `url(#${legendGradientId})`);

  const tickValues = [
    d3.timeParse("%m/%d/%Y")(`4/1/${colorScaleYear}`),
    d3.timeParse("%m/%d/%Y")(`7/1/${colorScaleYear}`),
    d3.timeParse("%m/%d/%Y")(`10/1/${colorScaleYear}`),
  ];
  const legendTickScale = d3
    .scaleLinear()
    .domain(colorScale.domain())
    .range([0, dimensions.legendWidth]);

  const legendValues = legendGroup
    .selectAll(".legend-value")
    .data(tickValues)
    .join("text")
    .attr("class", "legend-value")
    .attr("x", legendTickScale)
    .attr("y", -6)
    .text(d3.timeFormat("%b"));

  const legendValueTicks = legendGroup
    .selectAll(".legend-tick")
    .data(tickValues)
    .join("line")
    .attr("class", "legend-tick")
    .attr("x1", legendTickScale)
    .attr("x2", legendTickScale)
    .attr("y1", 6);

  // add two mouse actions on the legend
  legendGradient
    .on("mousemove", onLegendMouseMove)
    .on("mouseleave", onLegendMouseLeave);

  const legendHighlightBarWidth = dimensions.legendWidth * 0.05;
  const legendHighlightGroup = legendGroup.append("g").attr("opacity", 0);
  const legendHighlightBar = legendHighlightGroup
    .append("rect")
    .attr("class", "legend-highlight-bar")
    .attr("width", legendHighlightBarWidth)
    .attr("height", dimensions.legendHeight);

  const legendHighlightText = legendHighlightGroup
    .append("text")
    .attr("class", "legend-highlight-text")
    .attr("x", legendHighlightBarWidth / 2)
    .attr("y", -6);

  function onLegendMouseMove(e) {
    hoverElementsGroup.style("opacity", 0);
    tooltip.style("opacity", 0);

    legendValues.style("opacity", 0);
    legendValueTicks.style("opacity", 0);
    legendHighlightGroup.style("opacity", 1);

    // Display the data only when the data are in the selected date range.
    cursor = e.clientX - e.currentTarget.getBoundingClientRect().left;

    pointerScale = d3
      .scaleLinear()
      .domain([0, 250])
      .range([
        0,
        e.currentTarget.getBoundingClientRect().right -
          e.currentTarget.getBoundingClientRect().left,
      ]);

    timeScale = d3
      .scaleLinear()
      .domain(d3.extent(dataset, (d) => d.time))
      .range([0, 250]);

    intervalLength = 13.5;
    leftInterval = cursor - intervalLength / 2;
    rightInterval = cursor + intervalLength / 2;
    if (leftInterval < 0) {
      leftInterval = 0;
      rightInterval = intervalLength;
    } else if (rightInterval > 250) {
      leftInterval = 250 - intervalLength;
      rightInterval = 250;
    }

    dateLeftInterval = "2018-12-31";
    dateRightInterval = "2018-01-01";

    // Filter and visualize points when the mouse hovers to the color legend. (40 pts)

    const isDayWithinRange = (d) => {
      // Given a datum, judge whether the datum is in a datum range. Return True or False.
      if (
        leftInterval <= timeScale(d.time) &&
        timeScale(d.time) <= rightInterval
      ) {
        if (
          parseDate(d.date).getTime() < parseDate(dateLeftInterval).getTime()
        ) {
          dateLeftInterval = d.date;
        }
        if (
          parseDate(d.date).getTime() > parseDate(dateRightInterval).getTime()
        ) {
          dateRightInterval = d.date;
        }

        return true;
      } else {
        return false;
      }
    };

    dotsGroup.style("opacity", 0.075).attr("r", 4);

    dotsFiltered = dotsGroup.filter((d) => isDayWithinRange(d));
    dotsFiltered.style("opacity", 1).attr("r", 5);

    legendHighlightBar.attr(
      "transform",
      "translate(" + pointerScale(leftInterval) + ", 0)"
    );

    legendHighlightText
      .attr(
        "transform",
        "translate(" + pointerScale((leftInterval + rightInterval) / 2) + ", 0)"
      )
      .attr("text-anchor", "middle")
      .text(
        d3.timeFormat("%b %e")(parseDate(dateLeftInterval)) +
          " - " +
          d3.timeFormat("%b %e")(parseDate(dateRightInterval))
      );

    datasetFiltered = dataset.filter((d) => isDayWithinRange(d));

    var kde3 = kernelDensityEstimator(
      kernelEpanechnikov(5),
      xDensityScale.ticks(50)
    );
    var density3 = kde3(
      datasetFiltered.map(function (d) {
        return xAccessor(d);
      })
    );

    var kde4 = kernelDensityEstimator(
      kernelEpanechnikov(5),
      xDensityScale2.ticks(50)
    );
    var density4 = kde4(
      datasetFiltered.map(function (d) {
        return yAccessor(d);
      })
    );

    svg.selectAll(".subgraph").remove();

    svg
      .append("path")
      .datum(density3)
      .attr("class", "subgraph")
      .attr("fill", colorScale(colorAccessor(datasetFiltered[10])))
      .attr("stroke", "#acb0b0")
      .attr("stroke-width", 1)
      .attr("stroke-linejoin", "round")
      .attr("opacity", ".8")
      .attr(
        "d",
        d3
          .line()
          .curve(d3.curveBasis)
          .x(function (d) {
            return xDensityScale(d[0]);
          })
          .y(function (d) {
            return ySubDensityScale(d[1]);
          })
      )
      .style(
        "transform",
        `translate(
          ${dimensions.margin.left}px, 
          ${dimensions.margin.top - 90}px)`
      );

    svg
      .append("path")
      .datum(density4)
      .attr("class", "subgraph")
      .attr("fill", colorScale(colorAccessor(datasetFiltered[10])))
      .attr("stroke", "#acb0b0")
      .attr("stroke-width", 1)
      .attr("stroke-linejoin", "round")
      .attr("opacity", ".8")
      .attr(
        "d",
        d3
          .line()
          .curve(d3.curveBasis)
          .x(function (d) {
            return -xDensityScale(d[0]);
          })
          .y(function (d) {
            return ySubDensityScale2(d[1]);
          })
      )
      .style(
        "transform",
        `translate(
            ${dimensions.width}px,
            ${dimensions.height - dimensions.margin.bottom}px)
            rotate(90deg)`
      );
  }

  function onLegendMouseLeave() {
    dotsGroup.transition().duration(500).style("opacity", 1).attr("r", 4);

    svg.selectAll(".subgraph").remove();
    legendValues.style("opacity", 1);
    legendValueTicks.style("opacity", 1);
    legendHighlightGroup.style("opacity", 0);
  }
}
drawScatter();

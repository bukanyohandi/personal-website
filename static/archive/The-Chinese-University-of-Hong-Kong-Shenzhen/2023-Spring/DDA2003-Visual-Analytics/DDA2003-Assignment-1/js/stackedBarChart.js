class StackedAreaChart {
  /**
   * Class constructor with basic chart configuration
   * @param {Array}
   */
  constructor(_data) {
    this.margin = { top: 20, right: 40, bottom: 60, left: 60 };
    this.width = 1200 - this.margin.left - this.margin.right;
    this.height = 800 - this.margin.top - this.margin.bottom;
    this.displayType = "Bar";
    this.data = _data;
    this.initVis();
  }

  /**
   * Initialize scales/axes and append static chart elements
   */
  initVis() {
    let vis = this;

    // Select HTML tag, add a SVG, and set the attributes (5 pts)
    vis.svg = d3
      .select("#bar-chart")
      .attr("width", vis.width + vis.margin.left + vis.margin.right)
      .attr("height", vis.height + vis.margin.top + vis.margin.bottom);

    // Create scales for x and y axis (10 pts)
    vis.xScaleFocus = d3
      .scaleBand()
      .range([vis.margin.left, vis.width - vis.margin.right])
      .padding(0.1);
    vis.yScaleFocus = d3
      .scaleLinear()
      .rangeRound([vis.height - vis.margin.bottom, vis.margin.top]);

    // Create x and y axis (10 pts), create two groups for x and y axis, and add these groups in SVG
    vis.xAxis = d3.axisBottom(vis.xScaleFocus);
    vis.yAxis = d3.axisLeft(vis.yScaleFocus);

    // Then, add a group and make a translation.
    vis.xAxisG = vis.svg
      .append("g")
      .attr("transform", `translate(0,${vis.height - vis.margin.bottom})`)
      .attr("class", "x-axis");
    vis.yAxisG = vis.svg
      .append("g")
      .attr("transform", `translate(${vis.margin.left},0)`)
      .attr("class", "y-axis");

    // Add y label to the chart

    vis.svg
      .append("text")
      .attr("class", "ylabel")
      .attr("y", 0 - vis.margin.left + 60)
      .attr("x", 0 - vis.height / 120 + 40)
      .attr("dy", "1em")
      .attr("transform", "rotate(0)")
      .style("text-anchor", "middle")
      .text("Population");

    // Get the population under different age categories and assign color

    vis.subgroups = vis.data.columns.slice(1);

    vis.colorScale = d3
      .scaleOrdinal()
      .range([
        "#8dd3c7",
        "#ffffb3",
        "#bebada",
        "#fb8072",
        "#80b1d3",
        "#fdb462",
        "#b3de69",
      ])
      .domain(vis.subgroups);
    // color is represented by hex value (a link for the relationship among different color representations)
    // https://imagecolorpicker.com/color-code
    // Feel free to use your own color set

    // Get stacked data and sort
    // Hint: the following functions will be used during implementing this part:
    // map() and sort() functions in array and d3.stack() for stacked bar chart
    vis.find_index = new Map();
    for (var row in vis.data) {
      if (row == "columns") continue;
      vis.find_index.set(vis.data[row]["State"], parseInt(row));
    }
    vis.groups = vis.data.map(function (d) {
      return d["State"];
    });
    vis.sorted_groups = vis.data.map(function (d) {
      return d["State"];
    });
    // Sort data (10 pts)
    vis.sorted_groups.sort((a, b) =>
      vis.data[vis.find_index.get(a)].total <
      vis.data[vis.find_index.get(b)].total
        ? 1
        : -1
    ); // sort() function is used here; the sorting parameter is determined by one attribute: total
  }

  /**
   * Prepare the data and scales before we render it.
   */
  updateVis() {
    let vis = this;

    if (vis.displayType == "Sorted") {
      vis.xScaleFocus.domain(vis.sorted_groups);
      // sorted_groups is a set of states after sorting by total population
    } else {
      vis.xScaleFocus.domain(vis.groups);
      // groups is a set of states without sorting
    }
    vis.yScaleFocus.domain([
      0,
      d3.max(vis.data, function (d) {
        return d.total;
      }),
    ]);

    vis.renderVis();
  }

  /**
   * This function contains the D3 code for binding data to visual elements
   * Important: the chart is not interactive yet and renderVis() is intended
   * to be called only once; otherwise new paths would be added on top
   */
  renderVis() {
    let vis = this;

    vis.svg.selectAll("rect").remove();

    // Use D3 to generate bars and stacked bars (20pts)
    vis.stackedData = d3.stack().keys(vis.subgroups)(vis.data);

    // Visualize data and add legend based on the input option (25pts)
    if (vis.displayType == "Bar") {
      // Visualize Bar Chart
      vis.bars = vis.svg
        .selectAll("g.layer")
        .data(vis.stackedData)
        .enter()
        .append("g")
        .attr("class", "bar")
        .attr("fill", "#a8d4c4")
        .selectAll("rect")
        .data((d) => d)
        .enter()
        .append("rect")
        .attr("x", (d) => vis.xScaleFocus(d.data.State))
        .attr("y", (d) => vis.yScaleFocus(d[1]))
        .attr("height", (d) => vis.yScaleFocus(d[0]) - vis.yScaleFocus(d[1]))
        .attr("width", vis.xScaleFocus.bandwidth());
    } else if (vis.displayType == "Stacked") {
      // Visualize Stacked Bar Chart
      vis.bars = vis.svg
        .selectAll("g.layer")
        .data(vis.stackedData)
        .enter()
        .append("g")
        .attr("class", "bar")
        .attr("fill", (d) => vis.colorScale(d.index))
        .selectAll("rect")
        .data((d) => d)
        .enter()
        .append("rect")
        .attr("x", (d) => vis.xScaleFocus(d.data.State))
        .attr("y", (d) => vis.yScaleFocus(d[1]))
        .attr("height", (d) => vis.yScaleFocus(d[0]) - vis.yScaleFocus(d[1]))
        .attr("width", vis.xScaleFocus.bandwidth());
    } else if (vis.displayType == "Sorted") {
      // Visualize Sorted Stacked Bar Chart
      vis.bars = vis.svg
        .selectAll("g.layer")
        .data(vis.stackedData)
        .enter()
        .append("g")
        .attr("class", "bar")
        .attr("fill", (d) => vis.colorScale(d.index))
        .selectAll("rect")
        .data((d) => d)
        .enter()
        .append("rect")
        .attr("x", (d) => vis.xScaleFocus(d.data.State))
        .attr("y", (d) => vis.yScaleFocus(d[1]))
        .attr("height", (d) => vis.yScaleFocus(d[0]) - vis.yScaleFocus(d[1]))
        .attr("width", vis.xScaleFocus.bandwidth());
    }

    vis.xAxisG.call(vis.xAxis);
    vis.yAxisG.call(vis.yAxis);

    // Display or remove legend
    if (vis.displayType == "Bar") {
      vis.svg.selectAll("text.labels").remove();
    } else {
      vis.keys = [];
      for (var key in vis.stackedData) {
        vis.keys.push(vis.stackedData[key].key);
      }
      vis.keys.reverse();

      const size = 20;
      vis.svg
        .selectAll("dots")
        .data(vis.keys)
        .enter()
        .append("rect")
        .attr("x", vis.width - vis.margin.left - vis.margin.right + 35)
        .attr("y", function (d, i) {
          return vis.margin.top + i * (size + 5) + size / 2 - 12.5;
        })
        .attr("width", size)
        .attr("height", size)
        .style("fill", function (d) {
          return vis.colorScale(d);
        });

      vis.svg
        .selectAll("labels")
        .data(vis.keys)
        .enter()
        .append("text")
        .attr("class", "labels")
        .attr("x", vis.width - vis.margin.left - vis.margin.right + 30)
        .attr("y", function (d, i) {
          return vis.margin.top + i * (size + 5) + size / 2;
        })
        .style("fill", "black")
        .text(function (d) {
          return d;
        })
        .attr("text-anchor", "end")
        .style("alignment-baseline", "right");
    }
  }
}

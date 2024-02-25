class ForceDirectedGraph {
  /**
   * Class constructor with basic chart configuration
   * @param {Object}
   * @param {Array}
   */
  constructor(_config, _data) {
    this.config = {
      parentElement: _config.parentElement,
      containerWidth: 800,
      containerHeight: 800,
      margin: { top: 25, right: 20, bottom: 20, left: 35 },
    };
    this.data = _data;
    this.initVis();
  }

  /**
   * We initialize scales/axes and append static elements, such as axis titles.
   */
  initVis() {
    let vis = this;

    // Calculate inner chart size. Margin specifies the space around the actual chart.
    vis.config.width_l =
      vis.config.containerWidth -
      vis.config.margin.left -
      vis.config.margin.right;
    vis.config.height_l =
      vis.config.containerHeight -
      vis.config.margin.top -
      vis.config.margin.bottom;

    vis.colorScale = d3.scaleOrdinal(d3.schemeTableau10);

    // Define size of SVG drawing area
    vis.local = d3
      .select(vis.config.parentElement)
      .append("svg")
      .attr("width", vis.config.containerWidth)
      .attr("height", vis.config.containerHeight)
      .attr("id", "local");

    // Append group element that will contain our actual chart
    // and position it according to the given margin config
    vis.svg = vis.local
      .append("g")
      .attr(
        "transform",
        "translate(" +
          vis.config.margin.left +
          "," +
          vis.config.margin.top +
          ")"
      );

    d3.select("svg")
      .append("rect")
      .attr("x", 0)
      .attr("y", 0)
      .attr("width", vis.config.containerWidth)
      .attr("height", vis.config.containerHeight)
      .attr("fill", "none")
      .attr("stroke", "black")
      .attr("stroke-width", 1)
      .attr("stroke-linejoin", "round");

    // define node and link
    vis.nodes = vis.data.nodes;
    vis.links = vis.data.links;

    // define force simulation
    vis.simulation = d3
      .forceSimulation()
      .nodes(vis.nodes)
      .force(
        "link",
        d3
          .forceLink()
          .id(function (d) {
            return d.id;
          })
          .links(vis.links)
      )
      .force("charge", d3.forceManyBody().strength(-30))
      .force(
        "center",
        d3.forceCenter(vis.config.width_l / 2, vis.config.height_l / 2)
      );

    // define a tooltip for showing text

    vis.tooltip = vis.local
      .append("g")
      .selectAll("text")
      .data(vis.data.nodes)
      .join("text")
      .attr("font-size", 10);

    vis.linkedByIndex = {};

    // Build a dictionary (i.e., linkedByIndex) which will be used in isConnected function

    vis.links.forEach(function (d) {
      vis.linkedByIndex[d.source.index + "," + d.target.index] = 1;
    });

    vis.updateVis();
  }

  /**
   * Prepare the data and scales before we render it.
   */
  updateVis() {
    let vis = this;

    // Add node-link data to simulation
    vis.simulation.nodes(vis.data.nodes);
    vis.simulation.force("link").links(vis.data.links);

    // Map color to the node
    vis.colorScale.domain(vis.data.nodes.map((d) => d.group));

    vis.renderVis();
  }

  /**
   * Bind data to visual elements.
   */
  renderVis() {
    let vis = this;

    vis.selected = new Set();

    vis.widthScale = d3
      .scaleLinear()
      .domain(d3.extent(vis.links, (d) => d.value))
      .range([1, 3]);

    // Draw links
    vis.link = vis.svg
      .attr("class", "links")
      .selectAll("line")
      .data(vis.data.links)
      .enter()
      .append("line")
      .attr("x1", (d) => d.source.x)
      .attr("y1", (d) => d.source.y)
      .attr("x2", (d) => d.target.x)
      .attr("y2", (d) => d.target.y)
      .style("stroke-width", (d) => vis.widthScale(d.value));

    // Draw nodes
    vis.node = vis.svg
      .attr("class", "nodes")
      .selectAll("circle")
      .data(vis.data.nodes)
      .enter()
      .append("circle")
      .style("stroke", "black")
      .attr("cx", (d) => d.x)
      .attr("cy", (d) => d.y)
      .attr("r", 5)
      .attr("fill", (d) => vis.colorScale(d.group))
      .call(
        d3
          .drag()
          .on("start", () => {
            if (!d3.event.active) vis.simulation.alphaTarget(0.3).restart();
            d.fx = d.x;
            d.fy = d.y;
          })
          .on("drag", (d) => {
            d.fx = d3.event.x;
            d.fy = d3.event.y;
          })
          .on("end", (d) => {
            if (!d3.event.active) vis.simulation.alphaTarget(0);
            d.fx = null;
            d.fy = null;
          })
      )
      .on("mouseover", function (event, d) {
        vis.selected = new Set();
        vis.fade(d, 0.4);

        vis.tooltip
          .text(function (d) {
            if (vis.selected.has(d.index)) {
              return d.id;
            }
            return null;
          })
          .style("pointer-events", "none");

        vis.tooltip.style("opacity", 1);
      })
      .on("mouseout", function (d) {
        vis.fade(1);

        vis.tooltip.style("opacity", 0);
      });

    let nodes = [];
    vis.nodes.forEach(function (d) {
      nodes.push(d);
    });

    vis.clone = d3.selectAll("svg").node().cloneNode(true);
    d3.select(vis.clone)
      .attr("width", 200)
      .attr("height", 200)
      .attr("viewBox", `0 0 ${vis.config.width_l} ${vis.config.height_l}`)
      .attr(
        "transform",
        `translate(
          ${-200},
          ${0}
        )`
      )
      .style("pointer-events", "none");
    d3.select("svg").node().parentNode.appendChild(vis.clone);

    d3.clonedNodes = d3.select(vis.clone).selectAll("circle").data(vis.nodes);
    d3.clonedLinks = d3.select(vis.clone).selectAll("line").data(vis.links);

    vis.brush = d3
      .brush()
      .extent([
        [565, 575],
        [765, 775],
      ])
      .on("brush", function ({ selection }) {
        if (selection) {
          vis.xScale = d3.scaleLinear().domain([565, 765]).range([-35, 765]);
          vis.yScale = d3.scaleLinear().domain([575, 775]).range([-25, 775]);

          var x0 = vis.xScale(selection[0][0]);
          var x1 = vis.xScale(selection[1][0]);
          var y0 = vis.yScale(selection[0][1]);
          var y1 = vis.yScale(selection[1][1]);

          vis.x = d3.scaleLinear().domain([x0, x1]).range([-35, 765]);
          vis.y = d3.scaleLinear().domain([y0, y1]).range([-25, 775]);

          vis.compX = d3.scaleLinear().domain([184, 538]).range([230, 614]);
          vis.compY = d3.scaleLinear().domain([182, 586]).range([205, 646]);

          vis.node
            .attr("cx", (d) => vis.compX(vis.x(d.x)))
            .attr("cy", (d) => vis.compY(vis.y(d.y)));

          vis.link
            .attr("x1", (d) => vis.compX(vis.x(d.source.x)))
            .attr("y1", (d) => vis.compY(vis.y(d.source.y)))
            .attr("x2", (d) => vis.compX(vis.x(d.target.x)))
            .attr("y2", (d) => vis.compY(vis.y(d.target.y)));

          vis.tooltip
            .attr("x", (d) => vis.compX(vis.x(d.x + (43 * (x1 - x0)) / 800)))
            .attr("y", (d) => vis.compY(vis.y(d.y + (25 * (y1 - y0)) / 800)));
        }
      })
      .on("end", function ({ selection }) {});

    vis.gb = vis.svg.append("g").call(vis.brush).call(vis.brush.move);

    vis.simulation.on("tick", function ticked() {
      vis.node.attr("cx", (d) => d.x).attr("cy", (d) => d.y);

      vis.link
        .attr("x1", (d) => d.source.x)
        .attr("y1", (d) => d.source.y)
        .attr("x2", (d) => d.target.x)
        .attr("y2", (d) => d.target.y);

      vis.tooltip.attr("x", (d) => d.x + 43).attr("y", (d) => d.y + 25);

      d3.clonedNodes.attr("cx", (d) => d.x).attr("cy", (d) => d.y);

      d3.clonedLinks
        .attr("x1", (d) => d.source.x)
        .attr("y1", (d) => d.source.y)
        .attr("x2", (d) => d.target.x)
        .attr("y2", (d) => d.target.y);
    });
  }

  fade(d, opacity) {
    let vis = this;

    vis.node.style("opacity", function (o) {
      const thisOpacity = vis.isConnected(d, o) ? 1 : opacity;
      this.setAttribute("fill-opacity", thisOpacity);
      return thisOpacity;
    });

    vis.link.style("opacity", function (o) {
      return o.source === d || o.target === d ? 1 : opacity;
    });
  }

  isConnected(a, b) {
    if (
      a.index == b.index ||
      this.linkedByIndex[`${a.index},${b.index}`] ||
      this.linkedByIndex[`${b.index},${a.index}`]
    ) {
      this.selected.add(a.index);
      this.selected.add(b.index);
      return true;
    }
  }
}

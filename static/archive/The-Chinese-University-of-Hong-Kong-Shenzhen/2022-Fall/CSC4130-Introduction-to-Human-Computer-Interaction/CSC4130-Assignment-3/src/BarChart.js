class BarChart {
	constructor(_data){
	 this.margin = {top: 20, right: 20, bottom: 110, left: 40};
        this.width = 600 - this.margin.left - this.margin.right;
        this.height = 600 - this.margin.top - this.margin.bottom;

        this.data = _data;

        this.initVis();

	}

	initVis() {
		let vis = this;

		// Select HTML tag with a specific id ``bar", add a SVG container, and set the corresponding attributes.
		// Then add a group and make a translation (e.g., width and height).(5pts)		
		const bar = document.getElementById("bar");
		vis.svg = d3.select(bar).append("svg")
			.attr("width", vis.width + this.margin.left + this.margin.right)
			.attr("height", vis.height + this.margin.top + this.margin.bottom);

		// Create scales for x any y (15pts)
		vis.xScale = d3.scaleLinear().range([0, vis.width]);
		vis.xScaleFocus = d3.scaleLinear().range([0, vis.width]);
		vis.yScale = d3.scaleLinear().range([vis.height, 0]);
		vis.yScaleFocus = d3.scaleLinear().range([vis.height, 0]);

		// Place Axis (i.e., x-axis on the bottom and y-axis on the left)

		vis.xAxisFocus = d3.axisBottom(vis.xScaleFocus);

		vis.yAxisFocus = d3.axisLeft(vis.yScaleFocus);

		// Create a container in svg for drawing bar chart
		vis.focus = vis.svg.append("g")
		               .attr("transform", "translate(" + vis.margin.left + "," + vis.margin.top + ")");

		vis.focus.attr('id','focus')
		         .attr("width",vis.width)
		         .attr("height",vis.height)

		// Create Axis

		vis.xAxisFocusG = vis.focus.append('g')
		                     .attr('class', 'axis x-axis')
		                     .attr('transform', `translate(0,${vis.height})`);

		vis.yAxisFocusG = vis.focus.append('g')
		.attr('class', 'axis y-axis');

        // Create a brush variable (5pts). The "brush" variable will call brushed function
        // To determine whether a brush action is trigger, we can use d3.event.selection to judge
        // so remember to pass this variable into the brushed function
		vis.brushG = vis.focus.append("g")
						.attr("class", "brush");
		vis.brush = d3.brushX()
			.extent([[0, 0], [vis.width, vis.height]])
			.on("brush start", function(){
				vis.start_brush = 1;
			})
			.on("brush end", function(){
				vis.start_brush = 0;
				vis.brushed(d3.event.selection);
			})
			.on("brush", function(){
				if(d3.event.selection)
					vis.brushed(d3.event.selection);
			});

        // Add label for y-axis

        vis.svg.append("text")
               .attr("class", "ylabel")
               .attr("y", 0 - vis.margin.left+15)
               .attr("x", 0 - (vis.height/2))
               .attr("dy", "1em")
               .attr("transform", "rotate(-90)")
               .style("text-anchor", "middle")
               .text("Number of kWhDelivered");

	}

	updateVis(){
		let vis = this;

		// Set the domains for x axis.
		vis.xScaleFocus.domain([0, d3.max(vis.data, function(d){
			return d.kWhDelivered;
		})]);
		
		// Create a histogram (5pts) hint: D3.histogram()
		vis.histogram = d3.histogram()
			.value(function(d){
				return d.kWhDelivered;
			})
			.domain(vis.xScaleFocus.domain())
			.thresholds(vis.xScaleFocus.ticks(400));

		// Create bins from the histogram (5pts)
		vis.bins = vis.histogram(vis.data);
		
		// Set the domains for x and y axis (8pts).
		// note: domain for x is already set before creating the histogram
		vis.yScaleFocus.domain([0, d3.max(vis.bins, function(d){
			return d.length;
		})]);

		vis.renderVis();
		
	}


	renderVis(){
		let vis = this;

		// draw the bar chart from the generated bins (10 pts)
		vis.focus.selectAll("rect")
			.data(vis.bins)
			.join("rect")
			.attr("transform", function(d){
				return `translate(${vis.xScaleFocus(d.x0)} , ${vis.yScaleFocus(d.length)})`
			})
			.attr("width", function(d){
				return vis.xScaleFocus(d.x1) - vis.xScaleFocus(d.x0) - 1
			})
			.attr("height", function(d){
				return vis.height - vis.yScaleFocus(d.length);
			})
			.style("fill", "#fc3153");

		// Place x and y axis on the bottom and left, respectively
        vis.xAxisFocusG.call(vis.xAxisFocus);
        vis.yAxisFocusG.call(vis.yAxisFocus);

        // call the brush function
        vis.brushG
	        .call(vis.brush);
	}

	brushed(selection){
		let vis = this;

		if (selection) {

			//Convert given pixel coordinates (range: [x0,x1]) into a kw (domain: [number,number]) (10pts)
			if(vis.start_brush == 1){
				selection[0] = vis.xScaleFocus.invert(selection[0]);
				selection[1] = vis.xScaleFocus.invert(selection[1]);
				vis.selection = selection;
				return;
			}

			selection = vis.selection;

			vis.xAxisFocus = d3.axisBottom(vis.xScale);
			vis.yAxisFocus = d3.axisLeft(vis.yScale);

			// Update x-axis  accordingly (6pts)
			vis.xScale.domain(selection);
			
			// Based on the selected region to filter the bins (10pts) Hint: use filter() function
			vis.bins = vis.histogram(vis.data.filter(function(d){
				return selection[0] + 0.2 <= d.kWhDelivered && d.kWhDelivered <= selection[1];
			}));

			// Update y-axis accordingly
			vis.yScale.domain([0, d3.max(vis.bins, function(d){
				return d.length;
			})]);
			
			// Redraw the bar chart (10pts)		
			vis.focus.selectAll("rect")
				.data(vis.bins)
				.join("rect")
				.attr("transform", function(d){
					return `translate(${vis.xScale(d.x0)} , ${vis.yScale(d.length)})`
				})
				.attr("width", function(d){
					return vis.xScale(d.x1) - vis.xScale(d.x0) - 1
				})
				.attr("height", function(d){
					return vis.height - vis.yScale(d.length);
				})
				.style("fill", "#fc3153");

			// Update y-axis accordingly (6pts)
			// note: domain for y is already set before redrawing the histogram
			
			vis.xAxisFocusG.call(vis.xAxisFocus);
			vis.yAxisFocusG.call(vis.yAxisFocus);

		}
  }

}
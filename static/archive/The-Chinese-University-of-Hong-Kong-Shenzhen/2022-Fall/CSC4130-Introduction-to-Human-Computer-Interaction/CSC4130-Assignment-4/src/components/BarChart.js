import React from 'react';
import * as d3 from 'd3';
import { filter } from 'd3';

const BarChart = ({
    config:{
        colorScale,
        containerWidth,
        containerHeight,
        margin
    },
    data,
    setFilterCategory,
}) => {

    const svgRef = React.useRef();

    const chart = React.useRef();
    const xAxisG = React.useRef();
    const yAxisG = React.useRef();
    const bars = React.useRef();

    // These calculated intermidiate data should be
    // cleaned up to React-styled code.
    // that is, to combine all below refs and the "initialized" state into a single state
    const _colorScale = React.useRef();
    const width = React.useRef();
    const height = React.useRef();
    const xScale = React.useRef();
    const yScale = React.useRef();
    const xAxis = React.useRef();
    const yAxis = React.useRef();
    const _containerWidth = React.useRef();
    const _containerHeight = React.useRef();
    const [ initialized, setInitialized ] = React.useState(false)

    // Cannot dynamically change. If dynamically chaning is needed, these code can be modified.
    const _margin = React.useRef();
    const orderedKeys = ['Easy', 'Intermediate', 'Difficult'];

    // Intialize the bar plot (5pts)
    React.useEffect(()=>{
        initVis();
    }, []);

    // Update rendering result (5pts)
    React.useEffect(()=>{
        updateVis();
    }, [data]);

    const initVis = () => {
        let svg = d3.select(svgRef.current);
        _containerWidth.current = containerWidth || 260;
        _containerHeight.current =  containerHeight || 300;
        svg.attr('width', _containerWidth.current).attr('height', _containerHeight.current);
        _margin.current = margin || {top: 25, right: 20, bottom: 20, left: 40};
        width.current = _containerWidth.current - _margin.current.left - _margin.current.right;
        height.current = _containerHeight.current - _margin.current.top - _margin.current.bottom;
        xScale.current = d3.scaleBand().range([0, width.current]).paddingInner(0.2);
        yScale.current = d3.scaleLinear().range([height.current, 0]);
        xAxis.current = d3.axisBottom(xScale.current).ticks(['Easy', 'Intermediate', 'Difficult']).tickSizeOuter(0);
        yAxis.current = d3.axisLeft(yScale.current).ticks(6).tickSizeOuter(0);
        chart.current = svg.append('g').attr('transform', `translate(${_margin.current.left},${_margin.current.top})`);
        xAxisG.current = chart.current.append('g').attr('class', 'axis x-axis').attr('transform', `translate(0,${height.current})`);
        yAxisG.current = chart.current.append('g').attr('class', 'axis y-axis');
        svg.append('text').attr('class', 'axis-title').attr('x', 0).attr('y', 0).attr('dy', '.71em').text('Trails');

        _colorScale.current = d3.scaleOrdinal()
            .range(['#a0a1e2', '#6495ed', '#04ea17']) // light green to dark green
            .domain(['Easy','Intermediate','Difficult']);

        setInitialized(true);
    }

    const updateVis = () => {
        const aggregatedDataMap = d3.rollups(data, v => v.length, d => d.difficulty);
        let aggregatedData = Array.from(aggregatedDataMap, ([key, count]) => ({ key, count }));
        aggregatedData = aggregatedData.sort((a,b) => {
            return orderedKeys.indexOf(a.key) - orderedKeys.indexOf(b.key);
        });
        let colorValue = d => d.key;
        let xValue = d => d.key;
        let yValue = d => d.count;

        xScale.current.domain(aggregatedData.map(xValue))
        yScale.current.domain([0, d3.max(aggregatedData, yValue)]);


        // renderVis()
        bars.current = chart.current.selectAll('.bar')
        .data(aggregatedData, xValue)
        .join('rect')
        .attr('class', 'bar')
        .attr('x', d => xScale.current(xValue(d)))
        .attr('width', xScale.current.bandwidth())
        .attr('height', d => height.current - yScale.current(yValue(d)))
        .attr('y', d => yScale.current(yValue(d)))
        .attr('fill', d => _colorScale.current(colorValue(d)))
        .on('click', function(event, d) {

            // Check if current category is active and toggle class (5pts)
            var categoryKey = orderedKeys.indexOf(d.key);
            setFilterCategory(categoryKey);
            /* This automatically updates the filterCategory; hence, useEffect will be called */

            // Get the names of all active/filtered categories (10pts)
            /* This part is also done inside useEffect in App.js */
            
            // Change parent node's React State with the selected category names (5pts)
            /* This part is also done inside useEffect in App.js */
            
            /* stylize click action */
            var strokeValue = d3.select(this)
                .attr("stroke");
                
            if(strokeValue == "#848485"){
                d3.select(this)
                    .attr("stroke", "black")
                    .attr("stroke-width", 1.2);
            } else {
                d3.select(this)
                    .attr("stroke", "#FFFFFE")
                    .attr("stroke-width", 0);
            }
        })
        .on("mouseover", function(event, d){
            /* stylize hover action */
            const categoryColor = ["#898ACE", "#5B8AE0", "#0BB91A"];
            var categoryKey = orderedKeys.indexOf(d.key);

            d3.select(this)
                .transition()
                .duration("400")
                .attr("fill", categoryColor[categoryKey]);
                
            var strokeValue = d3.select(this)
                .attr("stroke");

            if(strokeValue == "black"){
                d3.select(this)
                    .attr("stroke", "#848484")
                    .attr("stroke-width", 2.5);
            } else {
                d3.select(this)
                    .attr("stroke", "#848485")
                    .attr("stroke-width", 2.5);
            }
        })
        .on("mouseleave", function(event, d){
            /* stylize hover action */
            const categoryColor = ["#a0a1e2", "#6495ed", "#04ea17"];
            var categoryKey = orderedKeys.indexOf(d.key);

            d3.select(this)
                .transition()
                .duration("100")
                .attr("fill", categoryColor[categoryKey]);

            var strokeValue = d3.select(this)
                .attr("stroke");
            
            if(strokeValue == "#848484"){
                d3.select(this)
                    .attr("stroke", "black")
                    .attr("stroke-width", 1.2);
            } else if(strokeValue == "#848485"){
                d3.select(this)
                    .attr("stroke", "#FFFFFE")
                    .attr("stroke-width", 0);
            } else if(strokeValue == "#FFFFFF"){
                d3.select(this)
                    .attr("stroke", "black")
                    .attr("stroke-width", 1.2);
            }
        });

        xAxisG.current.call(xAxis.current);
        yAxisG.current.call(yAxis.current);
    }

    return (
        <svg ref={svgRef}></svg>
    );
}

export default BarChart;
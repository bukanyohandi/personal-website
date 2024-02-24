import logo from './logo.svg';
import './App.css';
import BarChart from './components/BarChart';
import * as d3 from 'd3';
import React, { useState } from 'react';
import ScatterPlot from './components/ScatterPlot';
import { filter } from 'd3';

var filterState = 0; // filterState & (1 << x) == true means the category x is currently selected
const orderedKeys = ['Easy', 'Intermediate', 'Difficult']; // constants

function App() {
    // Create three states, i.e., data, selectedData, and filterCategory
    const [data, setData] = React.useState([]);
    const [selectedData, setSelectedData] = React.useState([]);
    const [filterCategory, setFilterCategory] = React.useState(-1);

    const colorScale = d3.scaleOrdinal()
        .range(['#d3eecd', '#7bc77e', '#2a8d46']) 
        .domain(['Easy','Intermediate','Difficult']);

    React.useEffect(()=>{
        loadData();
    },[])

    const loadData = () => {
        d3.csv('./vancouver_trails.csv') 
        .then(_data => {
            setData(_data.map(d => {
                d.time = +d.time;
                d.distance = +d.distance;
                return d
            }));
            
            // Init for selectedData as well
            setSelectedData(_data.map(d => {
                d.time = +d.time;
                d.distance = +d.distance;
                return d
            }));
        })
    }

    // Use useEffect to render and update visual results when dependency/dependencies change (30pts)
    React.useEffect(()=>{
        if(filterCategory != -1){
            // Check if current category is active and toggle class
            // Change parent node's React State with the selected category names
            filterState ^= (1 << filterCategory);
            setFilterCategory(-1);

            // Get the names of all active/filtered categories
            if(filterState == 0 || filterState == 7){
                console.log("Easy, Intermediate, Difficult");

                setSelectedData(data);
            } else {
                let selectedCategories = "";
                if(filterState & (1 << 0)) selectedCategories += ", Easy";
                if(filterState & (1 << 1)) selectedCategories += ", Intermediate";
                if(filterState & (1 << 2)) selectedCategories += ", Difficult";
                console.log(selectedCategories.substring(2));

                setSelectedData(data.filter(function(d){
                    return filterState & (1 << (orderedKeys.indexOf(d.difficulty)));
                }));
            }
        }
    }, [filterCategory])

    return (
        <div className='Container'>
        <h1 className='head'> Multiple-View Interaction </h1>
        <div className="App">
        <ScatterPlot config={colorScale} data = {selectedData}/>
        <BarChart config={colorScale} data = {data} setFilterCategory={setFilterCategory}/>
        </div>
        </div>
    );
}

export default App;

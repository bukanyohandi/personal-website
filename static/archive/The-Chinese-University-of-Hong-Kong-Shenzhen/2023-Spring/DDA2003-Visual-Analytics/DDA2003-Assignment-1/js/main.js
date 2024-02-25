// Initialize helper function

let data, stackedBarChart;

/**
 * Load data from CSV file asynchronously and render area chart
 */
d3.csv("data/A1_Data.csv").then((_data) => {
  // get the keys from the data and compute the total population (you are required to use sum function) (10 pts)
  for (var row in _data) {
    if (row == "columns") continue;
    var state_population = [];
    for (var keys in _data["columns"]) {
      if (_data["columns"][keys] == "State") continue;
      state_population.push(_data[row][_data["columns"][keys]]);
    }

    _data[row].total = d3.sum(state_population); // sum() function is used here
  }

  data = _data;

  // Initialize and render chart
  stackedBarChart = new StackedAreaChart(data);
  stackedBarChart.updateVis();
});

/**
 * Select box event listener
 */

//
d3.select("#display-type-selection").on("change", function () {
  // Get selected display type and update chart
  stackedBarChart.displayType = d3.select(this).property("value");
  stackedBarChart.updateVis();
});

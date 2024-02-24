 d3.json("./data/acndata_sessions.json").then(data => {
  items = data["_items"];
  barchart = new BarChart(items);
  barchart.updateVis();
 });
window.addEventListener('load', ()=>{
    document.addEventListener('click', click);    
    document.addEventListener('mousedown', startdrawormove);
    document.addEventListener('mouseup', stopdrawormove);
    document.addEventListener('mousemove', sketch);
});

var canvas = new fabric.Canvas("canvas");
var isDown, origX, origY;

var colorinput = document.getElementById("favcolor");
var slider = document.getElementById("opacity");
var output_o = document.getElementById("value");
var colorvalue = document.getElementById("colorVal");

output_o.innerHTML = slider.value;
colorvalue.innerHTML = colorinput.value;

var tooltype = "draw";
var shapetype = "circle";

const shapes = [];

function click(event){ 
  var draw_button = document.getElementById("draw_button");
  var move_button = document.getElementById("move_button");
  var reset_button = document.getElementById("reset_button");

  // if users click reset, clear all shapes in the interface (10pts)
  if(tooltype == "reset"){
    draw_button.disabled = false;
    move_button.disabled = false;
    reset_button.disabled = true;

    for(var i = 0; i < shapes.length; ++i){
      canvas.remove(shapes[i]);
    }
    shapes = [];
  }

  if(tooltype == "draw"){
    canvas.discardActiveObject();
    canvas.renderAll();

    draw_button.disabled = true;
    move_button.disabled = false;
  } else if(tooltype == "move") {
    draw_button.disabled = false;
    move_button.disabled = true;
  }
}

var current_shape;

function startdrawormove(event) {
  isDown = true;
  var pointer = canvas.getPointer(event); // get mouse position
  origX = pointer.x;
  origY = pointer.y;

  if (tooltype == "draw"){
    for(var i = 0; i < shapes.length; ++i){
      shapes[i].selectable = false;
      shapes[i].lockMovementX = true;
      shapes[i].lockMovementY = true;
    }

    //Use fabric.Circle/Rect/Triangle to define a circle/rectangle/triangle, respectively. Each shape is for 9pts
    if(shapetype == "circle"){
      current_shape = new fabric.Circle({
        radius: 0,
        hasControls: false
      });
    } else if(shapetype == "rectangle"){
      current_shape = new fabric.Rect({
        width: 0,
        height: 0,
        hasControls: false
      });
    } else if(shapetype == "triangle"){
      current_shape = new fabric.Triangle({
        width: 0,
        height: 0,
        hasControls: false
        // lockScalingX: true,
        // lockScalingY: true,
        // lockRotation: false
      });
    }

    current_shape.fill = document.getElementById("favcolor").value;
    
    current_shape.selectable = false;
    current_shape.opacity = slider.value;
    current_shape.lockMovementX = true;
    current_shape.lockMovementY = true;

    // add the defined shape into canvas (3pts).
    shapes.push(current_shape);
    canvas.add(current_shape);

    canvas.renderAll();
  }
  else if (tooltype == "move"){
    // make all shapes selectable (4pts).
    for(var i = 0; i < shapes.length; ++i){
      shapes[i].selectable = true;
      shapes[i].lockMovementX = false;
      shapes[i].lockMovementY = false;
    }
  }
    
}

function stopdrawormove(event){
  isDown = false;

  var reset_button = document.getElementById("reset_button");
  reset_button.disabled = false;
}

function sketch(event){
  if (tooltype == "draw"){
    if (!isDown) return;

    var pointer = canvas.getPointer(event); 
    if (shapetype == "circle"){
      // set the circle radius based on the mouse position (6pts)
      current_shape.set({
        radius: Math.min(Math.abs(pointer.x - origX), Math.abs(pointer.y - origY)) / 2
      });

      if(pointer.x <= origX && pointer.y <= origY){
        current_shape.set({ left: origX - 2 * current_shape.radius });
        current_shape.set({ top: origY - 2 * current_shape.radius });
      } else if(pointer.x <= origX){
        current_shape.set({ left: origX - 2 * current_shape.radius });
        current_shape.set({ top: origY });
      } else if(pointer.y <= origY){
        current_shape.set({ left: origX });
        current_shape.set({ top: origY - 2 * current_shape.radius });
      } else {
        current_shape.set({ left: Math.min(pointer.x, origX) });
        current_shape.set({ top: Math.min(pointer.y, origY) });
      }
      console.log(current_shape.left, current_shape.top);
      current_shape.setCoords();
    }
    else {
      // set the width and height of rectangle or triangle based on the mouse position (6pts)
      current_shape.set({
        width: Math.abs(origX - pointer.x),
        height: Math.abs(origY - pointer.y)
      });
      current_shape.set({ left: Math.min(pointer.x, origX) });
      current_shape.set({ top: Math.min(pointer.y, origY) });
      current_shape.setCoords();
    }

    canvas.renderAll();
  }
  else if (tooltype == "move"){
    var pointer = canvas.getPointer(event);

    // move the selected shape  hint: use getActiveObject() function(8pts)
    /* your code is here */
  }

  // get all shapes from canvas (6pts) and change the opacity of each shape (6pts)
  for(var i = 0; i < shapes.length; ++i){
    shapes[i].opacity = slider.value;
  }

  canvas.renderAll();
}

function select_shape(shape){
  shapetype = shape.value;
}

function use_tool(tool){
  tooltype = tool;
}

slider.oninput = function() {
  output_o.innerHTML = this.value;
}

colorinput.oninput = function() {
  colorvalue.innerHTML = this.value;
}



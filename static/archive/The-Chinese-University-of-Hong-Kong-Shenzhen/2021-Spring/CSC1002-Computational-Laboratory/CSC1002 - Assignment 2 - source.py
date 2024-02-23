import random
import time
import turtle

#Global Constant
backgroundColor = "DarkSeaGreen"
centerPosition = (0, -40)
distanceDistribution = 100
foodColor = ["Blue", "DarkCyan", "DarkGoldenRod", "DarkRed", "DarkOrange", "DarkOrchid", "DarkTurquoise", "DeepPink", "GreenYellow"]
foodOuter = "Black"
foodShape = "square"
foodTotal = 9
lowerMotion = [(-250, -290), (250, -290), (250, 210), (-250, 210)]
monsterInner = "Tomato"
monsterOuter = "Black"
monsterShape = "square"
monsterSpeed = random.randint(200, 350)
screenHeight = 740
screenWidth = 660
snakeBodyInner = "DimGrey"
snakeBodyOuter = "Black"
snakeHeadOuter = "Black"
snakeHeadShape = "square"
upperStatus = [(-250, 210), (250, 210), (250, 290), (-250, 290)]

#Global Variable
contactCount = 0
description = ""
foodConsumed = []
foodPosition = []
foodTurtle = [None] * foodTotal
monster = turtle.Turtle()
onGoing = True
screen = turtle.Screen()
snakeBodyPosition = []
snakeHead = turtle.Turtle()
snakeHeadInner = "SpringGreen"
snakeLastDirection = "pause"
snakeLastMove = "pause"
snakeLength = 6
snakePause = False
snakeSpeed = 200
text = turtle.Turtle()
textContact = turtle.Turtle()
textMotion = turtle.Turtle()
textTime = turtle.Turtle()
toggleStatus = 1

#Mouse click
def click(clickX, clickY):
    #Remove description
    text.clear()
    
    #Generate 9 random empty positions for food and display it
    generateFood(foodTotal)

    screen.onclick(None)
    screen.ontimer(snakeMove, snakeSpeed)
    screen.ontimer(monsterMove, monsterSpeed)
    
    while True:
        screen.update()

#Draw a line from (point1_x, point1_y) to (point2_x, point2_y)
def drawLine(point1, point2):
    turtle.speed(1024)
    turtle.penup()
    turtle.goto(point1)
    turtle.pendown()
    turtle.goto(point2)
    turtle.hideturtle()

#Draw polygon from a set of points
def drawPolygon(points): 
    for i in range(len(points)):
        drawLine(points[i], points[i - 1])

#Generate n foods with distance distribution
def generateFood(n): 
    global foodPosition
    foodPosition = [centerPosition, (monster.xcor(), monster.ycor())]
    while len(foodPosition) != (n + 2):
        x = random.randint(-225, 225)
        y = random.randint(-265, 185)
        valid = True
        for position in foodPosition:
            if manhattanDistance((x, y), position) <= distanceDistribution:
                valid = False
        if valid:
            foodPosition.append((x, y))
    foodPosition = foodPosition[2:]
    toggleScreen()
    for number in range(n):
        foodTurtle[number] = turtle.Turtle()
        foodTurtle[number].penup()
        foodTurtle[number].goto(foodPosition[number])
        foodTurtle[number].shape(foodShape)
        foodTurtle[number].write(number + 1, font = ("sans", 12, "normal"), align = "center")
        foodTurtle[number].color(foodOuter, foodColor[number])
        foodTurtle[number].turtlesize(0.25)
    toggleScreen()

#Check whether point is inside the motion area
def insideMotionArea(point):
    return (-250 < point[0] < 250) and (-290 < point[1] < 210)

#Check the Manhattan Distance between point1 and point2
def manhattanDistance(point1, point2):
    return abs(point1[0] - point2[0]) + abs(point1[1] - point2[1])

#Move monster to approach the head of snake randomly in vertical direction or the horizontal direction
def monsterMove():
    #Detect and increase the count of body contact when monster is overlapping 
    def contact():
        global contactCount, monster, snakeBodyPosition
        for point in snakeBodyPosition:
            if manhattanDistance(point, monster.position()) <= 20:
                contactCount += 1
                return
    #Change the vector length to the default size (20) with maintaining the same direction
    def setMove(length):
        return 20 * ((length + 1) / abs(length + 1))
    global monster, onGoing, screen, snakeHead
    if not onGoing:
        return
    dx = monster.xcor() - snakeHead.xcor()
    dy = monster.ycor() - snakeHead.ycor()
    moves = []
    if insideMotionArea((monster.xcor() - setMove(dx), monster.ycor())):
        moves.append((-setMove(dx), 0))
    if insideMotionArea((monster.xcor(), monster.ycor() - setMove(dy))):
        moves.append((0, -setMove(dy)))
    dx, dy = random.choice(moves)
    monster.goto((monster.xcor() + dx, monster.ycor() + dy))
    contact()
    screen.ontimer(monsterMove, monsterSpeed)

#Alterate snake's head direction toward the "down" direction
def snakeDown():
    if not snakePause and snakeLastMove in ["left", "right", "pause"]:
        snakeHead.direction = "down"

#Alterate snake's head direction toward the "left" direction
def snakeLeft():
    if not snakePause and snakeLastMove in ["down", "up", "pause"]:
        snakeHead.direction = "left"

#Move snake according to the last pressed key by user
def snakeMove():
    #"consume" and remove the food when the distance between snake's head and food is less than the default size
    def consumeFood():
        global foodColor, foodConsumed, foodTotal, snakeHead, snakeHeadInner, snakeLength
        for number in range(foodTotal):
            if manhattanDistance(snakeHead.position(), foodPosition[number]) <= 20 and number not in foodConsumed:
                foodTurtle[number].clear()
                foodTurtle[number].hideturtle()
                snakeHeadInner = foodColor[number]
                snakeLength += number + 1
                foodConsumed.append(number)
    #Replicate the current snake's head as its own body with stamp and move its head
    def snakeBodyMove():
        global snakeBodyPosition, snakeHead, snakeLength, snakeSpeed
        snakeBodyPosition.append(snakeHead.position())
        snakeHead.color(snakeBodyOuter, snakeBodyInner)
        snakeHead.stamp()
        snakeHead.color(snakeHeadOuter, snakeHeadInner)
        if snakeLength <= len(snakeHead.stampItems):
            snakeHead.clearstamps(1)
            snakeBodyPosition = snakeBodyPosition[1:]
            snakeSpeed = 200
        else:
            snakeSpeed = 400
    #Status update (include the body contact, the current motion, and total time)
    def statusUpdate():
        global foodConsumed, foodTotal, monster, onGoing, snakeHead
        if len(snakeHead.stampItems) == 50:
            writeMessage(snakeHead.position(), snakeHeadInner, "WINNER!!!")
            onGoing = False
            toggleScreen()
            turtle.done()
        elif snakeHead.distance(monster) <= 20:
            writeMessage(snakeHead.position(), monsterInner, "GAMEOVER!!!")
            onGoing = False
            toggleScreen()
            turtle.done()
        textContact.clear()
        textMotion.clear()
        textTime.clear()
        textContact.write("Contact: " + str(contactCount), font = ("arial", 14, "normal"), align = "center")
        if snakePause == True:
            textMotion.write("Motion: Pause", font = ("arial", 14, "normal"), align = "center")
        else:
            textMotion.write("Motion: " + str(snakeLastMove).capitalize(), font = ("arial", 14, "normal"), align = "center")
        textTime.write("Time: " + str(int(time.perf_counter())), font = ("arial", 14, "normal"), align = "center")
    #Write a "message" at "point" location with customized color
    def writeMessage(point, color, message):
        text = turtle.Turtle()
        text.speed(1024)
        text.penup()
        text.goto(point[0], point[1] + 20)
        text.color(color)
        text.write(message, font = ("arial", 12, "bold"), align = "center")
        text.hideturtle()
    global screen, snakeHead, snakeLastMove
    toggleScreen()
    if onGoing and not snakePause:
        dx, dy = {"down" : (0, -20), "left" : (-20, 0), "right" : (20, 0), "up" : (0, 20), "pause" : (0, 0)}[snakeHead.direction]
        if insideMotionArea((snakeHead.xcor() + dx, snakeHead.ycor() + dy)):
            snakeLastMove = snakeHead.direction
            snakeBodyMove()
            snakeHead.goto(snakeHead.xcor() + dx, snakeHead.ycor() + dy)
        else:
            snakeHead.direction = snakeLastMove
    consumeFood()
    statusUpdate()
    toggleScreen()
    screen.ontimer(snakeMove, snakeSpeed)

#Alterate snake's head direction toward the "right" direction
def snakeRight():
    if not snakePause and snakeLastMove in ["down", "up", "pause"]:
        snakeHead.direction = "right"

#Toggle the pause state (on to off /  off to on)
def snakeTogglePause():
    global snakeLastDirection, snakePause
    snakePause ^= True
    if snakeHead.direction == "pause":
        snakeHead.direction = snakeLastDirection
    else:
        snakeLastDirection = snakeHead.direction
        snakeHead.direction = "pause"

#Alterate snake's head direction toward the "up" direction
def snakeUp():
    if not snakePause and snakeLastMove in ["left", "right", "pause"]:
        snakeHead.direction = "up"

#Toggle the screen tracer (0 to 1 / 1 to 0)
def toggleScreen():
    global toggleStatus
    toggleStatus = 1 - toggleStatus
    screen.tracer(toggleStatus)

if __name__ == "__main__":

    #Screen setup
    screen.setup(width = screenWidth, height = screenHeight)
    screen.bgcolor(backgroundColor)

    toggleScreen()

    #Introduction
    text.hideturtle()
    text.penup()
    text.goto(-225, 50)
    text.write( "Welcome to Yohandi's version of snake ....\n" + \
                "\n" + \
                "To win this game, you have to consume all of the " + str(foodTotal) + " foods before you\n" + \
                "get caught by the monster. Use the [Up], [Down], [Left], and [Right]\n" + \
                "keys to direct the snake. To pause the game, use the [Space] key.\n" + \
                "\n" + \
                "Good luck, have fun! (click anywhere to start)\n",
                font = ("arial", 12, "normal"))

    #Upper status area
    drawPolygon(upperStatus)
    
    #Lower motion area
    drawPolygon(lowerMotion)

    #Initialize monster
    monster.penup()
    while manhattanDistance((monster.position()), centerPosition) <= distanceDistribution ** 1.2:
        monster.goto(random.randint(-11, 12) * 20 - 10, random.randint(-13, 10) * 20 - 10)
    monster.shape(monsterShape)
    monster.color(monsterOuter, monsterInner) 

    #Initialize snake's head
    snakeHead.penup()
    snakeHead.goto(centerPosition)
    snakeHead.shape(snakeHeadShape)
    snakeHead.color(snakeHeadOuter, snakeHeadInner)
    snakeHead.direction = "pause"
    
    #Initialize keys binding
    screen.onkey(snakeDown, "Down")
    screen.onkey(snakeLeft, "Left")
    screen.onkey(snakeRight, "Right")
    screen.onkey(snakeUp, "Up")
    screen.onkey(snakeTogglePause, "space")
    screen.listen()

    #Initialize text status
    textContact.penup()
    textContact.hideturtle()
    textContact.goto(-150, 245)
    textMotion.penup()
    textMotion.hideturtle()
    textMotion.goto(0, 245)
    textTime.penup()
    textTime.hideturtle()
    textTime.goto(150, 245)

    toggleScreen()

    #Game
    screen.title("Color Snake by Yohandi")
    screen.onclick(click)

    screen.mainloop()

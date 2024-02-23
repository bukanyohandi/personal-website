from os import system, name
import random
import sys
import time

def clearScreen():
    if name == 'nt':
        _ = system('cls')
    else:
        _ = system('clear')
    return

def fakeLoading(description):
    print(description, end = "")
    bar = "....."
    for c in bar:
        time.sleep(0.5)
        sys.stdout.write(c)
        sys.stdout.flush()
    time.sleep(0.3)
    print("")
    clearScreen()
    return

def printDelay(description):
    print(description)
    time.sleep(1.5)
    return

def blankCoordinate():
    global N, gridPuzzle
    for i in range(N):
        for j in range(N):
            if gridPuzzle[i][j] == 0:
                return i, j

def isComplete():
    global N, gridPuzzle
    return gridPuzzle == [[(x + y * N + 1) % (N * N) for x in range(N)] for y in range(N)]

def isComplete1D():
    global N, gridPuzzle, gridPuzzle1D
    return gridPuzzle1D == [x for x in range(N * N)]

def inputPrompt(description):
    while True:
        inp = input(description)
        try:
            if int(inp) < 3:
                print("Whoops! N should be larger or equal to 3!")
            elif int(inp) > 10:
                print("Whoops! N should be smaller or equal to 10!")
            else:
                return int(inp)
        except ValueError:
            pass

def inputKeybindMovePrompt(description):
    global moves
    while True:
        inp = input(description)
        if len(inp.split()) == 4:
            ok = True
            for i in inp.split():
                if len(i) != 1:
                    ok = False
            if ok:
                moves = inp.split()
                print(moves)
                return
            else:
                print("Whoops! Each keybind should be a letter!")
        else:
            print("Whoops! You should enter 4 letters each separated by a space!")

def inputMovePrompt():
    global moves
    x, y = blankCoordinate()
    description = "Enter your move (Exit - exit, Reset - reset"
    if x < N - 1 :
        description += ", Up - " + str(moves[0])
    if y > 0 :
        description += ", Right - " + str(moves[1])
    if x > 0 :
        description += ", Down - " + str(moves[2])
    if y < N - 1 :
        description += ", Left - " + str(moves[3])
    description += ")!\n"
    while True:
        printPuzzle()
        inp = input(description)
        for i in range(6):
            if inp == moves[i]:
                return i

def moveUp():
    global N, gridPuzzle
    x, y = blankCoordinate()
    if x + 1 < N: gridPuzzle[x][y], gridPuzzle[x + 1][y] = gridPuzzle[x + 1][y], gridPuzzle[x][y]
    return

def moveRight():
    global N, gridPuzzle
    x, y = blankCoordinate()
    if y - 1 >= 0: gridPuzzle[x][y], gridPuzzle[x][y - 1] = gridPuzzle[x][y - 1], gridPuzzle[x][y]
    return

def moveDown():
    global N, gridPuzzle
    x, y = blankCoordinate()
    if x - 1 >= 0: gridPuzzle[x][y], gridPuzzle[x - 1][y] = gridPuzzle[x - 1][y], gridPuzzle[x][y]
    return

def moveLeft():
    global N, gridPuzzle
    x, y = blankCoordinate()
    if y + 1 < N: gridPuzzle[x][y], gridPuzzle[x][y + 1] = gridPuzzle[x][y + 1], gridPuzzle[x][y]
    return

def proceed(description):
    while True:
        clearScreen()
        inp = input(description)
        if inp == "y":
            return True
        elif inp == "n":
            return False

def totalInversion():
    global N, gridPuzzle, gridPuzzle1D
    total = 0
    for i in range(0, N * N - 1):
        for j in range(i + 1, N * N):
            if gridPuzzle1D[j] > 0 and gridPuzzle1D[i] > 0 and gridPuzzle1D[i] > gridPuzzle1D[j]:
                total += 1
    return total

def isSolvable():
    global N
    x, y = blankCoordinate()
    if N % 2 == 0:
        return (totalInversion() + N - x) % 2 == 1
    else:
        return (totalInversion()) % 2 == 0

def generateRandomPuzzle():
    global N, gridPuzzle, gridPuzzle1D
    while isComplete1D() or not(isSolvable()):
        gridPuzzle1D = random.sample(gridPuzzle1D, N * N)
        for i in range(N):
            for j in range(N):
                gridPuzzle[i][j] = gridPuzzle1D[i * N + j]
    return

def printPuzzle():
    global N, gridPuzzle
    clearScreen()
    for i in range(N):
        for j in range(N):
            if gridPuzzle[i][j] == 0:
                print(end = "   ")
            elif gridPuzzle[i][j] < 10:
                print(gridPuzzle[i][j], end = "  ")
            else:
                print(gridPuzzle[i][j], end = " ")
            print(end = " ")
        print("")
    return

cast = [moveUp, moveRight, moveDown, moveLeft]
message = [ 
    "Artfully headaches!",        
    "In this game, you ought to push the pieces around over the board until the picture is complete.",
    "The pieces are numbered so that you will know in which order they should be.",
    "You can only move each piece if they share the same side with the blank one.",
    "The piece marked 1 should be in the upper left corner of the slide puzzle.",
    "This is how the pieces should be arranged when the puzzle is solved:",
    "1  2  3  4\n5  6  7  8\n9  10 11 12\n13 14 15"
]
clearScreen()
print("Welcome to Yohandi's Sliding Puzzle", end = "")
fakeLoading("")
for i in message:
    printDelay(i)
input("Press [Enter] to play the game!")
while True:
    clearScreen()
    fakeLoading("Loading")
    print("Enter the desired dimension of the puzzle N x N! (3 <= N <= 10)")
    N = inputPrompt("N = ")
    moves = []
    clearScreen()
    inputKeybindMovePrompt("Enter your custom keybind settings for Up, Right, Down, and Left respectively = ")
    moves.append("exit")
    moves.append("reset")
    gridPuzzle = [[(x + y * N + 1) % (N * N) for x in range(N)] for y in range(N)]
    gridPuzzle1D = [x for x in range(N * N)]
    generateRandomPuzzle()
    reset = False
    countMoves = 0
    while(not(isComplete())):
        inp = inputMovePrompt()
        if inp < 4:
            cast[inp]()
            countMoves += 1
        elif inp == 4:
            if proceed("Are you sure want to quit? [y/n]\n"):
                print("Good bye!")
                time.sleep(2)
                exit()
        else:
            reset = proceed("Are you sure want to reset the game? [y/n]\n")
        if reset:
            break
    if reset:
        continue
    printPuzzle()
    time.sleep(1)
    clearScreen()
    print("Congratulations, you just solved the puzzle in", countMoves, "moves!")
    time.sleep(1.5)
    while True:
        inp = input("Enter [P] or [p] to play again, [X] or [x] to exit!\n")
        if inp in ["P", "p"]:
            break
        elif inp in ["X", "x"]:
            clearScreen()
            print("Good bye!")
            time.sleep(2)
            exit()
        else:
            print("Whoops! Not that button, fella!")
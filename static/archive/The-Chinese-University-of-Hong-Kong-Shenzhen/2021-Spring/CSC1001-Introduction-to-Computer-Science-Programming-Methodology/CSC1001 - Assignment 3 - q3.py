import random

class Ecosystem:
    def __init__(self, riverLength, numberFishes, numberBears):
        self.__currentStep = 0
        self.__pendingBirth = []
        self.__riverLength = riverLength
        self.__numberFishes = numberFishes
        self.__numberBears = numberBears 
        self.__ecosystem = ["B"] * self.__numberBears
        self.__ecosystem += ["F"] * self.__numberFishes
        self.__ecosystem += ["N"] * (self.__riverLength - self.__numberBears - self.__numberFishes)
        random.shuffle(self.__ecosystem)

    def displayStatus(self):
        if self.__currentStep == 0:
            print("The initial state of river is:", "".join(self.__ecosystem))
        elif self.__currentStep == 1:
            print("The state of river after 1 step is:", "".join(self.__ecosystem))
        else:
            print("The state of river after", self.__currentStep, "steps is:", "".join(self.__ecosystem))

    def proceedBirth(self):
        nonePosition = [i for i in range(self.__riverLength) if self.__ecosystem[i] == "N"]
        random.shuffle(nonePosition)
        for i in range(min(len(self.__pendingBirth), len(nonePosition))):
            self.__ecosystem[nonePosition[i]] = self.__pendingBirth[i]
        self.__pendingBirth = []

    def move(self, position, orientation):
        if position + orientation < 0 or position + orientation >= self.__riverLength:
            return 0
        additionalMoves = 0
        if orientation == -1:
            if self.__ecosystem[position] == "B":
                if self.__ecosystem[position - 1] == "B":
                    self.__pendingBirth.append("B")
                else:
                    self.__ecosystem[position - 1] = "B"
                    self.__ecosystem[position] = "N"
            else:
                if self.__ecosystem[position - 1] == "B":
                    self.__ecosystem[position] = "N"
                elif self.__ecosystem[position - 1] == "F":
                    self.__pendingBirth.append("F")
                else:
                    self.__ecosystem[position - 1] = "F"
                    self.__ecosystem[position] = "N"
        elif orientation == 1:
            if self.__ecosystem[position] == "B":
                if self.__ecosystem[position + 1] == "B":
                    self.__pendingBirth.append("B")
                else:
                    self.__ecosystem[position + 1] = "B"
                    self.__ecosystem[position] = "N"
                    additionalMoves = 1
            else:
                if self.__ecosystem[position + 1] == "B":
                    self.__ecosystem[position] = "N"
                elif self.__ecosystem[position + 1] == "F":
                    self.__pendingBirth.append("F")
                else:
                    self.__ecosystem[position + 1] = "F"
                    self.__ecosystem[position] = "N"
                    additionalMoves = 1
        return additionalMoves

    def simulate(self):
        self.__currentStep += 1
        i = 0
        while i < self.__riverLength:
            if self.__ecosystem[i] != "N":
                i += self.move(i, random.randint(-1, 1))
            i += 1
        self.proceedBirth()

def inputPrompt(description):
    while True:
        ret = input(description)
        try:
            return int(ret)
        except ValueError:
            print("Error: The input must be an integer number.")

river = Ecosystem(
            inputPrompt("Enter the length of river: "),
            inputPrompt("Enter the number of fishes: "),
            inputPrompt("Enter the number of bears: ")
        )
for i in range(inputPrompt("Enter the number of steps: ")):
    river.displayStatus()
    river.simulate()
river.displayStatus()
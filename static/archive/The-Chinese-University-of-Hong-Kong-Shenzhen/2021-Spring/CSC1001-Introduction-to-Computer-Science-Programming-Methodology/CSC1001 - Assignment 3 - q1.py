def inputString(description):
    ret = input(description)
    while not(ret.isalpha()):
        print("Error: The input must be a string containing only alphabets.")
        ret = input(description)
    return ret

def inputInt(description):
    ret = input(description)
    while not(ret.isdigit()):
        print("Error: The input must be an integer number.")
        ret = input(description)
    return int(ret)

def inputFloat(description):
    try:
        return float(input(description))
    except:
        print("Error: The input must be a float number.")
        return inputFloat(description)

class Flower:
    def __init__(self, name, numberOfPetals, price):
        self.__name = name
        self.__numberOfPetals = numberOfPetals
        self.__price = price

    def display(self):
        print("Name:", self.__name)
        print("Number of Petals:", self.__numberOfPetals)
        print("Price:", self.__price)

    def getName(self):
        return self.__name
    
    def getNumberOfPetals(self):
        return self.__numberOfPetals
    
    def getPrice(self):
        return self.__price

    def setName(self, name):
        name = str(name)
        if not(name.isalpha()):
            print("Error: The assigned value must be a string containing only alphabets.")
        else:
            self.__name = name
        
    def setNumberOfPetals(self, numberOfPetals):
        numberOfPetals = str(numberOfPetals)
        if not(numberOfPetals.isdigit()):
            print("Error: The assigned value must be an integer number.")
        else:
            self.__numberOfPetals = int(numberOfPetals)

    def setPrice(self, price):
        price = str(price)
        try:
            self.__price = float(price)
        except:
            print("Error: The assigned value must be a float number.")

if __name__ == "__main__":
    flower = Flower(
                inputString("Enter the name of the flower: "),
                inputInt("Enter its number of petals: "),
                inputFloat("Enter its price: ")
            )
    flower.display()

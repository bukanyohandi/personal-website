import re

def inputPrompt(description):
    while True:
        poly = "".join(input(description).split())
        if poly == "":
            print("Error: Input not found.")
            continue
        doubleCharacter = False
        for i in range(26):
            for j in range(26):
                if (poly.find(chr(ord('A') + i) + chr(ord('A') + j)) != -1) or (poly.find(chr(ord('a') + i) + chr(ord('a') + j)) != -1):
                    doubleCharacter = True
        if doubleCharacter:
            print("Error: The inputted variable should only consist of one letter.")
            continue
        try:
            Polynomial(poly).derivate()
            return poly
        except:
            print("Error: Invalid syntax.")

class Polynomial:
    def __init__(self, poly):
        self.__poly = poly
        try:
            self.__var = poly[len(re.split("[A-Za-z]", poly)[0])]
        except IndexError:
            self.__var = "?"
        
    def derivate(self):
        coefficients = {}
        previousSign = eval("+" + "1")
        results = map(str.strip, re.split(r"([+ \-])", self.__poly))
        for terms in results:
            if terms in "+-":
                previousSign = eval(terms + "1")
            elif self.__var in terms:
                term = terms.split(self.__var)
                if len(term[0]) == 0:
                    term[0] = "1"
                if len(term[1]) == 0:
                    term[1] = "1"
                if term[0][-1] == "*":
                    term[0] += "1"
                a_i = eval(term[0])
                if term[1][0] == "^":
                    term[1] = term[1][1:]
                b_i = eval(term[1])
                try:
                    coefficients[b_i - 1] += previousSign * b_i * a_i
                except KeyError:
                    coefficients[b_i - 1] = previousSign * b_i * a_i
        self.__poly = ""
        coefficients = dict(sorted(coefficients.items(), reverse = True))
        for (key, value) in coefficients.items():
            if value == 0:
                continue
            elif value > 0:
                self.__poly += "+"
            else:
                self.__poly += "-"
            if abs(value) != 1:
                self.__poly += str(abs(value))
                if key > 0:
                    self.__poly += "*"
            if key == 0:
                if abs(value) == 1:
                    self.__poly += "1"
                continue
            elif key == 1:
                self.__poly += self.__var
            else:
                self.__poly += self.__var + "^" + str(key)
        if self.__poly == "":
            self.__poly = "0"
        elif self.__poly[0] == "+":
            self.__poly = self.__poly[1:]

    def getPoly(self):
        return self.__poly

    def getVar(self):
        return self.__var

g = Polynomial(inputPrompt("Input the polynomial: "))
g.derivate()
print("The derivated the polynomial is:", g.getPoly())

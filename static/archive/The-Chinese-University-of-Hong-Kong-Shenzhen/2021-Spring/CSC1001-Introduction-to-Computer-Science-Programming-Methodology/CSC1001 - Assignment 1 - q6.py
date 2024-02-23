import math

def inputPrompt(description):
    while True:
        inp = input(description)
        if inp in ["sin", "cos", "tan"]:
            return getattr(math, inp), inp
        print("The input should be either sin, cos, or tan")

def inputPrompt2(description):
    ret = None
    while True:
        inp = input(description)
        for cast in [int, float]:
            try:
                ret = cast(inp)
                return ret
            except ValueError:
                if cast == float:
                    print("The input should be either an integer number or a float number")
                pass

def inputPrompt3(description):
    ret = None
    while True:
        inp = input(description)
        for cast in [int]:
            try:
                ret = cast(inp)
                if ret > 0:
                    return ret
                else:
                    print("The integer should be larger than 0")
            except ValueError:
                print("The input should be an integer number")
                pass

f, strf = inputPrompt("Specify a trigonometric function f: ")
a = inputPrompt2("Input the interval end points a: ")
b = inputPrompt2("Input the interval end points b: ")
n = inputPrompt3("Input the number of sub-intervals n: ")
sum = 0
for i in range(1, n+1):
    sum += (b - a) / n * f(a + (b - a) / n * (i - 1/2))
print("The numerical integration of " + strf + " over [" + str(a) + ", " + str(b) + "] is", sum)
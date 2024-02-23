def inputPrompt(description):
    ret = None
    while True:
        inp = input(description)
        for cast in [float]:
            try:
                ret = cast(inp)
                if ret > 0:
                    return ret
                else:
                    print("The number should be positive")
            except ValueError:
                print("The input should be a number")
                pass

def sqrt(n):
    nextGuess = 1
    lastGuess = -1
    while abs(nextGuess - lastGuess) >= 0.0001:
        lastGuess = nextGuess
        nextGuess = (lastGuess + n / lastGuess) / 2    
    return nextGuess

print("The approximation of the sqrt number:", sqrt(inputPrompt("Enter a positive number: ")))
def inputPrompt(description):
    ret = None
    while True:
        inp = input(description)
        for cast in [int]:
            try:
                ret = cast(inp)
                if ret > 0:
                    return inp
                else:
                    print("The integer should be positive")
            except ValueError:
                print("The input should be an integer number")
                pass

for digit in list(inputPrompt("Enter a positive integer: ")):
    print(digit)
def inputPrompt(description):
    ret = None
    while True:
        inp = input(description)
        for cast in [int]:
            try:
                ret = cast(inp)
                if ret > 0:
                    return ret
                else:
                    print("The integer should be positive")
            except ValueError:
                print("The input should be an integer number")
                pass

N = inputPrompt("N = ")
print("m" + "\t" + "m+1" + "\t" + "m**(m+1)")
for m in range(1, N + 1):
    print(str(m) + "\t" + str(m + 1) + "\t" + str(m ** (m + 1)))
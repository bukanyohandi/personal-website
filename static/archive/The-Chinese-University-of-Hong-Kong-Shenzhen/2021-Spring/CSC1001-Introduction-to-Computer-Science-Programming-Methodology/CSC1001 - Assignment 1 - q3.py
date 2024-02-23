def inputPrompt(description):
    ret = None
    while True:
        inp = input(description)
        for cast in [int]:
            try:
                ret = cast(inp)
                return ret
            except ValueError:
                print("The input should be an integer number")
                pass

m = inputPrompt("m = ")
n = 1
while n**2 <= m:
    n += 1
print("n =", n)
def inputPrompt(description):
    while True:
        try:
            ret = int(input(description))
            if ret <= 0:
                print("InputError: The number of disks must be larger than 0!")
            else:
                return ret
        except ValueError:
            print("InputError: The number of disks must be an integer!")

def HanoiTower(n):
    #moveStack(n, "ABC") = moveStack(n - 1, "ACB") + "A" -> "C" + moveStack(n - 1, "BAC")
    #moveStack(1, "ABC") = "A" -> "C"
    stackList = [(n, ["A", "B", "C"])]
    while stackList:
        n, str = stackList.pop()
        if n == -1:
            print(str[0] + " --> " + str[2])
        elif n != 0:
            stackList.append((n - 1, [str[1], str[0], str[2]]))
            stackList.append((  - 1, str))
            stackList.append((n - 1, [str[0], str[2], str[1]]))

HanoiTower(inputPrompt("Please input the number of disks: "))

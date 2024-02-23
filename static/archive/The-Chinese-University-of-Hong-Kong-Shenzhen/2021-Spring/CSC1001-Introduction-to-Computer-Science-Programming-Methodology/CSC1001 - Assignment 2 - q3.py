def inputPrompt(description):
    ret = None
    while True:
        inp = input(description)
        if inp.isnumeric():
            if 13 <= len(inp) and len(inp) <= 16:
                return inp
            else:
                print("The length number should be between 13 and 16")
        else:
            print("The input should be a positive integer number")

def isValid(number):
    number = list(number)[::-1]
    return (sumOfDoubleEvenPlace(number) + sumOfOddPlace(number)) % 10 == 0

def sumOfDoubleEvenPlace(number):
    ret = 0
    for i in range(1, len(number), 2):
        ret += getDigit(2 * int(number[i]))
    return ret

def getDigit(number):
    ret = number % 10
    if number > 9:
        ret += number // 10
    return ret

def sumOfOddPlace(number):
    ret = 0
    for i in range(0, len(number), 2):
        ret += int(number[i])
    return ret

print("The card number is valid." if isValid(inputPrompt("Enter a card number: ")) else "The card number is invalid.")
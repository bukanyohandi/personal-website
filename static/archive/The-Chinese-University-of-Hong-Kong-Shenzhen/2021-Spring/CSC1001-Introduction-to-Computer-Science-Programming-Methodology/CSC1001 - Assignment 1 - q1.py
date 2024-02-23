def inputPrompt(description):
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

finalAccountValue = inputPrompt("Enter the final account value: ")
annualInterestRate = inputPrompt("Enter the annual interest rate: ")
numberOfYears = inputPrompt("Enter the number of years: ")
print("The initial value is ", finalAccountValue / (1 + annualInterestRate / 100) ** numberOfYears)
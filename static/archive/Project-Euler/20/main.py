fact = 1
for num in range(1, 101):
    fact *= num
print(sum([int(digit) for digit in str(fact)]))
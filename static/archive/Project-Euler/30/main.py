sm = 0
for num in range(1, 300000):
    if num == sum([int(digit) ** 5 for digit in str(num)]):
        sm += num
print(sm - 1)
import math
def d(n):
    n = int(n)
    sum = -n
    for div in range(1, math.floor(math.sqrt(n)) + 1):
        if n % div == 0:
            sum += div + n / div
        if div * div == n:
            sum -= div
    return sum

is_abundant = [False for num in range(28124)]
abundants = []
for num in range(12, 28124):
    if d(num) > num:
        is_abundant[num] = True
        abundants.append(num)
sum = 0
for num in range(1, 28124):
    can = False
    for abundant in abundants:
        if num > abundant and is_abundant[num - abundant]:
            can = True
    if can == False:
        sum += num

print(sum)
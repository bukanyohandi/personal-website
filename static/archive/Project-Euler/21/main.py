amicable = [False for num in range(20000)]
import math
def d(n):
    ret = 0
    for num in range(1, math.floor(math.sqrt(n)) + 1):
        if n % num == 0:
            ret += num + n / num
        if num * num == n:
            ret -= num
    return int(ret) - n
for a in range(1, 10000):
    b = d(a)
    if b == a: continue
    if d(b) == a:
        amicable[a] = True
        amicable[b] = True
sum = 0
for num in range(10000):
    if amicable[num]:
        sum += num
print(sum)
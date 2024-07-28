import math
sum = 0
num = 1
while True:
    sum += num
    num += 1
    divisors = 0
    for _ in range(math.floor(math.sqrt(sum))):
        if sum % (_ + 1) == 0:
            divisors += 2
            if (_ + 1) * (_ + 1) == sum:
                divisors -= 1
    if divisors > 500:
        print(sum)
        break
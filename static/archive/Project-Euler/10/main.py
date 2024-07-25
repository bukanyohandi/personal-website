is_prime = [True for _ in range(2000000)]
is_prime[0] = False
is_prime[1] = False
sum = 0
for cur in range(2000000):
    if is_prime[cur]:
        for num in range(cur * 2, 2000000, cur):
            is_prime[num] = False
        sum += cur
print(sum)
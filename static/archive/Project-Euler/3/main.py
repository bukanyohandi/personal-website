num = 600851475143
mx = -1
prime = 2
while num > 1:
    while num % prime == 0:
        mx = max(mx, prime)
        num /= prime
    prime += 1
print(mx)
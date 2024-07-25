primes = [2]
num = 3
while len(primes) < 10001:
    is_prime = True
    for prime in primes:
        if num % prime == 0:
            is_prime = False
            break
    if is_prime:
        primes.append(num)
    num += 1
print(primes[-1])
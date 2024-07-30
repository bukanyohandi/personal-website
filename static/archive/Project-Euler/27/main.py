is_prime = [True for num in range(2000000)]
is_prime[1] = False
for num in range(1, 2000000):
    if is_prime[num]:
        for num_next in range(num * 2, 2000000, num):
            is_prime[num_next] = False

def simulate(a, b):
    global is_prime
    n = 0
    while is_prime[n ** 2 + a * n + b]:
        n += 1
    return n

mx = -1
which_ab = -1
for a in range(-999, 1000):
    for b in range(-1000, 1001):
        res = simulate(a, b)
        if res > mx:
            mx = res
            which_ab = a * b
print(which_ab)
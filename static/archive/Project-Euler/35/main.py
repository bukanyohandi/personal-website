is_prime = [True for num in range(1000000)]
is_prime[0] = False
is_prime[1] = False
for num in range(2, 1000000):
    if is_prime[num]:
        for next_num in range(num * 2, 1000000, num):
            is_prime[next_num] = False
def check(num):
    global is_prime
    n = len(str(num)) + 1
    nxt = str(num)
    for _ in range(n):
        if is_prime[int(nxt)] == False:
            return False
        nxt = nxt[-1] + nxt[:-1]
    return True

cnt = 0
for num in range(2, 1000000):
    if is_prime[num] and check(num):
        cnt += 1
print(cnt)
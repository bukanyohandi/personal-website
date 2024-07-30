is_prime = [True for num in range(1000000)]
is_prime[0] = False
is_prime[1] = False
for num in range(2, 1000000):
    if is_prime[num]:
        for next_num in range(num * 2, 1000000, num):
            is_prime[next_num] = False
def unique(n):
    global is_prime
    cur = str(n)
    is_it = True
    while len(cur) > 0:
        if is_prime[int(cur)] == False:
            is_it = False
            break
        cur = cur[1:]
    if is_it == False:
        return False
    cur = str(n)
    while len(cur) > 0:
        if is_prime[int(cur)] == False:
            is_it = False
            break
        cur = cur[:-1]
    return is_it

sm = 0
for num in range(10, 1000000):
    if unique(num):
        sm += num
print(sm)
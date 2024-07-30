def recurring(n):
    start = 1
    while start < n:
        start *= 10
    start %= n
    digit = 0
    visited = [False for i in range(n)]
    while start != 0:
        if visited[start]:
            break
        visited[start] = True
        digit += 1
        while start < n:
            start *= 10
        start %= n
    return digit

mx = -1
which_d = -1
for d in range(1, 1000):
    res = recurring(d)
    if res > mx:
        mx = res
        which_d = d
print(which_d)
perm = []
visited = [False for i in range(10)]
cnt = 0
def dfs():
    global perm, visited, cnt
    if len(perm) == 10:
        cnt += 1
        if cnt == 1000000:
            for dig in perm:
                print(dig, end = '')
            exit(0)
    for i in range(10):
        if visited[i] == False:
            visited[i] = True
            perm.append(i)
            dfs()
            perm.pop()
            visited[i] = False
dfs()
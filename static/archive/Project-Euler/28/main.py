arr = [[-1 for _ in range(1001)] for __ in range(1001)]
num = 2

arr[500][500] = 1
pos = (501, 500)
d = 0

while num < 1002001 + 1:
    x = pos[0]
    y = pos[1]
    dx = [1, 0, -1, 0][d]
    dy = [0, 1, 0, -1][d]
    ddx = [1, 0, -1, 0][(d + 1) % 4]
    ddy = [0, 1, 0, -1][(d + 1) % 4]
    arr[x][y] = num
    num += 1
    if arr[x + ddx][y + ddy] == -1:
        pos = (x + ddx, y + ddy)
        d = (d + 1) % 4
    else:
        pos = (x + dx, y + dy)

sum = 0
for i in range(1001):
    sum += arr[i][i]
for i in range(1001):
    sum += arr[1001 - 1 - i][i]
print(sum - arr[500][500])

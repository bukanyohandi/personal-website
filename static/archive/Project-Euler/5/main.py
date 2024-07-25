import math

ans = 1
for num in range(1, 21):
    ans = math.lcm(ans, num)
print(ans)
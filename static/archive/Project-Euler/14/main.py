dp = [-1 for _ in range(1000000)]
def collatz(num):
    global dp
    if num == 1:
        return 1
    if num < 1000000 and dp[num] != -1:
        return dp[num]
    if num % 2 == 0:
        res = collatz(int(num / 2)) + 1
    else:
        res = collatz(3 * num + 1) + 1
    if num < 1000000:
        dp[num] = res
    return res
mx_num = -1
mx = -1
for num in range(1, 1000000):
    result = collatz(num)
    if result > mx:
        mx = result
        mx_num = num
print(mx_num)
dp = [[-1 for _ in range(50)] for __ in range(50)]
def C(n, k):
    if n < k:
        return 0
    if n == k:
        return 1
    if k == 1:
        return n
    if dp[n][k] != -1:
        return dp[n][k]
    dp[n][k] = C(n - 1, k) + C(n - 1, k - 1)
    return dp[n][k]
print(C(40, 20))
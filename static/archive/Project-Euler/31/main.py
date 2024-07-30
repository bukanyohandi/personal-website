coins = [1, 2, 5, 10, 20, 50, 100, 200]
# memo = [-1 for i in range(201)]
def dp(cur_coin, last):
    if cur_coin < 0:
        return 0
    if cur_coin == 0:
        return 1
    # if memo[cur_coin] != -1:
    #     return memo[cur_coin]
    res = 0
    global coins
    for coin in coins:
        if coin > last:
            continue
        res += dp(cur_coin - coin, coin)
    # memo[cur_coin] = res
    return res
print(dp(200, 200))
mx = -1
for num_1 in range(100, 1000):
    for num_2 in range(100, 1000):
        prod = num_1 * num_2
        if str(prod) == str(prod)[::-1]:
            mx = max(mx, prod)
print(mx)
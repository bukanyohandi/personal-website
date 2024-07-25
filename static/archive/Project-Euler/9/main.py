for c in range(1, 1001):
    for b in range(1, c):
        for a in range(1, b):
            if a ** 2 + b ** 2 == c ** 2 and a + b + c == 1000:
                print(a * b * c)
                exit(0)
F = [0, 1, 1]
while len(str(F[-1])) < 1000:
    F.append(F[-1] + F[-2])
print(len(F) - 1)
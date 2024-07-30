f = [1]
for i in range(1, 10):
    f.append(f[-1] * i)
sm = 0
for num in range(10, 362880):
    if num == sum([f[int(digit)] for digit in str(num)]):
        sm += num
print(sm)

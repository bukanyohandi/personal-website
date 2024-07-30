def is_pandigital(a, b, c):
    a = a + b + c
    if sorted([int(digit) for digit in a]) == [num for num in range(1, 10)]:
        return True
    return False

st = set()
for a in range(1, 10000):
    for b in range(a + 1, 10000):
        if len(str(a)) + len(str(b)) + len(str(a * b)) == 9:
            if is_pandigital(str(a), str(b), str(a * b)):
                st.add(a * b)
print(sum(st))
inexps = []
def inexp(a, b):
    global inexps
    aa = str(a)
    bb = str(b)
    if aa[0] == bb[1]:
        if a * int(bb[0]) == int(aa[1]) * b:
            inexps.append((a, b))
    if aa[1] == bb[0]:
        if a * int(bb[1]) == int(aa[0]) * b:
            inexps.append((a, b))
for a in range(10, 100):
    for b in range(a + 1, 100):
        inexp(a, b)
num = 1
denum = 1
for (a, b) in inexps:
    num *= a
    denum *= b
import math
gcdd = math.gcd(num, denum)
denum /= gcdd
print(int(denum))
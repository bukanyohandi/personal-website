x = 7.5
y = x + x*5.5
def add1():
    x = x + 1
    add2(x)
def add2(y):
    y = y + 2
    add3(y)
    z = y * (5.5 >=2)
def add3(z):
    z = z + 3
add2(y)
add3(x)
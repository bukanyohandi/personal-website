x = 2
x = y + 2
def foo(x):
    x = x + 1

def func(z, x, y=6):
    x = y + z
    foo(x)

func(x, 4, y=5)
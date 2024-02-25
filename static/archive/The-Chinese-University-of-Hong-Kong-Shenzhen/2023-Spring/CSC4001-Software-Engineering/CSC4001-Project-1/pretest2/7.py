x = 1
def foo2():
    y = x + 1
foo2()
x = y + 2
def func1(y):
    z = y*(5-2)
def foo(x=5, y=6):
    func1(y)
foo()
def foo3(x=10):
    x = y + 10
foo()
foo2()
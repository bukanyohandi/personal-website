lockerIsOpened = [False for i in range(101)]
for i in range(1, 101):
    for j in range(i, 101, i):
        lockerIsOpened[j] = not(lockerIsOpened[j])
for i in range(1, 101):
    if lockerIsOpened[i]:
        print("Locker", i, "is opened!")
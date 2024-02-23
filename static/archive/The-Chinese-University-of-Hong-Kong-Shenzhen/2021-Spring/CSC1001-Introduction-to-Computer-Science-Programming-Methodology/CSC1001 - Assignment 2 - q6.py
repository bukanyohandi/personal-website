import random

def isSameDiagonal(p, q):
    return ((p[0] - p[1]) == (q[0] - q[1])) or ((p[0] + p[1]) == (q[0] + q[1]))

def isSameColumn(p, q):
    return p[0] == q[0]

def isSameRow(p, q):
    return p[1] == q[1]

def findSolution():
    global coordinates
    if len(coordinates) == 8:
        return
    list_i = []
    for i in range(8):
        ok = True
        for k in coordinates:
            if isSameColumn((i, -1), k):
                ok = False
        if ok:
            list_i.append(i)
    random.shuffle(list_i)
    list_j = []
    for j in range(8):
        ok = True
        for k in coordinates:
            if isSameRow((-1, j), k):
                ok = False
        if ok:
            list_j.append(j)
    random.shuffle(list_j)
    list_k = []
    for i in list_i:
        for j in list_j:
            ok = True
            for k in coordinates:
                if isSameDiagonal((i, j), k):
                    ok = False
            if ok:
                list_k.append((i, j))
    random.shuffle(list_k)
    for k in list_k:
        coordinates.append(k)
        findSolution()
        if len(coordinates) == 8:
            return
        coordinates.pop()

coordinates = []
findSolution()
for i in range(8):
    print(end = "|")
    for j in range(8):
        if (i, j) in coordinates:
            print(end = "Q|")
        else:
            print(end = " |")
    print("")
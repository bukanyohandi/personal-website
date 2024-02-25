import cvxpy as cp

n = 8
x = cp.Variable((n,n), boolean=True)

constraints = [cp.sum(x, axis=0) == 1, cp.sum(x, axis=1) == 1]
for k in range(-n+2, n):
    constraints.append(cp.sum([x[i,j] for i in range(n) for j in range(n) if i-j == k]) <= 1)
for k in range(3, n*2-1):
    constraints.append(cp.sum([x[i,j] for i in range(n) for j in range(n) if i+j == k]) <= 1)

objective = cp.Maximize(1) # Any objective function doesn't matter

cp.Problem(objective, constraints).solve()
print(x.value)

m,s =input().split()
m=int(m)
s=int(s)
if s==0:
    if m==1:
        print("0 0")
    else:
        print("-1 -1")
    exit()
sumdigits=int(s-1)
arr=[1]
for i in range(m-1):
    arr.append(0)
for i in reversed(range(m)):
    tmp=min(9-arr[i],sumdigits)
    arr[i]+=tmp
    sumdigits-=tmp
if sumdigits!=0:
    print(-1,end='')
else:
    for i in range(m):
        print(arr[i],end='')
print(" ",end='')
sumdigits=int(s-1)
arr=[1]
for i in range(m-1):
    arr.append(0)
for i in range(m):
    tmp=min(9-arr[i],sumdigits)
    arr[i]+=tmp
    sumdigits-=tmp
if sumdigits!=0:
    print(-1,end='')
else:
    for i in range(m):
        print(arr[i],end='')
print("")
n=int(input())
a=list(map(int,input().strip().split()))[:n]
a.sort()
print(int((n-1)/2))
arr=[]
for i in range(n):
    arr.append(0)
start=0
for i in range(1,n,2):
    arr[i]=a[start]
    start+=1
for i in range(0,n,2):
    arr[i]=a[start]
    start+=1
for i in arr:
    print(i,"",end='')
print("")
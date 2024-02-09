tc=int(input())
for t in range(tc):
    trash=input()
    n,m=input().split()
    n=int(n)-1
    m=int(m)-1
    arr1=[]
    arr2=[]
    for i in range(n):
        x=int(input())
        arr1.append(x)
    for i in range(m):
        x=int(input())
        arr2.append(x)
    arr1.sort()
    arr2.sort()
    ans=0
    le=1
    ri=1
    while n>0 and m>0:
        if arr1[n-1]>arr2[m-1]:
            ans+=arr1[n-1]*le
            ri+=1
            n-=1
        else:
            ans+=arr2[m-1]*ri
            le+=1
            m-=1
    while n>0:
        ans+=arr1[n-1]*le
        n-=1
    while m>0:
        ans+=arr2[m-1]*ri
        m-=1
    print(ans)
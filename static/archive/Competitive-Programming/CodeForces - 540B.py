n,k,p,x,y=map(int,input().split())
s=0
cnt=0
sz=0
ans=[]
for arr in map(int,input().split()):
    s+=arr
    sz+=1
    if arr>=y:
        cnt+=1
while cnt<(n+1)/2:
    ans.append(y)
    cnt+=1
while len(ans)+k<n:
    ans.append(1)
if s+sum(ans)<=x and len(ans)+sz==n:
    for i in range(len(ans)):
        print(ans[i],"",end='')
    print("")
else:
    print("-1")
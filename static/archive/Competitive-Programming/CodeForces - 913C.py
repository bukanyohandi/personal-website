n,l=input().split()
n=int(n)
l=int(l)
c=list(map(int,input().strip().split()))[:n]
pow2=[1]
for i in range(n-1):
    pow2.append(2*pow2[i])
for i in range(n-1):
    c[i+1]=min(c[i+1],2*c[i])
def cost(pos,money):
    if pos==0:
        return c[pos]*money
    take=int(money/pow2[pos])
    ret=c[pos]*take
    money-=pow2[pos]*take
    if money==0:
        return ret
    return c[pos]*take+min(cost(pos-1,money),c[pos])
print(cost(n-1,l))
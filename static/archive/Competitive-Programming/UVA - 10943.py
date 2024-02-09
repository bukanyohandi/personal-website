def gcd(a,b):
    a=int(a)
    b=int(b)
    if b==0:
        return a
    else:
        return gcd(b,a%b)
while 1:
    n,k=map(int,input().split())
    if n==0 and k==0:
        break
    numerator=[]
    for i in range(k-1):
        numerator.append(int(n+i+1))
    for i in range(k-1):
        pivot=int(i+1)
        j=0
        while pivot!=1 and j<k-1:
            gcdd=gcd(pivot,numerator[j])
            if gcdd!=1:
                pivot/=gcdd
                numerator[j]/=gcdd
            j+=1
    ans=1
    for i in range(k-1):
        ans*=numerator[i]
        ans%=1000000
    print(int(ans))
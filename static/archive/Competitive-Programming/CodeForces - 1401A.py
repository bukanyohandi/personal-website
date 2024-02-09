for t in range(int(input())):
    n,k=map(int,input().split())
    print(k-n) if k>n else print((k+n)%2)
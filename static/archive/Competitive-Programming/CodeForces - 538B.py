s=input()
k=0
for i in range(len(s)):
    k=max(k,ord(s[i])-ord('0'))
arr=[]
for i in range(k):
    arr.append('')
for i in range(len(s)):
    for j in range(k):
        if ord(s[i])-ord('0')>j:
            arr[j]+='1'
        elif len(arr[j])!=0:
            arr[j]+='0'
print(k)
for i in range(k):
    if i!=0:
        print(" ",end='')
    print(arr[i],end='')

n=int(input())
s=input().split()
maxV,minV = int(s[0]),int(s[0])
for i in s:
    maxV = max(maxV,int(i))
    minV = min(minV,int(i))
print(maxV-minV)

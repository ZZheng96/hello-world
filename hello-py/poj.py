
s=input().split()
L,R=int(s[0]),int(s[1])
num=0
for i in range(L,R+1):
    for j in str(i):
        if j=="2":
            num+=1
print(num)

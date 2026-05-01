s=input()
a,b,c=s.split();
a=int(a)
b=int(b)
c=int(c)
if a+b>c and a+c>b and b+c>a:
    print("YES")
else:
    print("NO")

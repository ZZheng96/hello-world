s=input().split()
a,b,c=int(s[0]),int(s[1]),s[2]
if c in "+-*/":
    if c=="+":
        print(a+b)
    elif c=="-":
        print(a-b)
    elif c=="/":
        if b==0:
            print("Divided by zero!")
        else:
            print(a//b)
    else:
        print(a*b)
else:
    print("Invalid operator!")
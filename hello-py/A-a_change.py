
# ls1="abcdefghijklmnopqrstuvwxyz"
# ls2="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# s=input()
# outstr=""
# for i in s:
#     if i in ls1:
#         outstr+=i.upper()
#     elif i in ls2:
#         outstr+=i.lower()
#     else:
#         outstr+=i
# print(outstr)

s=input()
for c in s:
    if 'a'<=c<='z':
        print(chr(ord(c)-32),end="")
    elif 'A'<=c<='Z':
        print(chr(ord(c))+32,end="")
    else:
        print(c,end="")

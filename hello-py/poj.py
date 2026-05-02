

def ways(n,m):
    if n==0:
        return 1
    if m==0:
        return 0
    if m>n:
        return ways(n,n)
    return ways(n-m,m)+ways(n,m-1)


a=int(input())
num=ways(a,a)
print(num)
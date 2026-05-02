# 描述
# 将正整数n 表示成一系列正整数之和，n=n1+n2+…+nk, 其中n1>=n2>=…>=nk>=1 ，k>=1 。
# 正整数n 的这种表示称为正整数n 的划分。
# 正整数n 的不同的划分个数称为正整数n 的划分数。

# 输入
# 一个整数N(0 < N <= 30)。
# 输出
# 输出N的划分数。

# 递归思路：分成最大可用 m 与最大可用 m-1 两种情况

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
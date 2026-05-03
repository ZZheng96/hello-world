import copy
s=input().split()
n,m=int(s[0]),int(s[1])
ls=[]
for i in range(n):
    a=map(int,input().split())
    ls.append(list(a))
ls2=copy.deepcopy(ls)
for i in range(1,n-1):
    for j in range(1,m-1):
        b=(ls[i-1][j]+ls[i+1][j]+ls[i][j-1]+ls[i][j+1]+ls[i][j])/5
        ls2[i][j]=round(b) #四舍五入
for r in ls2:
    a=map(str,r)
    print(" ".join(list(a)))

# 描述
# 给定n行m列的图像各像素点的灰度值，要求用如下方法对其进行模糊化处理：

# 1. 四周最外侧的像素点灰度值不变；

# 2. 中间各像素点新灰度值为该像素点及其上下左右相邻四个像素点原灰度值的平均（舍入到最接近的整数）。

# 输入
# 第一行包含两个整数n和m，表示图像包含像素点的行数和列数。1 <= n <= 100，1 <= m <= 100。
# 接下来n行，每行m个整数，表示图像的每个像素点灰度。相邻两个整数之间用单个空格隔开，每个元素均在0~255之间。
# 输出
# n行，每行m个整数，为模糊处理后的图像。相邻两个整数之间用单个空格隔开。



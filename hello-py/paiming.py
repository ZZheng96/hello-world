def f(x): #用于排序的关键特征函数
    return (-int(x[1]),x[0]) #列表里都是字符串，比较时改成int
n=int(input())
ls=[]
for i in range(n):
    ls.append(input().split())
# ls.sort(key=f) #把列表里的元组排序
ls.sort(key= lambda x: (-int(x[1]),x[0]))
# for i in range(n):
    # print(" ".join(ls[i])) #元组转字符串
for i in ls:
    print(i[0],i[1])  

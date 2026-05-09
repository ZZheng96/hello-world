import numpy as np
print(np.array([1,2,3]))
print(np.arange(1,9,2))
print(np.linspace(1,10,4))
print(np.random.randint(10,20,(2,3)))
print(np.random.randint(10,20,5))
a=np.zeros(3)
print(a)
print(list(a))
a=np.zeros([2,3],dtype=int)
print(a)
b=np.array([i for i in range(12)])
a=b.reshape((3,4))
print(b)
print(a)
print(len(a))
print(a.size)
print(a.ndim)
print(a.shape)
print(a.dtype)
L=a.tolist()
print(L)
b=a.flatten()
print(b)
a=np.array([1,2,3])
b=np.append(a,10) #调用np对象的方法，用a后接10去创建一个新的数组
print(b)
b=np.append(a,[10,20]) #a后接 10 20
print(b)
c=np.zeros((2,3),dtype=int) # 创建两行三列整数类型的全零数组
print(c)
print(np.append(a,c)) #这时c会被自动展开
print(np.concatenate([a,(1,2),a])) #用元组和列表都行

print(np.concatenate([c,np.array([[1,2],[10,20]])],axis=1)) 
# concatenate可以拼接多维数组，axis=1表示增加列
print(np.concatenate([c,np.array([[1,2,3]])])) 
# 二维列表就是以列表为元素的一维列表，这样相当于增加一行

#查找

a=np.array((1,2,3,5,3,4))
pos = np.argwhere(a==3)
print(pos)
a=np.array([[1,2,3],[4,5,2]])
print(2 in a)
pos=np.argwhere(a==2)
print(pos)
b=a[a>2] #取其元素创建新的一维数组
print(b)
a[a>2]=-1
print(b) #b没变
print(a) #a改变

#运算
a=np.array([1,2,3,4])
b= a+1
print(b)
a+=1
print(a)
print(a*b)
#在n维数组上定义了矩阵运算方法
print(a+b)
c=np.sqrt(a*10)
print(c)

a=np.arange(8)
b=a[3:6]
print(b)
c=np.copy(a[3:6]) #新的数组
b[0]=100
print(a)
print(c)
#作为视图的b会修改a，但c不会随a改变
a=np.array([[i+1+j*4 for i in range(4)] for j in range(4)])
print(a)
b=a[1:3,1:4]
print(b)
# import pandas as pd
# s= pd.Series(data=[80,90,100],index=['yuwen','shuxue','yingyu'])
# for x in s:
#     print(x,end="")
# print("")
# print(s['yuwen'],s[1])
# print(s[0:2]['shuxue'])
# print(s['shuxue':'yingyu'][1])
# for i in range(len(s.index)):
#     print(s.index[i],end=" ")
# s['tiyu']=110
# s.pop('shuxue')
# # s2=s.append(pd.Series(120,index=['zhengzhi']))
# s2 = pd.concat([s, pd.Series([120], index=['zhengzhi'])])
# print(s2['yuwen'],s2['zhengzhi'])
# print(list(s2))


import pandas as pd
pd.set_option('display.unicode.east_asian_width',True)
#输出对齐方面的设置
scores = [['男',108,115,97],['女',115,87,105],['女',100,60,130],
['男',112,80,50]]
names = ['刘一哥','王二姐','张三妹','李四弟']
courses = ['性别','语文','数学','英语']
df = pd.DataFrame(data=scores,index = names,columns = courses)
print(df)
print(df.values[0][1],type(df.values))
print(list(df.index))
print(list(df.columns))
print(df.index[2],df.columns[2])
s1=df['语文']
print(s1['刘一哥'],s1[0])
print(df['语文']['刘一哥'])
s2=df.loc['王二姐']
print(s2['性别'],s2['语文'],s2[2])

print("---下面是DataFrame的分析和统计---")
print(df.T)
#df.T是df的转置矩阵,即行列互换的矩阵
print(df.sort_values('语文',ascending=False)) #按语文成绩降序排列
# print(df.sum()['语文'],df.mean()['数学'],df.median()['英语'])
#>>435 85.5 101.0 语文分数之和、数学平均分、英语中位数
print(df['语文'].sum(), df['数学'].mean(), df['英语'].median())

print(df.min()['语文'],df.max()['数学'])
#>>100 115 语文最低分，数学最高分
# print(df.max(axis = 1)['王二姐'])
#>>115 王二姐的最高分科目的分数
print(df[['语文', '数学', '英语']].max(axis=1)['王二姐'])

print(df['语文'].idxmax())
#>>王二姐
# 语文最高分所在行的标签
print(df['数学'].argmin())
#>>2
# 数学最低分所在行的行号
print(df.loc[(df['语文'] > 100) & (df['数学'] >= 85)])
      
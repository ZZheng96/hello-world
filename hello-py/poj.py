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
      
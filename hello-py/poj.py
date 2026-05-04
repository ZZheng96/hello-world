import pandas as pd
s= pd.Series(data=[80,90,100],index=['yuwen','shuxue','yingyu'])
for x in s:
    print(x,end="")
print("")
print(s['yuwen'],s[1])
print(s[0:2]['shuxue'])
print(s['shuxue':'yingyu'][1])
for i in range(len(s.index)):
    print(s.index[i],end=" ")
s['tiyu']=110
s.pop('shuxue')
# s2=s.append(pd.Series(120,index=['zhengzhi']))
s2 = pd.concat([s, pd.Series([120], index=['zhengzhi'])])
print(s2['yuwen'],s2['zhengzhi'])
print(list(s2))
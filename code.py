import igraph

from igraph import *
g = Graph()


import pandas
df = pandas.read_csv('musae_git_edges.csv')
print(df)


''' import igraph.test
igraph.test.run_tests()  '''



print(df['id_1'][9])

g.add_vertices(37700)
print(g)


print(len(df))
x = int(df['id_1'][9])

for ind in range(0,len(df)) : 
    x = int(df['id_1'][ind])
    y = int(df['id_2'][ind])
    g.add_edges([(x,y)])
    
print(g)


 

layout = g.layout_lgl()
layout = g.layout("lgl")
print(layout)
layout = g.layout("lgl")
plot(g, layout = layout)


g.degree()

lst = []

v1=g.vcount() 

for x in range(g.vcount()):
  c=0    
  for y in range(0,g.vcount()):
      if g.degree(x)==g.degree(y) :
          c = c+1
      if c>1:
          break
           
  if c==1 :
      lst.append(x)


print(lst)
z=g.maxdegree()

 # type(g.degree(4))


if len(lst)==1:
    if g.degree(lst[0]) < z:
        t1 = z-g.degree(lst[0]) 
        g.add_vertices(t1)
        for j in range(v1,g.vcount()):
                g.add_edges([(lst[0],j)]) 
        
    else:
        minn1=100000000000000
        minn2=0
        for i in range(0,g.vcount()):
            if lst[0]!=i :
                if g.degree(lst[0]) - g.degree(i) < minn1:
                    minn1 = g.degree(lst[0]) - g.degree(i)  
                    minn2 = g.degree(i)
               
                
                
             
        for i in range(0,g.vcount()):
            if g.degree(i)==minn2 :
                t2 = z - g.degree(i)
                g.add_vertices(t2)    
                for j in range(v1,g.vcount()): 
                      g.add_edges([(i,j)]) 
                v1=g.vcount() 
            
            
            
   
else:
    maxx_degree = 0
    for i in range(0,len(lst)):
        if maxx_degree < g.degree(lst[i]):
            maxx_degree = g.degree(lst[i]) 
    print(maxx_degree)
    
    for i in range(0,len(lst)):
        if g.degree(lst[i])!=maxx_degree :
            t = maxx_degree - g.degree(lst[i])
            g.add_vertices(t)
            for j in range(v1,g.vcount()):
                g.add_edges([(lst[i],j)]) 
            v1=g.vcount()        
 
    
print(g)



layout = g.layout_kamada_kawai()
layout = g.layout("kamada_kawai")
print(layout)
layout = g.layout("kk")
plot(g, layout = layout)
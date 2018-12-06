import numpy as np


'''
D-H Parameters
'''

'''Theta'''
t1 = 0         # positive insdide the Book    
t2 = 90           #
t3 = 90

'''Link Lengths'''
l1 = 1              #origin Shift Height
l2 = 1
l3 = 1

''' r  '''
r1 = 0
r2 = l2
r3 = l3


t1=(t1/180)*np.pi
t2=(t2/180)*np.pi
t3=(t3/180)*np.pi

#to is theta and a0 is alpha r and d are variable


Final_Mat = [ [ np.cos(t1)*np.cos(t2+t3)  ,  -np.sin(t2+t3)*np.cos(t1)  ,  np.sin(t1)  , np.cos(t1)*(r3*np.cos(t2+t3)+r2*np.cos(t2)+r1) ] , 
              [ np.sin(t1)*np.cos(t2+t3)  ,  -np.sin(t2+t3)*np.sin(t1)  , -np.cos(t1)  , np.sin(t1)*(r3*np.cos(t2+t3)+r2*np.cos(t2)+r1) ] , 
              [ np.sin(t2+t3)              ,   np.cos(t2+t3)             ,   0          , r3*np.sin(t2+t3) + r2*np.sin(t2)               ] , 
              [ 0                         ,   0                         ,   0          , 1                                              ]
            ]

Final_Mat = np.round(Final_Mat,1)
print(Final_Mat)

result = []
result.append( Final_Mat[0][3])
result.append( Final_Mat[1][3])
result.append( Final_Mat[2][3] - l1)


print("Result Cordinates")
print(result)





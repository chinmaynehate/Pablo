import numpy as np
import math

x=100
y=0
z=0


'''
D-H Parameters
'''

'''Link Lengths'''
l1 = 1              #origin Shift Height
l2 = 1
l3 = 1

''' r  '''
r1 = 0
r2 = l2
r3 = l3

#Fix the Shift of Origin
z   += l1

#Solution

t1 = math.atan2(y,x)

A=-z
B=r1-(x*np.cos(t1) + y*np.sin(t1))
D = (2*r1*(x*np.cos(t1) + y*np.sin(t1)) + r3**2 - r2**2 - r1**2 -z**2 - (x*np.cos(t1)+y*np.sin(t1))**2 )/(2*r2)

phi = math.atan2(B,A)

t02 = -phi + math.atan2(D, + (A**2+B**2 - D**2)**0.5)
t12 = -phi + math.atan2(D, - (A**2+B**2 - D**2)**0.5)

t03 = math.atan2( z-r2*np.sin(t02) , x*np.cos(t1) + y*np.sin(t1) - r2*np.cos(t02) -r1 ) -t02 
t13 = math.atan2( z-r2*np.sin(t12) , x*np.cos(t1) + y*np.sin(t1) - r2*np.cos(t12) -r1 ) -t12 

t1 *=180/np.pi
t02*=180/np.pi
t12*=180/np.pi
t03*=180/np.pi 
t13*=180/np.pi 

print("\n\n")
print("theta1 = ",t1)
print("theta2 = ", t02 ,"   or  ", t12)
print("theta3 = ", t03 ,"   or  ", t13)
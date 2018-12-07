import numpy as np
import math
import constants as c
import UARTModule as uart


LEG_A = 0
LEG_B = 1
LEG_C = 2
LEG_D = 3

LEG_SERVO_TOP = 0
LEG_SERVO_MIDDLE = 1
LEG_SERVO_BOTTOM = 2


#   DH Params

'''Link Lengths'''
l1 = c.l1              #origin Shift Height
l2 = c.l2
l3 = c.l3

''' r  '''
r1 = c.l01
r2 = l2
r3 = l3

def init():
    uart.initUART()



def goToXYZ(x,y,z ,legIndex):
    t1,t2,t3 = getInverse(x,y,z)
    if (c.IS_SERIAL_PLUGGED_IN):
        uart.writeAngle(legIndex,0,t1)
        uart.writeAngle(legIndex,1,t2)
        uart.writeAngle(legIndex,2,t3)

def gotoAngle(t1,t2,t3,legIndex):
    if (c.IS_SERIAL_PLUGGED_IN):
        uart.writeAngle(legIndex,0,t1)
        uart.writeAngle(legIndex,1,t2)
        uart.writeAngle(legIndex,2,t3)

def setAngle(angle,legIndex,servoIndex):
    if (c.IS_SERIAL_PLUGGED_IN):
        uart.writeAngle(legIndex,servoIndex,angle)



def getInverse(x,y,z):
    z   += l1       #Shift of Origin

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

    t1=np.round(t1,3)
    t02=np.round(t02,3)
    t12=np.round(t12,3)
    t03=np.round(t03,3) + 90
    t13=np.round(t13,3) + 90

    if (c.ENABLE_ARM_MESSAGES):
        print("\n\n")
        print("theta1 = ",t1)
        print("theta2 = ", t02 ,"   or  ", t12)
        print("theta3 = ", t03 ,"   or  ", t13)

    return t1,t02,t03

def getForward(t1,t2,t3):

    t1=(t1/180)*np.pi
    t2=(t2/180)*np.pi
    t3=((t3-90)/180)*np.pi


    Final_Mat = [ [ np.cos(t1)*np.cos(t2+t3)  ,  -np.sin(t2+t3)*np.cos(t1)  ,  np.sin(t1)  , np.cos(t1)*(r3*np.cos(t2+t3)+r2*np.cos(t2)+r1) ] , 
                [ np.sin(t1)*np.cos(t2+t3)  ,  -np.sin(t2+t3)*np.sin(t1)  , -np.cos(t1)  , np.sin(t1)*(r3*np.cos(t2+t3)+r2*np.cos(t2)+r1) ] , 
                [ np.sin(t2+t3)              ,   np.cos(t2+t3)             ,   0          , r3*np.sin(t2+t3) + r2*np.sin(t2)               ] , 
                [ 0                         ,   0                         ,   0          , 1                                              ]
                ]

    Final_Mat = np.round(Final_Mat,1)
    

    result = []
    result.append( Final_Mat[0][3])
    result.append( Final_Mat[1][3])
    result.append( Final_Mat[2][3] - l1)        #Compensate for Shift of Origin

    if (c.ENABLE_ARM_MESSAGES):
        print(Final_Mat)
        print("Result Cordinates")
        print(result)

    return result[0],result[1],result[2]


import pablo as arm

import time as e



        
if __name__=="__main__":
    arm.init()
    t=0
    while(1):

        while(t<4):
            arm.goToXYZ(2,t,-8,0)
            t+=0.5
            print(t)
            input()
            
        while(t>0):
            arm.goToXYZ(2,t,-8,0)
            t-=0.5
            print(t)
            input()
            


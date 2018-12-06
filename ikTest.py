import pablo as arm

import time as e

user = input("enter a ")
if user == "a":
        
    if __name__=="__main__":
        t=0
        while(1):

            while(t<4):
                arm.goToXY(2,t,-8,0)
                t+=0.5
                print(t)
                e.sleep(2)
            while(t>0):
                arm.goToXY(2,t,-8,0)
                t-=0.5
                print(t)
                e.sleep(2)
            
else:
    print("")


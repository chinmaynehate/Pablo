import pablo as arm
import UARTModule as uart

def command():
    uart.initUART()
    while True:
    
        
        t=0
        while(1):

            while(t<4):
                t1,t2,t3 = arm.getInverse(2,t,-8)
                uart.writeAngle( 0, 0, t1  )
                uart.writeAngle(0, 1 , t2  )
                uart.writeAngle( 0, 2, t3 )
                print(t1,t2,t3)
                t+=0.25
                print(t)
                input()

                
            while(t>0):
                t1,t2,t3 = arm.getInverse(2,t,-8)
                uart.writeAngle( 0, 0, t1  )

                uart.writeAngle(0, 1 , t2  )
                uart.writeAngle( 0, 2, t3 )
                print(t1,t2,t3)
                t-=0.5
                print(t)
                input()

            
        
if __name__=="__main__":
    # x=float(input("Enter Target X:"))
    # y=float(input("Enter Target Y:"))
    # z=float(input("Enter Target Z:"))

    # x=1
    # y=1
    # z=1
    # writeLegIndex = 0

    # t1,t2,t3 = arm.getInverse(x,y,z)
    # input("Press Any Key to Write")
    # arm.goToXYZ(x,y,z,writeLegIndex)

    command()







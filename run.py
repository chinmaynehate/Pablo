import pablo as arm
import UARTModule as uart



def command2():
    uart.initUART()
    while True:
        c = int(input("Enter Command"))
        uart.writeAngle( (c/10)%10 , c%10 ,c/100  )



if __name__=="__main__":
    # x=float(input("Enter Target X:"))
    # y=float(input("Enter Target Y:"))
    # z=float(input("Enter Target Z:"))

    
    command2()



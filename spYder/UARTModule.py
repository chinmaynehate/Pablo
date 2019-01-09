import serial
import constants as c

SER_PORT =   c.SER_PORT
SER_BAUD =   c.SER_BAUD

ser = serial.Serial()

def initUART():
    ser.baudrate=SER_BAUD
    ser.port=SER_PORT
    ser.open()


#    '@@@' <- Servo Angle , '&' <- legIndex ,'*'<-servoIndex
def writeAngle( legIndex ,servoIndex , Angle ): 
    message = Angle*100+legIndex*10+servoIndex
    message = str(int(message))   # @@@&* <- Message Syntax
    if(c.ENABLE_UART_MESSAGES):
        print("UART: Writing '",message,"'")
    ser.write(message.encode())

def writeCommand(message):
    message = str(message)   # @@@&* <- Message Syntax
    if(c.ENABLE_UART_MESSAGES):
        print("UART: Writing '",message,"'")
    ser.write(message.encode())

if __name__=="__main__":
    pass



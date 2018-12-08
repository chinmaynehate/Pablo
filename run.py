import pablo as arm
import UARTModule as uart
import time



def command2():
	uart.initUART()
	while True:
		c = int(input("Enter Command"))
		uart.writeCommand(c)


def createCommand( angle ,servoI):
	if angle < 0:
		return (int(angle)*100) -servoI
	else:
		return (int(angle)*100) +servoI


def loopCommand():
	uart.initUART()
	x=6
	y=2.5
	z=-8

	Y_MAX=8.5
	Y_MIN=-3.5
	STEP_SIZE=0.2

	STEP_DELAY =0.02


	while True:
		# Loop Forward
		while(y<Y_MAX):
			isSol=True
			try:
				print("Trying for :" ,x,",",y,",",z)
				t1,t2,t3 = arm.getInverse(x,y,z)
				command1=createCommand(t1,0)
				command2=createCommand(t2,1)
				command3=createCommand(t3,2)
				print("To Write Angles :",t1,t2,t3)
			except:
				isSol=False

			if isSol:
				uart.writeCommand(command1)
				time.sleep(STEP_DELAY)
				uart.writeCommand(command2)
				time.sleep(STEP_DELAY)
				uart.writeCommand(command3)
			else:	
				print("NO Soultion")
			time.sleep(STEP_DELAY)
			#input("Emter Any Key")
			y+=STEP_SIZE
				
		# Loop BACKWARD
		while(y>Y_MIN):
			isSol=True
			try:
				print("Trying for :" ,x,",",y,",",z)
				t1,t2,t3 = arm.getInverse(x,y,z)
				command1=createCommand(t1,0)
				command2=createCommand(t2,1)
				command3=createCommand(t3,2)
				print("To Write Angles :",t1,t2,t3)
			except:
				isSol=False

			if isSol:
				uart.writeCommand(command1)
				time.sleep(STEP_DELAY)
				uart.writeCommand(command2)
				time.sleep(STEP_DELAY)
				uart.writeCommand(command3)
			else:	
				print("NO Soultion")
			time.sleep(STEP_DELAY)
			#input("Enter Any Key")
			y-=STEP_SIZE

		print("Loop Ended")

                


if __name__=="__main__":
#     command2()
    loopCommand()



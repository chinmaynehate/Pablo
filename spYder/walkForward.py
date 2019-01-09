import pablo as leg
import time


SPACING_X = 5
LEG_HEIGHT = 10
PICKUP_Z = 8

Y1=10
Y2=110
Y3=50

PULLFRONT_Y=Y3+Y1
PULLFRONT_DELAY = 5 / 1000    
ROTATION_DELAY  = 300 / 1000


def goToInitialPosition():
    leg.goToXYZ(    SPACING_X   ,   Y3  ,   LEG_HEIGHT    ,   leg.LEG_A   )
    leg.goToXYZ(    SPACING_X   ,  -Y1  ,   LEG_HEIGHT    ,   leg.LEG_B   )
    leg.goToXYZ(    SPACING_X   ,   Y1  ,   LEG_HEIGHT    ,   leg.LEG_C   )
    leg.goToXYZ(    SPACING_X   ,  -Y3  ,   LEG_HEIGHT    ,   leg.LEG_D   )

def readyStep1():        # 7     ----->Home Position    
    leg.goToXYZ(    SPACING_X   ,   Y3  ,   LEG_HEIGHT    ,   leg.LEG_A   )
    leg.goToXYZ(    SPACING_X   ,  -Y1  ,   LEG_HEIGHT    ,   leg.LEG_B   )
    leg.goToXYZ(    SPACING_X   ,   Y1  ,   LEG_HEIGHT    ,   leg.LEG_C   )
    leg.goToXYZ(    SPACING_X   ,  -Y3  ,   LEG_HEIGHT    ,   leg.LEG_D   )

def Step1():        # 1
    readyStep1()
    # Pickup Leg B and Step Forward 

    # Pickup
    leg.goToXYZ(    SPACING_X   ,  -Y1  ,   PICKUP_Z    ,   leg.LEG_B   )
    time.sleep(ROTATION_DELAY)
    # Rotate To Location Above the Target Y
    leg.goToXYZ(    SPACING_X   ,   Y3  ,   PICKUP_Z    ,   leg.LEG_B   )
    time.sleep(ROTATION_DELAY)
    # Drop off the Leg
    leg.goToXYZ(    SPACING_X   ,   Y3  ,   LEG_HEIGHT    ,   leg.LEG_B   )
    time.sleep(ROTATION_DELAY)

    Shift1()

def Shift1():       # 2
    # Move All the Leg Backwards
    for i in range(1,PULLFRONT_Y):
        leg.goToXYZ(    SPACING_X   ,   Y3-i  ,   LEG_HEIGHT    ,   leg.LEG_A   )
        leg.goToXYZ(    SPACING_X   ,  -Y1-i  ,   LEG_HEIGHT    ,   leg.LEG_B   )
        leg.goToXYZ(    SPACING_X   ,   Y1-i  ,   LEG_HEIGHT    ,   leg.LEG_C   )
        leg.goToXYZ(    SPACING_X   ,  -Y3-i  ,   LEG_HEIGHT    ,   leg.LEG_D   )
        time.sleep(PULLFRONT_DELAY)


def readyStep2():
    # Ready For the Next Step
    leg.goToXYZ(    SPACING_X   , -Y1  ,   LEG_HEIGHT    ,   leg.LEG_A   )
    leg.goToXYZ(    SPACING_X   ,  Y3  ,   LEG_HEIGHT    ,   leg.LEG_B   )
    leg.goToXYZ(    SPACING_X   , -Y3  ,   LEG_HEIGHT    ,   leg.LEG_C   )
    leg.goToXYZ(    SPACING_X   , -Y2  ,   LEG_HEIGHT    ,   leg.LEG_D   )
    

def Step2():        # 3
    readyStep2()
    # Pickup Leg D and Step Forward 

    # Pickup
    leg.goToXYZ(    SPACING_X   ,  -Y2  ,   PICKUP_Z    ,   leg.LEG_D   )
    time.sleep(ROTATION_DELAY)
    # Rotate To Location Above the Target Y
    leg.goToXYZ(    SPACING_X   ,   Y1  ,   PICKUP_Z    ,   leg.LEG_D   )
    time.sleep(ROTATION_DELAY)
    # Drop off the Leg
    leg.goToXYZ(    SPACING_X   ,   Y1  ,   LEG_HEIGHT    ,   leg.LEG_D   )
    time.sleep(ROTATION_DELAY)


def Step3():        # 4
    # Pickup Leg A and Step Forward 

    # Pickup
    leg.goToXYZ(    SPACING_X   ,  -Y1  ,   PICKUP_Z    ,   leg.LEG_A   )
    time.sleep(ROTATION_DELAY)
    # Rotate To Location Above the Target Y
    leg.goToXYZ(    SPACING_X   ,   Y2  ,   PICKUP_Z    ,   leg.LEG_A   )
    time.sleep(ROTATION_DELAY)
    # Drop off the Leg
    leg.goToXYZ(    SPACING_X   ,   Y2  ,   LEG_HEIGHT   ,   leg.LEG_A   )
    time.sleep(ROTATION_DELAY)

    Shift3()

def Shift3():       # 5
    # Move All the Leg Backwards
    for i in range(1,PULLFRONT_Y):
        leg.goToXYZ(    SPACING_X   ,   Y2-i  ,   LEG_HEIGHT    ,   leg.LEG_A   )
        leg.goToXYZ(    SPACING_X   ,   Y3-i  ,   LEG_HEIGHT    ,   leg.LEG_B   )
        leg.goToXYZ(    SPACING_X   ,  -Y3-i  ,   LEG_HEIGHT    ,   leg.LEG_C   )
        leg.goToXYZ(    SPACING_X   ,   Y1-i  ,   LEG_HEIGHT    ,   leg.LEG_D   )
        time.sleep(PULLFRONT_DELAY)


def readyStep4():
    # Ready For the Next Step
    leg.goToXYZ(    SPACING_X   ,  Y3  ,   LEG_HEIGHT    ,   leg.LEG_A   )
    leg.goToXYZ(    SPACING_X   , -Y1  ,   LEG_HEIGHT    ,   leg.LEG_B   )
    leg.goToXYZ(    SPACING_X   , -Y2  ,   LEG_HEIGHT    ,   leg.LEG_C   )
    leg.goToXYZ(    SPACING_X   , -Y3  ,   LEG_HEIGHT    ,   leg.LEG_D   )


def Step4():        # 6
    readyStep4()
    # Pickup Leg C and Step Forward 

    # Pickup
    leg.goToXYZ(    SPACING_X   ,  -Y2  ,   PICKUP_Z    ,   leg.LEG_C   )
    time.sleep(ROTATION_DELAY)
    # Rotate To Location Above the Target 
    leg.goToXYZ(    SPACING_X   ,   Y1  ,   PICKUP_Z    ,   leg.LEG_C   )
    time.sleep(ROTATION_DELAY)
    # Drop off the Leg
    leg.goToXYZ(    SPACING_X   ,   Y1  ,   LEG_HEIGHT   ,  leg.LEG_C   )
    time.sleep(ROTATION_DELAY)


def goForward():
    print("Motion : Step 1")
    Step1()
    print("Motion : Step 2")
    Step2()
    print("Motion : Step 3")
    Step3()
    print("Motion : Step 4")
    Step4()

if __name__=="__main__":
    # leg.init()
    goToInitialPosition()
    while True:
        goForward()
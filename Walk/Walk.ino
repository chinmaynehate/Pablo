#include <megaPinDefs.h>
#include <Servo.h>
#include<math.h>



// CONSTANTS
#define  pi  3.141592653589793;
#define SHIFT_ALL_STEP_SIZE 0.3
#define SHIFT_ALL_STEP_DELAY 30
#define STEP_IN_Y_DELAY 300
#define STEP_IN_Y_HEIGHT -9.5


const float X = 4;
const float Z = -13;

// Link Lengths
float l1 = 4.56;
float l01=0.6;
float l2=4.575;
float l3=8.4;

// Inverse Params
float r1 = l01;
float r2 = l2;
float r3 = l3;

// Output Float Angles 
float th1,th02,th12,th03,th13;
// Storage Angles
float currenty_a,currenty_b,currenty_c,currenty_d;

Servo myservo[12];

float currentY;
void getInverse(float,float,float);
void setLegPoistion(char,float,float,float);
void StepInY(char,float,float);
void shiftAll(float);
void attachServos(void);
void writeServoAngle(int,int);
void goToStartingPos(void);
void walk();


float InitialY_a=1.8,InitialY_b=-0.9,InitialY_c=0.9,InitialY_d=-1.8;

float shiftDist=1.0;
void walk()
{
    //Assume Bot is in Starting Postion  

    // Step 1   -Step Leg B Froward
    StepInY('B',-0.9,4.5);
\
    // Shift 1  -Push Forward
    shiftAll(shiftDist);

    // Step 2 - Step Leg D Forward
    StepInY('D',-4.5,0.9);

    // Step 3 - Step Leg A Forward
    StepInY('A',-0.9,4.5);

    // Shift 2 - Push Forward
    shiftAll(shiftDist);

    // Step 4 - Step Leg C Forward
    StepInY('C',-4.5,0.9);

}


void goToStartingPos()
{Serial.println("Going to Standard Position");
  
    setLegPoistion('A',X,InitialY_a,Z);
    setLegPoistion('B',X,InitialY_b,Z);
    setLegPoistion('C',X,InitialY_c,Z);
    setLegPoistion('D',X,InitialY_d,Z);

    
//    setLegPoistion('A',X,0,Z);
//    setLegPoistion('B',X,0,Z);
//    setLegPoistion('C',X,0,Z);
//    setLegPoistion('D',X,0,Z);
    currenty_a=InitialY_a;
    currenty_b=InitialY_b;
    currenty_c=InitialY_c;
    currenty_d=InitialY_d;

}


void StepInY(char legIndex,float from,float to)
{
    // Pull Up
    setLegPoistion(legIndex,X,from,STEP_IN_Y_HEIGHT);
    delay(STEP_IN_Y_DELAY);
    // Set the Leg Postion above the Target Y
    setLegPoistion(legIndex,X,to,STEP_IN_Y_HEIGHT);
    delay(STEP_IN_Y_DELAY);
    // Set the Leg Position to the Target Y
    setLegPoistion(legIndex,X,to,Z);
    delay(STEP_IN_Y_DELAY);
    
}

void shiftAll(float shiftSize)
{
    float shiftY = 0;
    while(shiftY<shiftSize)
    {
        shiftY+=SHIFT_ALL_STEP_SIZE;
        setLegPoistion('A',X,currenty_a-shiftY,Z);
        setLegPoistion('B',X,currenty_b-shiftY,Z);
        setLegPoistion('C',X,currenty_c-shiftY,Z);
        setLegPoistion('D',X,currenty_d-shiftY,Z);
        delay(SHIFT_ALL_STEP_DELAY);
    }

    currenty_a = currenty_a - shiftY + SHIFT_ALL_STEP_SIZE;
    currenty_b = currenty_b - shiftY + SHIFT_ALL_STEP_SIZE;
    currenty_c = currenty_c - shiftY + SHIFT_ALL_STEP_SIZE;
    currenty_d = currenty_d - shiftY + SHIFT_ALL_STEP_SIZE;

}

void setLegPoistion(char LegIndex,float tx,float ty,float tz)
{
  Serial.println("Shifting Leg Position");
    int sIndex;
    switch(LegIndex)
    {
        case 'A':sIndex=0;
                currenty_a=ty;
                break;
        case 'B':sIndex=3;
                currenty_b=ty;
                break;
        case 'C':sIndex=6;
                currenty_c=ty;
                break;
        case 'D':sIndex=9;
                currenty_d=ty;
                break;
        default: ;
    }
    getInverse(tx,ty,tz);
    int t1=int(th1);
    int t2=int(th02);
    int t3=int(th03);
    writeServoAngle(t1,sIndex);
    writeServoAngle(t2,sIndex+1);
    writeServoAngle(t3,sIndex+2);
}


// InverseK Function
void getInverse(float x,float y,float z)
{
    z+=l1;   //Shift of Origin 

    th1 = atan2f(y,x);

    float A = -z;
    float B=r1 -(x*cosf(th1) + y*sinf(th1));
    float D = (2*r1*(x*cosf(th1) + y*sinf(th1)) + powf(r3,2) - powf(r2,2) - powf(r1,2) -powf(z,2) - powf((x*cosf(th1)+y*sinf(th1)),2) )/(2*r2);

    float phi = atan2f(B,A);

    th02 = -phi + atan2f(D, + powf((powf(A,2)+powf(B,2) - powf(D,2)),0.5));
    th12 = -phi + atan2f(D, - powf((powf(A,2)+powf(B,2) - powf(D,2)),0.5));
    
    th03 = atan2f( z-r2*sinf(th02) , x*cosf(th1) + y*sinf(th1) - r2*cosf(th02) -r1 ) -th02 ;
    th13 = atan2f( z-r2*sinf(th12) , x*cosf(th1) + y*sinf(th1) - r2*cosf(th12) -r1 ) -th12 ;


    th1 *=180/pi;
    th02*=180/pi;
    th12*=180/pi;
    th03*=180/pi ;
    th13*=180/pi ;

    th03+=90;
    th13+=90;

    Serial.print("For (");Serial.print(x);Serial.print(",");Serial.print(y);Serial.print(",");Serial.print(z);
    Serial.print(":");Serial.print(th1);Serial.print(",");Serial.print(th02);Serial.print(",");Serial.println(th03);
    
}


//int servoFixedPoints[12] = {70, 90, 100, 125, 75, 80,  46 ,  105, 115, 96, 70,100} ;
//int servoFixedPoints[12] = {70, 90, 100, 125, 75, 80,   46 ,  100 , 100, 96, 110,68} ;
//int servoFixedPoints[12] = {70, 98, 130, 125, 75, 80,   40 ,  110 , 78, 98, 115,127} ;
int servoFixedPoints[12] = {70, 98, 130, 125, 75, 80,   40 ,  85 , 78, 98, 115,127} ;
void writeServoAngle(int angle,int index)
{
    if(index == 0 || index==2 ||index==4 ||index==8 ||index==9 ||index==10)
    {
        myservo[index].write(servoFixedPoints[index] + angle);
    }
    else
    {
        myservo[index].write(servoFixedPoints[index] - angle);
    }
   
}

void setAngle(int angle,int legIndex,int servoIndex)
{
    writeServoAngle(angle,legIndex*3+servoIndex);
}


/*void attachServos()
{
  /////AAAAAAAAAAAAAAAAAAAA//////////////      FRONT LEFT
  myservo[0].attach(D2);//  TOP
  myservo[1].attach(D3);//  MIDDLE
  myservo[2].attach(D4);//  BOTTOM

  ////BBBBBBBBBBBBBBBBBBBBB///////            FRONT RIGHT
  myservo[3].attach(D7);//   TOP
  myservo[4].attach(D6);//   MIDDLE
  myservo[5].attach(D5);//   BOTTOM
 ////////////////////////////////////////// 

 ////CCCCCCCCCCCCCCCCCCCCCCC/////////        BACK RIGHT
  myservo[6].attach(G3);//   TOP
  myservo[7].attach(G1);//   MIDDLE
  myservo[8].attach(G2);//   BOTTOM
    ////////////////////////////////////////// 
  
    ///////////////////////////////////////////////  
  ////DDDDDDDDDDDDDDDDDDDDDD////          BACK LEFT
  myservo[9].attach(G0);//    TOP   
  myservo[10].attach(D0);//   MIDDLE
  myservo[11].attach(D1);//   BOTTOM
    //  ////////////////////////////////////////////
}*/


void attachServos()
{
  /////AAAAAAAAAAAAAAAAAAAA//////////////      FRONT LEFT
  myservo[0].attach(D4);//  TOP
  myservo[1].attach(D6);//  MIDDLE
  myservo[2].attach(D7);//  BOTTOM

  ////BBBBBBBBBBBBBBBBBBBBB///////            FRONT RIGHT
  myservo[3].attach(D2);//   TOP
  myservo[4].attach(B4);//   MIDDLE
  myservo[5].attach(D0);//   BOTTOM
 ////////////////////////////////////////// 

 ////CCCCCCCCCCCCCCCCCCCCCCC/////////        BACK RIGHT
  myservo[6].attach(C2);//   TOP
  myservo[7].attach(B5);//   MIDDLE
  myservo[8].attach(C0);//   BOTTOM
////////////////////////////////////////// 
  
///////////////////////////////////////////////  
  ////DDDDDDDDDDDDDDDDDDDDDD////          BACK LEFT
  myservo[9].attach(E3);//    TOP   
  myservo[10].attach(E4);//   MIDDLE
  myservo[11].attach(C7);//   BOTTOM
//////////////////////////////////////////////
}

void setup()
{
  Serial.begin(115200);
  Serial.println("In Setup");
    attachServos();
    goToStartingPos();
    
}

void loop()
{
//  Serial.println("Looping");
//  walk(); 
     //turn();
     turn_right();
//go2StablePosition();
//walk();
}


const int stableTopAngle = 30;
void go2StablePosition(void)
{
    // Leg A 
    setAngle(stableTopAngle,0,0);
    setAngle(0,0,1);
    setAngle(0,0,2);

    // Leg B 
    setAngle(stableTopAngle,1,0);
    setAngle(0,1,1);
    setAngle(0,1,2);

    // Leg C 
    setAngle(-stableTopAngle,2,0);
    setAngle(20,2,1);
    setAngle(0,2,2);

    // Leg D 
    setAngle(-stableTopAngle,3,0);
    setAngle(0,3,1);
    setAngle(0,3,2);
}


const int legPickupAngle = 70;
const int turningAngle = 40;
const int pickupDelay = 100;
void turn_right()
{
    // Turn Left
    // Pickup Leg A and Rotate
    setAngle(legPickupAngle,0,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
//    waitForEnter();
    setAngle(stableTopAngle + turningAngle,0,0);    //Rotate Top 
    delay(pickupDelay);
//    waitForEnter();
    setAngle(0,0,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);
    waitForEnter();

    // Pickup Leg C and Rotate
    setAngle(legPickupAngle,2,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
//    waitForEnter();
    setAngle(-stableTopAngle - turningAngle,2,0);    //Rotate Top 
    delay(pickupDelay);
//    waitForEnter();
    setAngle(0,2,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);
    waitForEnter();

    // Pickup Leg B and Rotate
    setAngle(legPickupAngle,1,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
//    waitForEnter();
    setAngle(stableTopAngle - turningAngle,1,0);    //Rotate Top 
    delay(pickupDelay);
//    waitForEnter();
    setAngle(0,1,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);
    waitForEnter();
    

    // Pickup Leg D and Rotate
    setAngle(legPickupAngle,3,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
//    waitForEnter();
    setAngle(-stableTopAngle + turningAngle,3,0);    //Rotate Top 
    delay(pickupDelay);
//    waitForEnter();
    setAngle(0,3,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);
    waitForEnter();
    

    // Rotate All Back to Normal Position
    setAngle(stableTopAngle,0,0);
    setAngle(stableTopAngle,1,0);
    setAngle(-stableTopAngle,2,0);
    setAngle(-stableTopAngle,3,0);
    delay(pickupDelay+100);
    waitForEnter();

//    go2StablePos/ition();                   

}







void turn_left()
{
    // Turn Left
    // Pickup Leg A and Rotate
    setAngle(legPickupAngle,0,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
    setAngle(stableTopAngle - turningAngle+30,0,0);    //Rotate Top 
    delay(pickupDelay);
    setAngle(0,0,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);

    // Pickup Leg B and Rotate
    setAngle(legPickupAngle,1,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
    setAngle(stableTopAngle + turningAngle,1,0);    //Rotate Top 
    delay(pickupDelay);
    setAngle(0,1,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);
    
    // Pickup Leg D and Rotate
    setAngle(legPickupAngle,3,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
    setAngle(-stableTopAngle - turningAngle,3,0);    //Rotate Top 
    delay(pickupDelay);
    setAngle(0,3,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);
    
    // Pickup Leg C and Rotate
    setAngle(legPickupAngle,2,1);                   //pickup using 2nd Servo
    delay(pickupDelay);
    setAngle(-stableTopAngle + turningAngle,2,0);    //Rotate Top 
    delay(pickupDelay);
    setAngle(0,2,1);                                //Drop off the 2nd Servo of the Corresponding Leg
    delay(pickupDelay);

    
   
    
    

    // Rotate All Back to Normal Position
    setAngle(stableTopAngle,0,0);
    setAngle(stableTopAngle,1,0);
    setAngle(-stableTopAngle,2,0);
    setAngle(-stableTopAngle,3,0);
    delay(pickupDelay+200);

//    go2StablePos/ition();                   

}


int waitForEnter()
{
//  return 0;
    while(true)
    {
        if(Serial.available())
        {
          while(Serial.available())
          {
            Serial.read();
          }
            Serial.println("Input Received !");
//            delay(100);
            return 0;
        }
    }
  
}

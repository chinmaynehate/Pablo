#include <megaPinDefs.h>

#include <Servo.h>

#define COMM_DELAY 3

#define LOG(X) Serial.print(X);
#define LOGln(X) Serial.println(X);


Servo myservo[12];

void setup() 
{
    Serial.begin(115200);
    attachServos();
    goToMotionBeginPosition();
   
}


void loop() 
{

 readIncommingData();
}


void goToMotionBeginPosition()
{
  myservo[0].write(5);   //decrease(subtract an angle) to take the leg back +
  myservo[1].write(90);     //increase(add an angle) to take the leg down   -
  myservo[2].write(100);    //increase(add an angle) to expand the leg  +

  myservo[3].write(180);    //increase(add an angle) to take the leg back  -
  myservo[4].write(91);       //decrease(subtract an angle) to take the leg down  +
  myservo[5].write(80);   //decrease(subtract an angle) to expand the leg   -

  myservo[6].write(15);    ///inrease(add an angle) to take the leg back    -
  myservo[7].write(54);    ///increase(add an angle) to take the leg down   -
  myservo[8].write(100);   //increase(add an angle) to expand the leg       +

  myservo[9].write(155);   //decrease(subtract an angle) to take the leg back   +
  myservo[10].write(85);   //decrease(subtract an angle) to take the leg down   +
  myservo[11].write(70);  //decrease(subtract an angle to expand the leg    -
}


void readIncommingData()
{
  
  String input;
  bool isReceiving = false;
  while(Serial.available())
  {
    isReceiving=true;
    char c = Serial.read();
    input+=c;
  }


  if(isReceiving)  {
    Serial.print("Received:");
    Serial.println(input);
    long int msg = input.toInt();
    
    int servoIndex = abs(msg%10);
    msg/=10;
    int legIndex = abs(msg % 10);
    msg/=10;
    long int angle = msg;
    
    writeServoAngle(angle,legIndex*3+servoIndex);

    LOG("Writing Angle:");
    LOG(angle);
    LOG(",Leg Index:");
    LOG(legIndex)
    LOG(",ServoIndex:");
    LOGln(servoIndex);
    
    
    input="";
    isReceiving=false;
  }


  delay(5);

}

int servoFixedPoints[12] = {5,90,100,180,91,80,15,54,100,155,85,70};

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


void attachServos()
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
  myservo[7].attach(G2);//   MIDDLE
  myservo[8].attach(G1);//   BOTTOM
////////////////////////////////////////// 
  
///////////////////////////////////////////////  
  ////DDDDDDDDDDDDDDDDDDDDDD////          BACK LEFT
  myservo[9].attach(G0);//    TOP
  myservo[10].attach(D0);//   MIDDLE
  myservo[11].attach(D1);//   BOTTOM
//////////////////////////////////////////////
}

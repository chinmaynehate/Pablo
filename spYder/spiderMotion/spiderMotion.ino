#include <megaPinDefs.h>

#include <Servo.h>


#define TEST_SERVO_INDEX 12
#define dels 300

Servo myservo[13];
void setup() 
{
  attachServos();
  goToMotionBeginPosition();
  delay(1000);
}


int pos = 0;

void loop() 
{
  Motion();
}

int a0set=5;
int a1set = 90-20;

int b0set=175;
int b1set = 76+35;

int c0set=15;
int c1set = 75-20;

int d0set=130;
int d1set = 50+35;


void Motion()
{

  //Pickup Leg A and Move it Forward 
  int pickupAngle= -35;

  

  myservo[1].write(a1set + pickupAngle);  //Pickup Leg with Middle Servo
  delay(dels);
  myservo[0].write(a0set+70);    //Rotate the Top Most Servo
  delay(dels);
  myservo[1].write(a1set);                //Drop the Leg Back on the Ground
  delay(dels);

  //Rotate the Entire Body


  myservo[0].write(a0set + 30);   //a0
  myservo[3].write(b0set -0);   //b0
  myservo[6].write(c0set   + 45);         //c0
  myservo[9].write(d0set - 30);     //d0
  delay(dels);

  //Parallel Leg C to the Body
  

  myservo[7].write(c1set + pickupAngle);     //Pickup the Leg
  delay(dels);
  myservo[6].write(c0set + 0);              //Rotate the Leg Parallel to the Body   //////////////////+make parallel angle
  delay(dels);
  myservo[7].write( c1set );                 //Drop the Leg
  delay(dels);


  //Pickup Leg B and Move it Forward
  

//  myservo[4].write(b1set - pickupAngle-                                                                           40);  //Pickup Leg with Middle Servo
myservo[4].write(180);  //Pickup Leg with Middle Servo
  delay(dels);
  myservo[3].write(b0set-70);    //Rotate the Top Most Servo
  delay(dels);
  myservo[4].write(b1set);                //Drop the Leg Back on the Ground
  delay(dels);

  //Rotate the Entire Body
  

  myservo[0].write(a0set+0);
  myservo[3].write(b0set-30);
  myservo[6].write(c0set+30);
  myservo[9].write(d0set-45);
  delay(dels);

  
  //Move Leg D Parallel to the Body

  myservo[10].write(d1set+60);     //Pickup the Leg
  delay(dels);
  myservo[9].write(d0set+0);              //Rotate the Leg Parallel to the Body
  delay(dels);
  myservo[10].write(d1set);                 //Drop the Leg
  delay(dels);

}

void goToMotionBeginPosition()
{
  myservo[0].write(5+30);
  myservo[1].write(90-20);
  myservo[2].write(100-20);

  myservo[3].write(175-30);   
  myservo[4].write(76+35);  
  myservo[5].write(80+20);   

  myservo[6].write(15+30);
  myservo[7].write(75-30);
  myservo[8].write(120-20);

  myservo[9].write(130-30+30);
  myservo[10].write(50+35);
  myservo[11].write(70+20);
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

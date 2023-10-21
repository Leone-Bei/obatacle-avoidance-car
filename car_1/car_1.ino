#include <math.h>
#define M_left1 10
#define M_left2 11
#define M_right1 6
#define M_right2 7
#define tl
#define tr
#define tf
#define ml
#define mr 
#define mf
#define turn_constant=0.5
#define speed_constant=1
#define v_r
#define v_l
#define turn_radius
#define speed


const int front_dis=40
const int infinite_dis=100
const float L 13.3

void setup() {
  pinMode(M_left1, OUTPUT);
  pinMode(M_left2, OUTPUT);
  pinMode(M_right1, OUTPUT);
  pinMode(M_right2, OUTPUT);
  pinMode(tl, OUTPUT);
  pinMode(el, INPUT);
  pinMode(tr, OUTPUT);
  pinMode(er, INPUT);
  pinMode(tf, OUTPUT);
  pinMode(ef, INPUT);
  Serial.begin(9600);

}

double USRead(int trig,int echo){
  //pinMode(trig,OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  //pinMode(echo,INPUT);
  double t=pulseIn(echo,HIGH);
  double distance=t*0.0343/2;
  return distance;
}

void loop() {
    double lenl=USRead(tl, el);
    double lenr=USRead(tr, er);
    double lenf=USRead(tf, ef);
    double delta=abs(lenl-lenr);
    turn_radius=turn_constant/delta;
    speed=lenf*speed_turn;
    if(lenr>lenf)
    {
      v_r=((2*turn_radius-L)/(2*(turn_radius-L)))*speed;//右转，右轮速度小
      v_l=speed*2-v_r;
      // analogWrite(M_left1,);
      // analogWrite(M_left2,);
      // analogWrite(M_right1,);
      // analogWrite(M_right2,);
      delay(500); 
    }
    else if(lenr<lenf)
    {
      v_l=((2*turn_radius-L)/(2*(turn_radius-L)))*speed;
      v_r=speed*2-v_r;
      // analogWrite(M_left1,);
      // analogWrite(M_left2,);
      // analogWrite(M_right1,);
      // analogWrite(M_right2,);
      delay(500); 
    }
    else if(lenr<lenf)
    {
      v_r=speed*2;
      v_l=speed*2;
      // analogWrite(M_left1,);
      // analogWrite(M_left2,);
      // analogWrite(M_right1,);
      // analogWrite(M_right2,);
      delay(500); 
    }
}
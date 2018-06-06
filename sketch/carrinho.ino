#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>

// Motors defines
// Left
#define ENA 5
#define IN1 7
#define IN2 8

// Right
#define ENB 6
#define IN3 9
#define IN4 11

#define MAX_VEL 220
#define MAX_VEL_ANGULAR 180
#define OffTime 250

ros::NodeHandle nh;

float mr = 0, ml = 0;

// Time
long prev = 0;
long current = 0;

void acionaMotorEsquerdo(int pwm){
  bool forward = (pwm > 0);
  if (pwm < 0) pwm *= -1;
  
  if (forward){
    digitalWrite(IN1, HIGH);    
    digitalWrite(IN2, LOW);
    analogWrite(ENA, pwm);
  }
  else{
    digitalWrite(IN1, LOW);    
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, pwm);
  }  
}

void acionaMotorDireito(int pwm){
  bool forward = (pwm > 0);
  if (pwm < 0) pwm *= -1;
  
  if (forward){
    digitalWrite(IN3, LOW);    
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, pwm);
  }
  else{
    digitalWrite(IN3, HIGH);    
    digitalWrite(IN4, LOW);
    analogWrite(ENB, pwm);
  }  
}

void teleopCmdVelCb(const geometry_msgs::Twist& msg){
  prev = current;
  if (msg.linear.x > 0 || msg.linear.x < 0)
  {
    mr = MAX_VEL * (msg.linear.x > 0 ? 1 : -1);
    ml = MAX_VEL * (msg.linear.x > 0 ? 1 : -1);
  }
  else if (msg.angular.z > 0)
  {
      ml = -MAX_VEL_ANGULAR;
      mr = MAX_VEL_ANGULAR;
  }
  else if (msg.angular.z < 0)
  {
      ml = MAX_VEL_ANGULAR;
      mr = -MAX_VEL_ANGULAR;
  }
}

ros::Subscriber<geometry_msgs::Twist> sub_teleop("mybot/teleop", teleopCmdVelCb);

void setup(){
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  
  
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub_teleop);
}

void loop(){
  nh.spinOnce();
  current = millis();
  if (current - prev >= OffTime){
    ml = 0;
    mr = 0;
  }
  acionaMotorEsquerdo(ml);
  acionaMotorDireito(mr);
}

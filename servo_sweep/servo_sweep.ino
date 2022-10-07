#include <Servo.h>

Servo lowerLeg;  // create servo object to control a servo
Servo upperLeg;  // create servo object to control a servo
// twelve servo objects can be created on most boards

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  lowerLeg.attach(11);  // attaches the servo on pin 9 to the servo object
  lowerLeg.write(61.2);
  upperLeg.attach(12);  // attaches the servo on pin 9 to the servo object
  upperLeg.write(118.2);
}

void loop() {
  // put your main code here, to run repeatedly:
//  for (pos = 60; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    lowerLeg.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 60; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    upperLeg.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  
//  for (pos = 120; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
//    lowerLeg.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 120; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
//    upperLeg.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
  for (float x = 0.0; x <= 100.0; x += 0.1) {
    float y = 120.0;
    Serial.print("x ");
    Serial.print(x);
    Serial.print(" y ");
    Serial.print(y);
    Serial.print("\n");
    invKin(x, y);             
    delay(5);                      
  }

  for (float x = 100.0; x >= 0.0; x -= 0.1) {
    float y = 120 - 50 * sin(x * PI / 100);
    Serial.print("x ");
    Serial.print(x);
    Serial.print(" y ");
    Serial.print(y);
    Serial.print("\n");
    invKin(x, y);             
    delay(5);                      
  }
  
}

void invKin(float x, float y){
  float l1 = 124.0;
  float l2 = 80.0;
  float delta1 = 170.0;
  float delta2 = 83.0;
  float len = sqrt(x*x + y*y);
    
  float alpha = atan2(y, x) * RAD_TO_DEG;
  //Serial.print("alpha ");
  //Serial.print(alpha);
  //Serial.print("\n");
  float beta = acos((len*len + l1*l1 - l2*l2)/(2 * len * l1)) * RAD_TO_DEG;
  //Serial.print("beta ");
  //Serial.print(beta);
  //Serial.print("\n");
  float gamma = acos((l1*l1 + l2*l2 - len*len)/(2* l1 * l2)) * RAD_TO_DEG;
  //Serial.print("gamma ");
  //Serial.print(gamma);
  //Serial.print("\n");

  float phi1 = alpha - beta;
  float phi2 = 90 - gamma;

  float alpha1 = delta1 - phi1 * 2.85;
  float alpha2 = delta2 - phi2;

  Serial.print("alpha1 ");
  Serial.print(alpha1);
  Serial.print("\n");
  Serial.print("alpha2 ");
  Serial.print(alpha2);
  Serial.print("\n");
  cmdServos(alpha1, alpha2);
}

void cmdServos(float alpha1, float alpha2){
  lowerLeg.write(alpha2); 
  upperLeg.write(alpha1); 
}

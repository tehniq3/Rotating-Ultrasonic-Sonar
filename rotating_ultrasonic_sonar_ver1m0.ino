/* Arduino Basics - #7 - Rotating Ultrasonic Sonar: http://apcmag.com/arduino-basics-7-turning-heads-with-arduino.htm/
 * Code by Darren Yates - 18-Feb-2015
 * small changes by Nicu FLORICA (niq_ro) - 19-Apr-2016: http://www.tehnic.go.ro & http://www.arduinotehiq.com/
*/
#define TRIG_PIN A0
#define ECHO_PIN A1
#include <Servo.h> 
#include <NewPing.h>

#define MAX_DISTANCE 300
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myServo;  // create servo object to control a servo 
char dist[3];
char rot[3];
int rotation = 0;
String output = "";

void setup() {
  pinMode (TRIG_PIN, OUTPUT);
  pinMode (ECHO_PIN, INPUT);
  myServo.attach(4);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  Serial.println("===== Ultrasonic rotating sonar =====");
  myServo.write(90);
  delay(2000);
}

void loop() { 
  // scan right to left
  for (int deg = 10; deg < 170; deg+=5) {
    myServo.write(deg);
    delay(500);
    displaySonar(deg);
  }

  // scan left to right
  for (int deg = 170; deg > 10; deg-=5) {
    myServo.write(deg);
    delay(500);
    displaySonar(deg);
  }
}

void displaySonar(int degrees) {
  int distance = sonar.ping_cm(); 
  delay(30);
  if (distance <= 0) distance = MAX_DISTANCE; 
  
  sprintf(dist,"%3d",distance);
  Serial.print("Range:");
  Serial.print(dist);
  Serial.print("cm / ");
  sprintf(rot,"%3d",degrees);
  Serial.print(rot);
  Serial.print("deg:");

  for (int dloop = 0; dloop < distance/4; dloop++) {
    Serial.print("-");
  }
  Serial.println("=");
}

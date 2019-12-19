#include <Wire.h>
#include <Sp
arkFun_ADXL345.h>
#define LEFT_LED  12
#define RIGHT_LED  11

ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

int x,y,z;
float xg,yg,zg;
float soh;
float tilt;
float angle;
String dir;

uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

void setup(){

  Serial.begin(9600);
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  digitalWrite(LEFT_LED, HIGH);
  digitalWrite(RIGHT_LED, HIGH);
}

void blinkON(){
  digitalWrite(LEFT_LED,HIGH);
  digitalWrite(RIGHT_LED,HIGH);
  delay(500);
  digitalWrite(LEFT_LED,LOW);
  digitalWrite(RIGHT_LED,LOW);
  delay(500);
}
void blinkOFF(){
  
  digitalWrite(LEFT_LED,LOW);
  digitalWrite(RIGHT_LED,LOW);
  
}
void loop(){
  //Boring accelerometer stuff   
  adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
  xg = x*0.0039;
  yg = y*0.0039;
  zg = z*0.0039;
  // Output x,y,z values - Commented out
Serial.print("X Value:"); Serial.print(xg);
Serial.print(", Y Value: "); Serial.print(yg);
Serial.print(", Z Value: "); Serial.println(zg);
soh = yg/zg;

tilt = atan(soh)*57.296;
if (abs(tilt) > 90) {
  }
  else {
    if (tilt < 30) {
      dir = "Up";
      angle = abs(tilt);
      blinkOFF();
    } else {
      dir = "Down";
      angle = tilt;
      blinkON();
      tone(10,1000,1000);
      
    }
  }
Serial.print("Tilt Angle is: "); Serial.print(tilt); Serial.println(" degrees.");

 delay(250);
}

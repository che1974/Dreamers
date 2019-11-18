2
#include <Wire.h>
#include <Sp
arkFun_ADXL345.h>
//#include <LCD.h>
//#include <LiquidCrystal_I2C.h>
//#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
//#define BACKLIGHT_PIN     3
#define LEFT_LED  12
#define RIGHT_LED  11
//#define Rs_pin  0
//#define D4_pin  4
//#define D5_pin  5
//#define D6_pin  6
//#define D7_pin  7
//LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

int x,y,z;
float xg,yg,zg;
float soh;
float tilt;
float angle;
String dir;

uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

void setup(){
//  lcd.begin (16,2);
//  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
//  lcd.setBacklight(HIGH);
//  lcd.createChar(0, degree);
//  lcd.home (); 
//  lcd.print("Angle Meter");  
  Serial.begin(9600);
  adxl.powerOn();
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  digitalWrite(LEFT_LED, HIGH);
  digitalWrite(RIGHT_LED, HIGH);
 adxl.printAllRegister();
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
//    lcd.setCursor (0,1);        
//    lcd.print("                ");
//    lcd.setCursor (0,1);   
//    lcd.print("Tilt:Range Error");
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
//    lcd.setCursor (0,1);        
//    lcd.print("                ");
//    lcd.setCursor (0,1);   
//    lcd.print("Tilt:");lcd.print(angle);lcd.write(byte(0));lcd.print(dir);

  }
Serial.print("Tilt Angle is: "); Serial.print(tilt); Serial.println(" degrees.");

 delay(250);
}

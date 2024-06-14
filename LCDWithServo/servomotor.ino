#include <LiquidCrystal.h>

#include <Servo.h>

//variables
int brightness;
//input pins
int RS = 8;
int E = 9;
int D10 = 10;
int D11 = 11;
int D12 = 12;
int D13 = 13;
//functions

void Cycle180DegreesAndPrintToLCD();


LiquidCrystal lcd(RS, E, D10, D11, D12, D13);
Servo motor;


void setup() {
  // put your setup code here, to run once:
motor.attach(2); //attach to pin number 1
Serial.begin(9600);
lcd.begin(16,2);
}


void loop() {
  
  // put your main code here, to run repeatedly:
 Cycle180DegreesAndPrintToLCD();

  
 

}

void Cycle180DegreesAndPrintToLCD(){
  for(int i=0; i<=180; i+=10){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("degrees:");
    lcd.setCursor(0,1);
    lcd.print(i);
    motor.write(i);
    delay(200);
  }
  for(int j=180; j>=0; j-=10){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("degrees:");
    lcd.setCursor(0,1);
    lcd.print(j);
    motor.write(j);
    delay(200);
  }
 }

/*
void move90DegreesForwardThen45DegreesBackward(){
  for(int i=0; i<=90; i+=5 ){ //180 degrees
  Serial.println(i);
    motor.write(i);
    
    delay(100);//100 ms delay

  }
  for(int j=45; j>=0; j-=5){
    Serial.println(j);
    motor.write(j);
    delay(100);
     
  }
}
void moveMotor90Degrees(){

for(int i=0; i<=90; i+=5 ){ //180 degrees
  Serial.println(i);
    motor.write(i);
    
    delay(100);//100 ms delay

  }
  for(int j=90; j>=0; j-=5){
    Serial.println(j);
    motor.write(j);
    delay(100);
      
  }

}
*/

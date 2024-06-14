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
int lightValue=0;
int brightnessThreshold=100;

LiquidCrystal lcd(RS, E, D10, D11, D12, D13);
Servo motor;

void turnMotor90Degrees();

void setup() {
  // put your setup code here, to run once:
  pinMode(A1,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  motor.attach(4); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A1));
  lightValue=analogRead(A1);

  if(lightValue<brightnessThreshold){
    //light off, turn red light on
    analogWrite(A4,255);
    analogWrite(A3, 0);
    analogWrite(A2,0);
    turnMotor90Degrees();
  }else{
    //light on. turn green light on
    analogWrite(A4, 0);
    analogWrite(A3, 255);
    analogWrite(A2,0);
    
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Light Reading:");
  lcd.setCursor(0,1);
  lcd.print(analogRead(A1));
  delay(500);


  
}

void turnMotor90Degrees(){
  for(int i=0; i<=90;i+=5){
    motor.write(i);
    delay(50);
  }
  for(int j=90; j>=0; j-=5){
    motor.write(j);
     delay(50);
  }
}

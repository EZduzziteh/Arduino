#include <LiquidCrystal.h>

//lcd pins
int RS = 8;
int E = 9;
int D10 = 10;
int D11 = 11;
int D12 = 12;
int D13 = 13;

//Ultrasonic sensor pins
int echoPin=4;
int triggerPin=5;

//pushbutton pin
int buttonPin=2;

//variables
long distance=0;
int buttonPressed=0;

LiquidCrystal lcd(RS, E, D10, D11, D12, D13);

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin,INPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  buttonPressed=digitalRead(buttonPin); //check if button pressed
  
  if(buttonPressed){ 

    digitalWrite(triggerPin,LOW);
    delayMicroseconds(10);
    digitalWrite(triggerPin,HIGH);
    delayMicroseconds(20);
    digitalWrite(triggerPin,LOW);


    distance=pulseIn(echoPin,HIGH);
    long cm=((distance/2)/29.1); //convert reading to distance in cm

    Serial.print("distance: ");
    Serial.println(cm);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distance(cm): ");
    lcd.setCursor(0,1);
    lcd.print(cm);

    delay(100);
  }
}

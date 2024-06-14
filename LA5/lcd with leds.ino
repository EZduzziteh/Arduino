#include <LiquidCrystal.h>

int redLED = 3;
int blueLED = 5;
int greenLED = 6;

int brightness;
int RS = 7;
int E = 8;
int D10 = 10;
int D11 = 11;
int D12 = 12;
int D13 = 13;

int timer = 120000; //timer in milliseconds

LiquidCrystal lcd(RS ,E ,D10 ,D11, D12 ,D13 );


void setup() {
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
  
  // put your setup code here, to run once:
  lcd.begin(16,2);


}

void loop() {
 delay(500);

lcd.clear();
//fade red led up and down once
  for (int i=0 ; i<50 ; i++){

  analogWrite(redLED, i);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(i);

  lcd.setCursor(0,1);
  lcd.print("red fading up ");
  delay(200);
  }
  for (int i=50 ; i>0 ; i--){

  analogWrite(redLED, i);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(i);
  lcd.setCursor(0,1);
  lcd.print("red fading down ");
  delay(200);
  
  }
    //make sure red is off
    analogWrite(redLED,0);

  

//fade blue led up and down for 30 seconds using for loop

for(int j=0; j<30; j++){
    for (int i=0 ; i<50 ; i++){

    analogWrite(blueLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("blue fading up (30s)");
    delay(10);
    } 

    for (int i=50 ; i>0 ; i--){

    analogWrite(blueLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("blue fading down ");
    delay(10);
    
    }
  }
  //make sure blue is off
  analogWrite(blueLED,0);


  //fade 3 leds up and down one after the other using for loop

  //green cycle
    for (int i=0 ; i<50 ; i++){

    analogWrite(greenLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("green for up");
    delay(100);
    } 

    for (int i=50 ; i>0 ; i--){

    analogWrite(greenLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("green for down");
    delay(100);
    
    }
   //make sure green is off
    analogWrite(greenLED, 0);

    //blue cycle
    for (int i=0 ; i<50 ; i++){

    analogWrite(blueLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("blue for up");
    delay(100);
    } 

    for (int i=50 ; i>0 ; i--){

    analogWrite(blueLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("blue for down");
    delay(100);
    
    }  
    //make sure blue is off
    analogWrite(blueLED, 0);


    //red cycle
    for (int i=0 ; i<50 ; i++){

    analogWrite(redLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("red for up");
    delay(100);
    } 

    for (int i=50 ; i>0 ; i--){

    analogWrite(redLED, i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
    lcd.setCursor(0,1);
    lcd.print("red for down");
    delay(100);
    
    }
    //make sure red is off
      analogWrite(redLED, 0);
  

  //fade 3 leds up and down one after the other using while loop

  int brightness=0;
  //red
  while(brightness<50){
    analogWrite(redLED, brightness);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(brightness);
    lcd.setCursor(0,1);
    lcd.print("red while(R>B>G)");
    brightness++;
      delay(100);
  }
  while(brightness>0){
    analogWrite(redLED, brightness);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(brightness);
    lcd.setCursor(0,1);
    lcd.print("red while(R>B>G)");
    brightness--;
      delay(100);
  }
  //make sure red is off
 brightness=0;
  analogWrite(redLED, brightness);

  //green

while(brightness<50){
    analogWrite(greenLED, brightness);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(brightness);
    lcd.setCursor(0,1);
    lcd.print("green while");
    brightness++;
      delay(100);
  }

  
  while(brightness>0){
    analogWrite(greenLED, brightness);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(brightness);
    lcd.setCursor(0,1);
    lcd.print("green while");
    brightness--;
      delay(100);
  }
  //make sure green is off
  brightness=0;
  analogWrite(greenLED, brightness);


  //blue
  while(brightness<50){
    analogWrite(blueLED, brightness);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(brightness);
    lcd.setCursor(0,1);
    lcd.print("blue while up");
    brightness++;
      delay(100);
  }


  while(brightness>0){
    analogWrite(blueLED, brightness);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(brightness);
    lcd.setCursor(0,1);
    lcd.print("blue while down");
    brightness--;
    delay(100);
  }
  //make sure blue is off
  brightness=0;
  analogWrite(blueLED, brightness);
}



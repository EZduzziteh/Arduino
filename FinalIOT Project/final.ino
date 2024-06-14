#include <IRremote.hpp>
#include <Keypad.h>
#include <Adafruit_Keypad.h>
#include <Key.h>
#include <Servo.h>





unsigned long lockTimer=0.0;
unsigned long buttonTimer=0.0;

int passwordAttempts=3;


bool runLockTimer=false;
bool alarmIsSounding=false;
bool isInLearnMode=false;
bool isLocked=true;
bool buttonPressed=false;
bool buttonState=false;


char keypadChar;

String password="1";
String userInput="";
String remoteInput="";

byte const Rows=4;
byte const Columns=4;

char KeyPadArray[Rows][Columns]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};




//other Pins
int buttonPin=6;
int buzzer=8;


//Ultrasonic Sensor Pins
int trigger=11;
int echo=12;
int servoPin=13;
//LED pins
int blue=18;
int yellow=19;
int red=20;
int green=21;

//ir receiver pin
int receiverIR=30;

//keypad pins
byte rowPins[Rows]={39,41,43,45};
byte columnPins[Columns]={47,49,51,53};

//Keypad KeypadBlack = Keypad(makeKeymap(KeyPadArray), rowPins, columnPins, Rows, Columns);
Adafruit_Keypad customKp = Adafruit_Keypad(makeKeymap(KeyPadArray),rowPins,columnPins, Rows, Columns);

//receiver IR
IRrecv receiver(receiverIR);
decode_results results;

//Servomotor
Servo servo;


void setup() {
  // put your setup code here, to run once:

  
  pinMode(buzzer,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(buttonPin, INPUT);
  

  receiver.enableIRIn();
  customKp.begin();
  servo.attach(servoPin);
  Serial.begin(9600);

  delay(500);
  Serial.println("ready");
}

void loop() {

  

  //Check if alarm should be sounding
  if(alarmIsSounding){
   Alarm();
    
  }else{
    noTone(buzzer);
    //Make Sure All LEDS OFF
    digitalWrite(red,LOW);
    digitalWrite(blue,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,LOW);



    //Check if In Learn Mode
  if(isInLearnMode){
    digitalWrite(yellow,LOW);
    delay(200);
    digitalWrite(yellow, HIGH);
    delay(200);
    digitalWrite(yellow,LOW);
    delay(200);

  }

  

  }

  if(receiver.decode()){
    
      //This was code for getting the IR remote to work but I just could not get it working right. 
      //Every time i pressed a button it would issue a different command even if it was the same button being pressed which makes no sense. 
      //The weird part is i had this working and now all of a sudden it wont work at all so maybe my remote is faulty not sure.
    
    /*long value = receiver.decodedIRData.command;
     Serial.println(receiver.decodedIRData.command);
     IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();
  
    receiver.resume();
    */
   

     /* if(value==22){
        remoteInput+='0';
        PlayInputSound();
      }else if(value==12){
        remoteInput+='1';
        PlayInputSound();
      }else if(value==24){
        remoteInput+='2';
        PlayInputSound();
      }else if(value==94){
        remoteInput+='3';
        PlayInputSound();
      }else if(value==8){
        remoteInput+='4';
        PlayInputSound();
      }else if(value==28){
        remoteInput+='5';
        PlayInputSound();
      }else if(value==90){
        remoteInput+='6';
        PlayInputSound();
      }else if(value==66){
        remoteInput+='7';
        PlayInputSound();
      }else if(value==82){
        remoteInput+='8';
        PlayInputSound();
      }else if(value==74){
      remoteInput+='9';
      PlayInputSound();
      }else if(value==71){
      remoteInput+='A';
      PlayInputSound();
      }else if(value==67){
      remoteInput+='B';
      PlayInputSound();
      }else if(value==9){
      remoteInput+='C';
      PlayInputSound();
      }else if(value==13){
      remoteInput+='D';
      PlayInputSound();
      }else if(value==69){  //confirrm
      if(remoteInput==password){
        alarmIsSounding=false;
        PlayCorrectSound();
        Unlock();
        remoteInput="";
      }else{
        IncorrectPassword();
        remoteInput="";
      }
      }else if(value==7){ //reset
      remoteInput="";
      PlayInputSound();
      }

      Serial.println(remoteInput);
      
    */
    
  }

    UltrasonicSensorPing();
    

    long distance=pulseIn(echo,HIGH);
    long cm=((distance/2)/29.1); //convert reading to distance in cm
  
  if(!isLocked){
   
    if(!isInLearnMode){
      buttonState=digitalRead(buttonPin);
      
      if(!buttonPressed){
        if(buttonState==HIGH){
          StartButtonTimer();
        }
      }else{

        
        if(buttonState==LOW){
            StopButtonTimer();
        }else{

          
            //Serial.println(millis()-buttonTimer); timer for counting down relearn
            if(millis()-buttonTimer>=5000){
              
              StopButtonTimer();

              isInLearnMode=true;
              
            

              

            }
        }
      }
    }

    if(runLockTimer ){

      if(cm>10){ //if over threshold stop the lock timer

        StopLockTimer();
      }else{

       // Serial.println("elapsed time: ");
        //Serial.println(millis()-lockTimer);
        if(((millis()-lockTimer))>=10000){ //if 10 seconds have elapsed and under threshold, lock the box.
        StopLockTimer();
        Lock();
        }
      }


      
    }else{
    
      if(cm<10){ //if within threshold, start the lock timer.
        StartLockTimer();
      }

    }
  }

    
if(isLocked&&!alarmIsSounding){
 
    digitalWrite(blue,LOW);
    delay(200);
    digitalWrite(blue, HIGH);
    delay(200);
}

     

  

  

//keypad locked, handle keypad and password settings
    HandleKeyPad();
  

  


 
}

void Lock(){
 
  servo.write(90);
  
  //Serial.println("Lock");
  isLocked=true;
  passwordAttempts=3;
}

void Unlock(){

  servo.write(180);

  //Serial.println("Unlock");
 
  
 isLocked=false;
}

void StartButtonTimer(){
  buttonPressed=true;
  buttonTimer=millis();
  //Serial.println("Start buttonTimer");

}
void StopButtonTimer(){
  buttonPressed=false;
  
   //Serial.println("Stop button Timer");

}
void StartLockTimer(){
lockTimer=millis();
//Serial.println("Start Lock Timer");
  runLockTimer=true;
}

void StopLockTimer(){
  runLockTimer=false;
  //Serial.println("Stop Lock Timer");
}

void IncorrectPassword(){
  passwordAttempts--;
  PlayIncorrectSound();
  if(passwordAttempts<=0){
    alarmIsSounding=true;
  }
}

void Alarm(){
   //Make Sure All LEDS OFF
    digitalWrite(red,LOW);
    digitalWrite(blue,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,LOW);

    //Sound Buzzer and trigger LEDS
    tone(buzzer,1000);
    digitalWrite(red, HIGH);
    delay(200);

    tone(buzzer,500);
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    delay(200);

    tone(buzzer,1000);
    digitalWrite(yellow, LOW);
    digitalWrite(blue, HIGH);
    delay(200);

    tone(buzzer,500);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    delay(200);

    digitalWrite(green, LOW);
}

void PlayCorrectSound(){
  tone(buzzer,1000);
  delay(100);
  tone(buzzer,1200);
   delay(100);
  tone(buzzer,1400);
   delay(100);
  tone(buzzer,1600);
  delay(1000);
  noTone(buzzer);
}
void PlayIncorrectSound(){
  tone(buzzer,400);
  delay(300);
   tone(buzzer,100);
  delay(1000);
  noTone(buzzer);
}
void PlayInputSound(){
  tone(buzzer,700);
  delay(100);
   
  noTone(buzzer);
}

void UltrasonicSensorPing(){
//Ultrasonic sensor ping
    digitalWrite(trigger,LOW);
    delayMicroseconds(10);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(20);
    digitalWrite(trigger,LOW);
}

void HandleKeyPad(){
  if(isInLearnMode){

 customKp.tick();
    while(customKp.available()){
      keypadEvent e = customKp.read();
      keypadChar = (char)e.bit.KEY;

      if(e.bit.EVENT==KEY_JUST_PRESSED){
      if(keypadChar == '*'){  //use * to clear input
          PlayInputSound();
          userInput = "";
          digitalWrite(green,LOW);
          digitalWrite(red,LOW);
          Serial.println();
          Serial.println("Password: ");
        
        
      }else{
        if(keypadChar == '#'){//use #to submit pword
          
            digitalWrite(green,HIGH);
            digitalWrite(red,LOW);
            Serial.println();
            Serial.println("New Password Set!");
            password=userInput;
            Serial.println(password);
            PlayCorrectSound();
            StopButtonTimer();
            isInLearnMode=false;
            buttonPressed=false;
            userInput = "";
          
          
        }else{//user input string
          PlayInputSound();
          userInput+=keypadChar;
          Serial.print(keypadChar);
        }
      }
      
      }
    }

  }else{
    customKp.tick();
    while(customKp.available()){
      keypadEvent e = customKp.read();
      keypadChar = (char)e.bit.KEY;

      if(e.bit.EVENT==KEY_JUST_PRESSED){
      if(keypadChar == '*'){  //use * to clear input
          PlayInputSound();
          userInput = "";
          digitalWrite(green,LOW);
          digitalWrite(red,LOW);
          Serial.println();
          Serial.println("Password: ");
          
        
        
      }else{
        if(keypadChar == '#'){//use #to submit pword
          if(userInput==password){//check if user input matches password
            digitalWrite(green,HIGH);
            digitalWrite(red,LOW);
            Serial.println();
            Serial.println("-------------Correct-------------");
            Serial.print("Password: ");
            userInput = "";
            PlayCorrectSound();
            Unlock();
            alarmIsSounding=false;
            
          }else{ //if user input does not match password
            digitalWrite(red,HIGH);
            digitalWrite(green,LOW);
            Serial.println();
            Serial.println("-------------Incorrect-------------");
            Serial.println("please try again!");
            Serial.println();
            Serial.print("Password: ");
            userInput = "";
            IncorrectPassword();
          }
        }else{//user input string
          PlayInputSound();
          userInput+=keypadChar;
          Serial.print(keypadChar);
        }
      }
      
      }
    }
  }
}

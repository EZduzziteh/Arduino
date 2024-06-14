int sensorPowerPin = 1;
int fanPin = 4;
int pumpPin=6;

int currentDesiredLevel=0;
int desiredLevel=10; //base desired level value in mm

int potentioValue=0;
int sensorValue = 0; 

void setup() {
  Serial.begin(9600);
   
  pinMode(fanPin,OUTPUT);
  pinMode(pumpPin,OUTPUT);
  digitalWrite(sensorPowerPin, HIGH);  // turn the sensor ON
  currentDesiredLevel=desiredLevel; //set current desired level (the user variable ) to be the desired level(initial value set).
}

void loop() {

  
  potentioValue = analogRead(A8) + 1 - 512;
  //The logic behind this is that the potentiometer goes from 0-1023 and i want an even number to divide by, 
  //so i add 1 making it 1-1024. We will be using the middle of this as our "0" point so anything above
  //(1024/2) or 512 is positive while below that will be negative
  
  sensorValue = analogRead(A1); // read the analog value from sensor

  sensorValue = sensorValue*30/1023; //approximate conversion to mm (sets range to 0-30)

currentDesiredLevel = desiredLevel+(desiredLevel*potentioValue/512);  //set the current desired level as a % of the potentiometer (based on original level)  if max potentiometer, should be approx 20 mm, double the original. 
//It should be noted that this value is always rounded down.


//Logs all relevant values so we can make sure it is working correctly.

  Serial.println("-------Log Start-------");

  Serial.print("Sensor reading(mm): "); //This shows what our water sensor is picking up as the water level.
  Serial.println(sensorValue);            

  Serial.print("Desired level(mm): "); //this is what we have set the current desired water level to be.
  Serial.println(currentDesiredLevel);


  Serial.println("-------Log End-------");

 
  

  if(sensorValue>currentDesiredLevel+5){  //if when sensor goes 5 mm over desired level

    digitalWrite(fanPin, HIGH);//turn fan on

  }else{
    digitalWrite(fanPin, LOW);//turn fan off
  }

  if(sensorValue<currentDesiredLevel-5){  //if sensor goes 5 mm under desired level
      
    digitalWrite(pumpPin, HIGH);//turn pump on
    
  }else{
    digitalWrite(pumpPin, LOW);//turn pump off
  }



delay(5000);
  
}

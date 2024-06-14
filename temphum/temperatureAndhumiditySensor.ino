#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

#define Type DHT11

int tempHumiditySensorPin =  4;
DHT HumidityTemp(tempHumiditySensorPin, Type);
LiquidCrystal lcd(8,9,10,11,12,13);
float humidity;
float temperature;

int redLED=3;
int blueLED=2;
void setup() {
  // put your setup code here, to run once:
  HumidityTemp.begin();
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  humidity = HumidityTemp.readHumidity();
  temperature = HumidityTemp.readTemperature();




  if(temperature>23){
    digitalWrite(redLED, HIGH);
  }else{
    digitalWrite(redLED, LOW);
  }

  if(humidity>28){
  digitalWrite(blueLED, HIGH);
  }else{
  digitalWrite(blueLED, LOW);
  }


  lcd.setCursor(0,0);
  lcd.print("Temp is: ");
  lcd.print(temperature);

  lcd.setCursor (0,1);
  lcd.print("Humidity is: ");
  lcd.print(humidity);

  delay(1000);
  lcd.clear();

  
}

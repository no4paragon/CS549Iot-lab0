#include <Arduino.h>
#include <Servo.h>

const int testphoto = GPIO_NUM_37;
const int ledpinout = GPIO_NUM_22;
const int ledpinin = GPIO_NUM_36;
float maxAnalogValue = 0;
float minAnalogValue = 9999;
Servo myservo;

void BlinkLed(){
  if(digitalRead(ledpinin) == HIGH){
    digitalWrite(ledpinout, LOW);
  } else{
    digitalWrite(ledpinout, HIGH);
  }
}

void BlinkTenSec(){
  for(int i = 0; i < 10; i++){
    BlinkLed();

    if(maxAnalogValue < analogRead(testphoto)){
      maxAnalogValue = analogRead(testphoto);
    }else if (minAnalogValue > analogRead(testphoto)){
      minAnalogValue = analogRead(testphoto);
    }
    sleep(1);
  }
}

void setup() {

  Serial.begin(9600);
  myservo.attach(GPIO_NUM_21);
  pinMode(ledpinout, OUTPUT);
  pinMode(ledpinin, INPUT);
  pinMode(testphoto, INPUT); 
  BlinkTenSec();
  Serial.println("current max");
  Serial.println(maxAnalogValue);
  Serial.println("============");
  Serial.println("current min");
  Serial.println(minAnalogValue);
  Serial.println("============");

}

void loop() {

  float ldrStatus = analogRead(testphoto);
  Serial.println(ldrStatus);

  float servoVal = (ldrStatus/maxAnalogValue)*180;  
  myservo.write(servoVal);
  delay(1000);

}


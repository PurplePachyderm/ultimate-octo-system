#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 0x08
byte data_to_echo = 0;

Servo monServo; 

void setup() 
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  monServo.attach(2, 1000, 2000);
  
  
}


void loop() {
  digitalWrite(13, HIGH);   // allume la LED
  delay(1000);              // ne fait rien pendant 1 seconde
  digitalWrite(13, LOW);    // éteint la LED
  delay(1000); 
  monServo.write(90);       // tourne de 90 DEUX GRAISSE

}

void receiveData(int bytecount) {
  for (int i = 0; i < bytecount; i++) {
    data_to_echo = Wire.read();
  }
}


void sendData()
{
  Wire.write(data_to_echo);
}
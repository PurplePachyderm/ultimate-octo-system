#include <Wire.h>
#define SLAVE_ADDRESS 0x08
byte data_to_echo = 0;
void setup() 
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}


void loop() {
  digitalWrite(13, HIGH);   // allume la LED
  delay(1000);              // ne fait rien pendant 1 seconde
  digitalWrite(13, LOW);    // éteint la LED
  delay(1000); 
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

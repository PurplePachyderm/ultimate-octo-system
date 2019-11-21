#include <iostream>
#include <wiringPiI2C.h>
#include <cstdint>

#include <iostream>
#include <wiringPiI2C.h>


using namespace std;
int main(void) {

    //Setup I2C
    int fd8 = wiringPiI2CSetup(0x08);
    int fd9 = wiringPiI2CSetup(0x09);


    if(fd8 == -1) {
        cout << "I2C comm failed w/ 8" << endl ;
        return -1;
    }   
 

    if(fd9 == -1) {
        cout << "I2C comm failed w/ 9" << endl ;
        return -1;
    }   
 
    cout << "I2C comm setup" << endl;
                                          
                                               
    //Send msg to 8
    uint8_t outData8 = 42;
    wiringPiI2CWrite(fd8, outData8); 
    cout << "Sending msg to 8: " << (int)outData8 << endl;
        
                
    //Receive msg from 8
    int inData8 = wiringPiI2CRead(fd8);
    cout << "Received msg from 8: " << inData8 << endl;
              


    //Send msg to 9
    uint8_t outData9 = 43;
    wiringPiI2CWrite(fd9, outData9); 
    cout << "Sending msg to 9: " << (int)outData9 << endl;
        
                
    //Receive msg from 9
    int inData9 = wiringPiI2CRead(fd9);
    cout << "Received msg from 9: " << inData9 << endl;
              



    if(inData8 == outData8 && inData9 == outData9) {
        cout << "Yay =)!" << endl;
    }     
 

    return 0;

}

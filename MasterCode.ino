#include <Wire.h>
#include <AFMotor.h>

#define pass (void)0
#define I2C_SLAVE1_ADDRESS 11
#define PAYLOAD_SIZE 2


int n=0;

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    Serial.println(F("-------------------------------------I am the Master"));
    delay(1000);

    //Request value of n to slave
    Wire.requestFrom(I2C_SLAVE1_ADDRESS, 1);
    n = Wire.read();
    Serial.print(F("recieved value : "));
    Serial.println(n);

    //Send value 12 to slave
    Wire.beginTransmission(I2C_SLAVE1_ADDRESS);
    Wire.write(12);
    Serial.print(F("sending value : "));
    Serial.println(12);
    Wire.endTransmission();

    Serial.print(" ");

}


void loop()
{
    delay(100);
}
#include <Wire.h>
#include <AFMotor.h>
#include <Servo.h>
#define pass (void)0
#define I2C_SLAVE1_ADDRESS 11
#define PAYLOAD_SIZE 2
#define MAX_SWERVE 30

Servo servo;
int angle = 90;
int angle_change = 5;



char car_state = 'S';
char car_mode = 'C'; // C for controlled by user, A for autonomous parking mode
int n=0;

const int servo_pin = 1;
const int motor1_pin = 2;
const int motor2_pin = 3;

AF_DCMotor motor1(motor1_pin);
AF_DCMotor motor2(motor2_pin);

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

void motorsSetup()
{
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    Stop();
}

void loop()
{
    car_mode=Serial.read();
    car_state=Serial.read();

    if (car_mode == 'C')
        controlled_mode();
    else
        autonomous_mode();

    delay(100);
}

void controlled_mode()
{
    pass;
}
void autonomous_mode()
{
    pass;
}


//----------MOTION FUNCTIONS
void go_forward()
{
    motor1.run(FORWARD);
    motor2.run(FORWARD);
}
void turn(int angle)
{
    if (angle > MAX_SWERVE)
        return;

    servo.write(angle);
}
void Stop()
{
    pass;
}

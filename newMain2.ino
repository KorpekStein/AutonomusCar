#include <AFMotor.h>


//----------------PINY---------------

const int Sensor_1_EchoPin = 5;
const int Sensor_1_TrigPin = 6;
const int Sensor_2_EchoPin = 7;
const int Sensor_2_TrigPin = 8;
const int Sensor_3_EchoPin = 9;
const int Sensor_3_TrigPin = 10;
const int Sensor_4_EchoPin = 11;
const int Sensor_4_TrigPin = 12;




AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


//--------------------------------------

char bt='S';
void setup()
{
    Serial.begin(9600);

    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor3.setSpeed(255);
    motor4.setSpeed(255);
    Stop();
}


void loop()
{

    bt=Serial.read();
    control();
    //readSensors();

}

//-----------------------CONTROLING-------------------------
void control()
{
    if(bt=='F')
    {
        forward();
    }

    if(bt=='B')
    {
        backward();
    }

    if(bt=='L')
    {
        left();
    }

    if(bt=='R')
    {
        right();
    }

    if(bt=='S')
    {
        Stop();
    }

}
void forward()
{
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}

void backward()
{
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}
void left()
{
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}
void right()
{
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}
void Stop()
{
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}
//--------------------------------SENSORS-----------------------------------------------
void readSensors()
{

    inMode(Sensor_1_TrigPin, OUTPUT);
    pinMode(Sensor_1_EchoPin, INPUT);

    pinMode(Sensor_2_TrigPin, OUTPUT);
    pinMode(Sensor_2_EchoPin, INPUT);

    pinMode(Sensor_3_TrigPin, OUTPUT);
    pinMode(Sensor_3_EchoPin, INPUT);

    pinMode(Sensor_4_TrigPin, OUTPUT);
    pinMode(Sensor_4_EchoPin, INPUT);

    pinMode(Sensor_5_TrigPin, OUTPUT);
    pinMode(Sensor_5_EchoPin, INPUT);

    pinMode(Sensor_6_TrigPin, OUTPUT);
    pinMode(Sensor_6_EchoPin, INPUT);


}
float GetDistance(int TrigPin, int EchoPin)
{
    float distance,duration;

    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    duration = pulseIn(EchoPin, HIGH);
    distance = duration * 0.034 / 2;
    return distance;

}
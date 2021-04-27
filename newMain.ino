#include <Wire.h>
#include <vector>
#include <Array.h>
#define pass (void)0
#define MAX_ARRAYSIZE 10
int n = 0;
int speed = 0;
/* NOTE
 * THIS CONFIGURATION CONSIST ONLY FROM 2 ONE-SIDE SENSORS
 *
 *
 *
 */
//----------Setup----------------------------
const int Sensor_1_EchoPin = 0;
const int Sensor_1_TrigPin = 1;
const int Sensor_2_EchoPin = 2;
const int Sensor_2_TrigPin = 3;
/*
const int Sensor_3_EchoPin = 4;
const int Sensor_3_TrigPin = 5;
const int Sensor_4_EchoPin = 6;
const int Sensor_4_TrigPin = 7;
const int Sensor_5_EchoPin = 8;
const int Sensor_5_TrigPin = 9;
const int Sensor_6_EchoPin = 10;
const int Sensor_6_TrigPin = 11;

*/
 //TODO FIND HOW TO STORE DATA

//typedef Array<float,MAX_ARRAYSIZE> Sensor1_distances;
//typedef Array<float,MAX_ARRAYSIZE> Sensor2_distances;
//typedef Array<float,MAX_ARRAYSIZE> Sensor3_distances;
//typedef Array<float,MAX_ARRAYSIZE> Sensor4_distances;
//typedef Array<float,MAX_ARRAYSIZE> Sensor5_distances;
//typedef Array<float,MAX_ARRAYSIZE> Sensor6_distances;


float Sensor1New = 0;
float Sensor2New = 0;
float Sensor1Old = 0;
float Sensor2Old = 0;

AF_DCMotor Right_front_Motor(5);
AF_DCMotor Left_front_Motor(6);
AF_DCMotor Right_back_Motor(7);
AF_DCMotor Left_back_Motor(8);


void setup()
{
    PinSetup();
    Serial.begin(9600);
}
void PinSetup()
{
    pinMode(Sensor_1_TrigPin, OUTPUT);
    pinMode(Sensor_1_EchoPin, INPUT);

    pinMode(Sensor_2_TrigPin, OUTPUT);
    pinMode(Sensor_2_EchoPin, INPUT);
/*
    pinMode(Sensor_3_TrigPin, OUTPUT);
    pinMode(Sensor_3_EchoPin, INPUT);

    pinMode(Sensor_4_TrigPin, OUTPUT);
    pinMode(Sensor_4_EchoPin, INPUT);

    pinMode(Sensor_5_TrigPin, OUTPUT);
    pinMode(Sensor_5_EchoPin, INPUT);

    pinMode(Sensor_6_TrigPin, OUTPUT);
    pinMode(Sensor_6_EchoPin, INPUT);
*/
}
//----------------------------------mainloop--------------------
void loop()
{
    Sensor1Old = Sensor1New;
    Sensor2Old = Sensor2New;
    Sensor1New = GetDistance(Sensor_1_TrigPin,Sensor_1_EchoPin);
    Sensor2New = GetDistance(Sensor_2_TrigPin,Sensor_2_EchoPin);
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

void setspeed(int speed)
{
    Right_front_Motor.setSpeed(speed);
    Left_front_Motor.setSpeed(speed);
    Right_back_Motor.setSpeed(speed);
    Left_back_Motor(speed);
}

void go_forward()
{
    Right_front_Motor.run(FORWARD);
    Left_front_Motor.run(FORWARD);
    Right_back_Motor.run(FORWARD);
    Left_back_Motor.run(FORWARD);
}

void go_backward()
{
    Right_front_Motor.run(BACKWARD);
    Left_front_Motor.run(BACKWARD);
    Right_back_Motor.run(BACKWARD);
    Left_back_Motor.run(BACKWARD);
}

void turn_right()
{
    Right_front_Motor.run(BACKWARD);
    Left_front_Motor.run(FORWARD);
    Right_back_Motor.run(BACKWARD);
    Left_back_Motor.run(FORWARD);
}

void turn_left()
{
    Right_front_Motor.run(FORWARD);
    Left_front_Motor.run(BACKWARD);
    Right_back_Motor.run(FORWARD);
    Left_back_Motor.run(BACKWARD);
}





//-------------------------------looking for space to park-------------------------------

int look_for_parallel()
{
    pass;
}
int look_for_perpendicular()
{
    pass;
}
int look_for_angled()
{
    pass;
}

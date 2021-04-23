#include <Wire.h>
#include <vector>
#define pass (void)0
int n = 0;

//----------Setup----------------------------
const int Sensor_1_EchoPin = 0;
const int Sensor_1_TrigPin = 1;
const int Sensor_2_EchoPin = 2;
const int Sensor_2_TrigPin = 3;
const int Sensor_3_EchoPin = 4;
const int Sensor_3_TrigPin = 5;
const int Sensor_4_EchoPin = 6;
const int Sensor_4_TrigPin = 7;
const int Sensor_5_EchoPin = 8;
const int Sensor_5_TrigPin = 9;
const int Sensor_6_EchoPin = 10;
const int Sensor_6_TrigPin = 11;

/*int Sensor1_distance;
int Sensor2_distance;
int Sensor3_distance;
int Sensor4_distance;
int Sensor5_distance;
int Sensor6_distance;*/

std::vector< float > Sensor1_distances;
std::vector< float > Sensor2_distances;
std::vector< float > Sensor3_distances;
std::vector< float > Sensor4_distances;
std::vector< float > Sensor5_distances;
std::vector< float > Sensor6_distances;

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

    pinMode(Sensor_3_TrigPin, OUTPUT);
    pinMode(Sensor_3_EchoPin, INPUT);

    pinMode(Sensor_4_TrigPin, OUTPUT);
    pinMode(Sensor_4_EchoPin, INPUT);

    pinMode(Sensor_5_TrigPin, OUTPUT);
    pinMode(Sensor_5_EchoPin, INPUT);

    pinMode(Sensor_6_TrigPin, OUTPUT);
    pinMode(Sensor_6_EchoPin, INPUT);

}
//----------------------------------mainloop--------------------
void loop()
{
    Sensor1_distance.push_back(GetDistance(Sensor_1_TrigPin,Sensor_1_EchoPin));
    Sensor2_distance.push_back(GetDistance(Sensor_2_TrigPin,Sensor_2_EchoPin));
    Sensor3_distance.push_back(GetDistance(Sensor_3_TrigPin,Sensor_3_EchoPin));
    Sensor4_distance.push_back(GetDistance(Sensor_4_TrigPin,Sensor_4_EchoPin));
    Sensor5_distance.push_back(GetDistance(Sensor_5_TrigPin,Sensor_5_EchoPin));
    Sensor6_distance.push_back(GetDistance(Sensor_6_TrigPin,Sensor_6_EchoPin));
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


//--------------Master-Slave Connection----------------------
void requestEvents()
{
    Serial.println(F("---> recieved request"));
    Serial.print(F("sending value : "));
    Serial.println(Sensor1_distance);
    Wire.write(Sensor1_distance);
}

void receiveEvents(int numBytes)
{
    Serial.println(F("---> recieved events"));
    n = Wire.read();
    Serial.print(numBytes);
    Serial.println(F("bytes recieved"));
    Serial.print(F("recieved value : "));
    Serial.println(n);
}
//-------------------------------looking for space to park-------------------------------

int look_for_parallel()
{
    pass();
}
int look_for_perpendicular()
{
    pass();
}
int look_for_angled()
{
    pass();
}

#include <AFMotor.h>


//----------------PINY---------------



const int Sensor_1_EchoPin = 53;
const int Sensor_1_TrigPin = 52;

const int Sensor_2_EchoPin = 23;
const int Sensor_2_TrigPin = 22;

const int Sensor_3_EchoPin = 24;
const int Sensor_3_TrigPin = 25;

/*
const int Sensor_4_EchoPin = 11;
const int Sensor_4_TrigPin = 12;
const int Sensor_5_EchoPin = 13;
const int Sensor_5_TrigPin = 14;
const int Sensor_6_EchoPin = 15;
const int Sensor_6_TrigPin = 16;
*/


const int ledpin = 26;



/*  MAP TODO MAP ALL SENSORS
 *  Sensor1 - back
 *  Sensor2 - back_left
 *  Sensor3 - front_left
 */
//-----------Car_properties---------------------------

const float car_length = 30;
const float car_width = 20;

int speed = 100;

//-------------Spot properties----------

float spot_length;
float spot_width;

//---------------------------------

AF_DCMotor motor1(1); //left back motor
AF_DCMotor motor2(2); // right back motor
AF_DCMotor motor3(3); //right front motor
AF_DCMotor motor4(4); //left front motor


//--------------------------------------

char CarMode = 'C'; // C for control mode, A for parking
char bt='S';

//-------------EXTREMELY IMPORTANT-----------------
int parking_mode = 0; //TODO describe every scenario with appropriate number

/* 0 - no spot found, keep looking
 * 1 - spot found, looking for end
 * 2 - end found, started parking protocol
 * 200 - PARKED
 */

void setup()
{
    Serial.begin(9600);

    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
    Stop();
    SensorsSetup();
}


void loop()
{

    bt=Serial.read();
    control_type();

}

//-----------------------CONTROLLING-------------------------


void control_type()
{
    if(bt=='X')
    {
        Stop();
        CarMode='A';
        parking_mode = 0;


    }

    if(bt=='x')
    {
        Stop();
        CarMode='C';

    }

    if (CarMode == 'C')
    {
        control();
    }

    if (CarMode == 'A')
    {
        parking();
    }
}

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
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
}
void right()
{
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
}
void Stop()
{
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

//------------------RIDE N -------------------;

void setSpeed(int newSpeed)
{
    motor1.setSpeed(newSpeed);
    motor2.setSpeed(newSpeed);
    motor3.setSpeed(newSpeed);
    motor4.setSpeed(newSpeed);
}


void go_forward(int newSpeed)
{
    setSpeed(newSpeed);
    forward();

}


void go_back(int newSpeed)
{
    setSpeed(newSpeed);
    backward();

}

void go_right(int newSpeed)
{
    setSpeed(newSpeed);
    right();

}

void go_left(int newSpeed)
{
    setSpeed(newSpeed);
    left();

}

//--------------------------------SENSORS-----------------------------------------------
void SensorsSetup()
{
    pinMode(Sensor_1_TrigPin, OUTPUT);
    pinMode(Sensor_1_EchoPin, INPUT);

    pinMode(Sensor_2_TrigPin, OUTPUT);
    pinMode(Sensor_2_EchoPin, INPUT);

    pinMode(Sensor_3_TrigPin, OUTPUT);
    pinMode(Sensor_3_EchoPin, INPUT);

/*
    pinMode(Sensor_4_TrigPin, OUTPUT);
    pinMode(Sensor_4_EchoPin, INPUT);
    pinMode(Sensor_5_TrigPin, OUTPUT);
    pinMode(Sensor_5_EchoPin, INPUT);
    pinMode(Sensor_6_TrigPin, OUTPUT);
    pinMode(Sensor_6_EchoPin, INPUT);
*/

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


void parking()
{
    scan_for_parking();
    //TODO implement parking scan
}

void scan_for_parking()
{

    float front_side_scan;
    float back_side_scan;


    //--------------for left side-------------

    back_side_scan = GetDistance(Sensor_2_TrigPin, Sensor_2_EchoPin);
    front_side_scan = GetDistance(Sensor_3_TrigPin, Sensor_3_EchoPin);


    float change = front_side_scan - back_side_scan;

    Serial.print("back_side_scan: ");
    Serial.print(back_side_scan);
    Serial.print("\n");
    Serial.print("front_side_scan:");
    Serial.print(front_side_scan);
    Serial.print("\n");
    Serial.print("change:");
    Serial.print(change);
    Serial.print("\n");
    Serial.print("praking mode:");
    Serial.print(parking_mode);
    Serial.print("\n");


    if(parking_mode == 200)
    {
        blink(1);
        Stop();
        Serial.print("praking mode:\n");
        Serial.print("\n");
        Serial.print(parking_mode);
        return;
    }


    if (change > car_width && parking_mode == 0) //szuka roznicy pomiedzy przednim i tylnim
    {
        digitalWrite(ledpin, HIGH);
        spot_length = change;
        parking_mode = 1;
        //TODO start clock so we can measure spot length
        Serial.print("First condition fillfulled\n");


    }


    if (parking_mode==1 && back_side_scan < car_width && front_side_scan < car_width) // jak wie ze ma rownolegle to podjezdza do konca (bez liczenia dystansu narazie)
    {
        Stop();
        blink(5);
        delay(2000);
        Serial.print("parking..............\n");
        parallel_parking();
        //vertical_parking();
        parking_mode = 200;
        return;

        /*
            //TODO check conditions whether do park parallel or vertical
            if(spot_length > car_length && spot_width > car_width)
            {
                vertical_parking();
            }
            if else(spot_length > car_width && spot_width > car_length)
            {
                parallel_parking();
            }
            else
            {
                parking_mode = 0;
                return;
            }
                parking_mode = 200;
        }
         */

    }
    else
    {
        forward();

    }
}


void parallel_parking()
{
    //Funkcje do parkowania uzaleznione od wymiarow (formulka)

    float front_side_scan;
    for(;;)
    {
        go_back(100);
        front_side_scan = GetDistance(Sensor_3_TrigPin, Sensor_3_EchoPin);
        if(front_side_scan > spot_length) break;
        Serial.print("front scan: ");
        Serial.print(front_side_scan);
        Serial.print("\n");
    }

    Stop();
    delay(1000);
    go_right(150);
    delay(250);
    Stop();
    delay(500);



    float back_scan;




    for(;;)
    {
        back_scan = GetDistance(Sensor_1_TrigPin,Sensor_1_EchoPin);
        if(back_scan <4) break; //TO NIE DZIAALA
        go_back(100);
        Serial.print("back scan: ");
        Serial.print(back_scan);
        Serial.print("\n");
    }

    /*
     do
    {
        back_scan = GetDistance(Sensor_1_TrigPin,Sensor_1_EchoPin);
        go_back(100);
    } while(!(back_scan > 6 && back_scan <13));
    */

    Stop();
    delay(1000);
    go_left(150);
    delay(250);
    Stop();


    parking_mode = 200;
    return;

}

void vertical_parking()
{
    float front_side_scan;
    for(;;)
    {
        go_back(100);
        front_side_scan = GetDistance(Sensor_3_TrigPin, Sensor_3_EchoPin);
        if(front_side_scan > spot_length) break;
        Serial.print("front scan\n");
        Serial.print(front_side_scan);
    }
    Stop();
    delay(1000);
    go_right(150);
    delay(500);
    Stop();
    delay(500);



    float back_scan;




    for(;;)
    {
        go_back(100);
        back_scan = GetDistance(Sensor_1_TrigPin,Sensor_1_EchoPin);
        if(back_scan <4) break; //TO NIE DZIAALA
        Serial.print("back scan\n");
        Serial.print(back_scan);
    }


    Stop();
    delay(1000);



    parking_mode = 200;
    return;

}

void blink(int n)
{
    for(int i=0;i<n;i++)
    {
        digitalWrite(ledpin, LOW);
        delay(500);
        digitalWrite(ledpin, HIGH);
        delay(500);
        digitalWrite(ledpin, LOW);
    }
}

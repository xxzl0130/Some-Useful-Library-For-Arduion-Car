#ifndef __US_DISTANCE_H__
#define __US_DISTANCE_H__

#include <arduino.h>

#ifndef uchr
#define uchr unsigned char
#endif // uchr

class US_Distance{
private:
    uchr echoPin,trigPin;
public:
    US_Distance(uchr TrigPin = 2, uchr EchoPin = 3)
    {
        pinMode(echoPin = EchoPin,INPUT);
        pinMode(trigPin = TrigPin,OUTPUT);
        digitalWrite(TrigPin, LOW);
    }

    float getDistance()
    {
        float Dis;

        digitalWrite(trigPin,LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin,HIGH);
        delayMicroseconds(11);
        digitalWrite(trigPin,LOW);
        Dis = (float)pulseIn(echoPin,HIGH) / 58.0;
        return Dis;
    }
};

#endif //__US_DISTANCE_H__


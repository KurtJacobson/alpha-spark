#include <stdio.h>
#include <wiringPi.h>

int main(void)
{
    wiringPiSetupGpio();

    pinMode(17, INPUT);
    digitalWrite(17,HIGH);

    int count = 0;
    int countPerMinute = 0;
    int timePreviousMeasure = 0;
    int lastRead = 0;


    while(1)
    {
        if (millis()-timePreviousMeasure > 1000)
        {
            timePreviousMeasure= millis();
            countPerMinute = 60*count;
            printf("cpm = %d \n\n", countPerMinute);
            count = 0;
        }

        if (digitalRead(17)==LOW && lastRead==1)
        {
            count++;
            lastRead=0;
        }
        else if (digitalRead(17)==HIGH)
        {
            lastRead=1;
        }

    }
     return 0;
}

//Notes: compile command: gcc -Wall -lwiringPi kurt2.c -o kurt2
// to run program: sudo ./kurt2
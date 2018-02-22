#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

int main(void)
{
    wiringPiSetupGpio();

    pinMode(17, INPUT);
    digitalWrite(17,HIGH);

    int count = 0;
    int countPerSec = 0;
    int countPerMinute = 0;
    int timePreviousPrint = 0;
    int lastRead = 0;
    char time[10];
    char fName[15];


    printf(Input save to filename: );
    fgets(fName,15,stdin);
    fName=fname +".txt";
    FILE *fp;
    fp=fopen(fName,"w");
    fprintf(fp , "TIME\tcpm\n");


    printf("Input Count Time: ");
    fgets(time,10,stdin);
    printf("Counting for %s",time);

    int timeInt = atoi(time);

    int startTime = millis();

    while(millis()-startTime < timeInt*1000)
    {

        if (millis()-timePreviousPrint > 1000)
        {
            timePreviousPrint= millis();
            countPerSec = countPerSec;
            printf("%d\t%d\n", (millis()-startTime+1000)/1000 , countPerSec);
                    fprintf(fp, "%d\t%d\n", (millis()-startTime+1000)/1000 , countPerSec);
            countPerSec = 0;
        }

        if (digitalRead(17)==LOW && lastRead==1)
        {
            count++;
            countPerSec++;
            lastRead=0;
        }

        else if (digitalRead(17)==HIGH)
        {
            lastRead=1;
        }

    }

    countPerMinute = count*(60/timeInt);
    printf("Avg cpm was: %d \n", countPerMinute);
        //fprintf(fp, "Avg cpm = %d \n", countPerMinute);
        fclose(fp);

    return 0;

}

//Notes: compile command: gcc -Wall -lwiringPi kurt2.c -o kurt2
// to run program: sudo ./kurt2


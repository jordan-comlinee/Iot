#include <stdio.h>
#include <math.h>
#include <wiringPi.h>

#define IN1	22
#define IN2	23
#define IN3	24
#define IN4	25

int inArray[4] = {IN1, IN2, IN3, IN4};

int init()
{
	if(wiringPiSetup() == -1) return -1;
	for(int i = 0; i < 5; i ++)
		pinMode(inArray[i], OUTPUT);
}


int main()
{
	init();
	while(1)
	{
		/*
		for(int i=0; i<4; i++)
		{
			
			digitalWrite(inArray[i], 1);
			delay(2);
			digitalWrite(inArray[i], 0);
			delay(2);
		}
		*/
		for (int i=0; i<4; i++) {
			digitalWrite(inArray[i%4], 1);
			digitalWrite(inArray[(i+1)%4], 1);
			delay(2);
			digitalWrite(inArray[i%4], 0);
			digitalWrite(inArray[(i+1)%4], 0);
			delay(2);
		}
	}
	
}

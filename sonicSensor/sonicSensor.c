#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>
#define trigger	1
#define echo	27
#define buzzer	29


int main()
{
	int distance = 0;
	int pulse = 0;

	long startTime;
	long endTime;

	if(wiringPiSetup() == -1) return -1;

	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
	pinMode(buzzer, OUTPUT);

	while(1)
	{
		digitalWrite(trigger, 0);
		digitalWrite(trigger, 1);
		delayMicroseconds(10);
		digitalWrite(trigger, 0);
		while(digitalRead(echo) == 0)
		{
		}
		startTime = micros();
		while(digitalRead(echo) == 1)
		{
		}
		endTime = micros() - startTime;
		int distance = endTime / 58;
		if(distance < 1000) {
			printf("Distance : %dcm\n", distance);
			delay(1500);
			if(distance < 30)
			{
				digitalWrite(buzzer, 1);
				delayMicroseconds(1000);
				digitalWrite(buzzer, 0);
				delayMicroseconds(100);
			}

		}

	}

}

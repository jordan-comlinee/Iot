#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>

int sonicSensor(int trigger, int echo, long startTime, long endTime)
{
	// sensor to something distance
	int distance = 0;

	digitalWrite(trigger, 0);
	digitalWrite(trigger, 1);
	delayMicroseconds(10);
	digitalWrite(trigger, 0);
	//printf("ongoing...1\n");
	while(digitalRead(echo) == 0)
	{}
	startTime = micros();
	//printf("ongoing...2\n");
	while(digitalRead(echo) == 1)
	{}
	endTime = micros() - startTime;
	distance = endTime / 58;
	//printf("ongoing...3\n");
	delay(1500);

	return distance;

}

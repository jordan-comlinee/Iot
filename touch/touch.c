#include <stdio.h>
#include <wiringPi.h>

#define tilt	27
#define touch	29


int main(void)
{
	if(wiringPiSetup() == -1) return -1;
	pinMode(tilt, INPUT);
	pinMode(touch, INPUT);

	while(1)
	{
		delay(500);
		printf("tilt: %d | touch: %d\n", digitalRead(tilt), digitalRead(touch));
	}
}

#include <stdio.h>
#include <wiringPi.h>

#define ENABLE	23
#define O1	24
#define O2	25

int init()
{
	if(wiringPiSetup() == -1)
		return -1;

	pinMode(O1, OUTPUT);
	pinMode(O2, OUTPUT);
	pinMode(ENABLE, OUTPUT);
}

int main() {

	init();
	
	//enable motor
	digitalWrite(ENABLE, 1);

	while(1) {
		digitalWrite(ENABLE, 1);
		digitalWrite(O1, 0);
		digitalWrite(O2, 1);

		delay(100);
	
		digitalWrite(ENABLE, 0);
		digitalWrite(O1, 1);
		digitalWrite(O2, 0);

		
	}
}

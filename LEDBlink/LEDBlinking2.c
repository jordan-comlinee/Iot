#include <stdio.h>
#include <wiringPi.h>
#define PIN_NUM1 27
#define PIN_NUM2 25

int main(void) {

	if(wiringPiSetup() == -1) {
		return -1;
	}
	
	
	pinMode(PIN_NUM1, OUTPUT);
	pinMode(PIN_NUM2, OUTPUT);

	while(1){
		digitalWrite(PIN_NUM1, 1);
		delay(100);
		digitalWrite(PIN_NUM1, 0);
		digitalWrite(PIN_NUM2, 1);
		delay(100);
		digitalWrite(PIN_NUM2, 0);
	}
	
	return 0;
	
}

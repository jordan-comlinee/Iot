#include <stdio.h>
#include <wiringPi.h>
#define LED_PIN_NUM 27
#define SWITCH_PIN_NUM 1


int main(void) {

	if(wiringPiSetup()==-1)
		return -1;
	
	pinMode(SWITCH_PIN_NUM, INPUT);
	pinMode(LED_PIN_NUM, OUTPUT);

	while(1){
		if(digitalRead(SWITCH_PIN_NUM) == 1){
			digitalWrite(LED_PIN_NUM, 1);
		}
		else if(digitalRead(SWITCH_PIN_NUM) == 0)
			digitalWrite(LED_PIN_NUM, 0);
	}
	return 0;
}

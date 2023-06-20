#include <stdio.h>
#include <wiringPi.h>

void blink(int i, int time){
	delay(time);
	digitalWrite(i, 1);
	delay(time);
	digitalWrite(i, 0);
}

int main(void) {
	
	if(wiringPiSetup() == -1)
		return -1;
	
	int pinArray[5] = {1, 4, 6, 26, 28};
	
	for(int i=0; i<5; i++)
		pinMode(pinArray[i], OUTPUT);


	while(1){
		for(int i=0; i<4; i++)
			blink(pinArray[i], 100);
		for(int i=4; i>=1; i--)
			blink(pinArray[i], 100);
	}
	
	return 0;
	
}

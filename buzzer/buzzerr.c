#include <stdio.h>
#include <wiringPi.h>
#define BUZ_NUM 27

void micro_delay(unsigned int t){
	unsigned int cur;
	cur = micros();
	if(micros() > cur+t)
		return;
	else
		cur = micros();

}


int soundMake(int f) {
	int t = 1 / f * 1000 / 2;
	return t;
}

int main(void) {
	int hz[7] = {3822, 3405, 3034, 2863, 2551, 2273, 2025};
	int plane[] = {2, 1, 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2};
	/*
	for (int i=0; i<sizeof(hz); i++){
		hz[i] = soundMake(hz[i]);
	}
	*/
	if(wiringPiSetup() == -1 ) {
		return -1;
	}

	pinMode(BUZ_NUM, OUTPUT);
	//micro_delay(before_time);


	while(1) {
		unsigned int t=100;
		for(int i=0; i < sizeof(plane); i++) {
			digitalWrite(BUZ_NUM, hz[plane[i]]);
			micro_delay(t);
			digitalWrite(BUZ_NUM, 0);
			micro_delay(t);
		}
	}

	return 0;

}

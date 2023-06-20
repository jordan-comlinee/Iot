#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>
#define LED	27


int dutyCycle = 10;

int init() {
	if(wiringPiSetup() == -1)	return -1;

	pinMode(LED, OUTPUT);
}

void ledON() {
	while(1){
		// make cycle in LED!!
		digitalWrite(LED, 1);
		delay(dutyCycle/10);
		digitalWrite(LED, 0);
		delay(10-(dutyCycle/10));		
	}
}

void inputDutyCycle() {
	printf("input the DUTY CYCLE :  % ");
	scanf("%d", &dutyCycle);
}



void *threadRoutine1(void *argumentPointer)
{
	init();
	ledON();
	return NULL;
}

void *threadRoutine2(void *argumentPointer)
{
	while(1){
		inputDutyCycle();
	}
}

int main(){

	pthread_t threadID[2];

	threadID[0] = pthread_self();
	threadID[1] = pthread_self();

	printf("Create Thread!\n");
	pthread_create(&(threadID[0]), NULL, threadRoutine1, NULL);
	pthread_create(&(threadID[1]), NULL, threadRoutine2, NULL);

	for(int i=0; i<2; i++) {
		pthread_join(threadID[i], NULL);
	}
	


}

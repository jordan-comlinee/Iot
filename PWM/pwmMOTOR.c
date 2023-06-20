#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>

#define ENABLE	23
#define O1	24
#define O2	25


bool buttonPressed = True;
int dutyCycle = 10;

int init() {
	if(wiringPiSetup() == -1)	return -1;

	pinMode(O1, OUTPUT);
	pinMode(O2, OUTPUT);
	pinMode(ENABLE, OUTPUT);
}

void motorON(){
	digitalWrite(ENABLE, 1);
	while(1){
		digitalWrite(O1, 0);
		digitalWrite(O2, 1);

	}

}

void slowStart(){
}

void slowEnd(){
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

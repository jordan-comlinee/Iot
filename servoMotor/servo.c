#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#define SERVO	29

int dutyCycle = 20;
int pwm=0;


int init()
{
	if(wiringPiSetup() == -1)	return -1;

	pinMode(SERVO, OUTPUT);
}

void motorStart(int pwm)
{
	while(1){
		digitalWrite(SERVO, 1);
		delayMicroseconds(pwm);
		digitalWrite(SERVO, 0);
		delayMicroseconds(pwm);
	}
}
void input()
{
	printf("input PWM: ");
	scanf("%d", &pwm);

}

void *threadRoutine1(void *argumentPointer)
{
	init();
	motorStart(pwm);
	return NULL;
}

void *threadRoutine2(void *argumentPointer)
{
	while(1){
		input();
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

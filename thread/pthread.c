#include <pthread.h>
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#define PIN_NUM1 27
#define PIN_NUM2 25
#define SWITCH_PIN_NUM 1
int buttonBlink = 0;

void *threadRoutine1(void *argumentPointer)
{	
	if(wiringPiSetup() == -1) {
		return NULL;
	}

	pinMode(PIN_NUM1, OUTPUT);
	while(buttonBlink = 0)
	{
		digitalWrite(PIN_NUM1, 1);
		delay(100);
		digitalWrite(PIN_NUM1, 0);
		delay(100);
	}
	return NULL;
}

void *threadRoutine2(void *argumentPointer)
{
	if(wiringPiSetup()==-1) {
		return NULL;
	}

	pinMode(SWITCH_PIN_NUM, INPUT);
	while(1)
	{
		if(digitalRead(SWITCH_PIN_NUM) == 1) {
			buttonBlink = 1;
			break;
		}
	}


	return NULL;
}

int main()
{
	pthread_t threadID[2];
	
	printf("Create Thread!\n");	
	pthread_create(&(threadID[0]), NULL, threadRoutine1, NULL);
	pthread_create(&(threadID[1]), NULL, threadRoutine2, NULL);
	for(int i=0; i<2; i++) {
		pthread_join(threadID[i], NULL);

	}
	//printf("Create Thread!\n");
	//pthread_create(&threadID, NULL, threadRoutine, NULL);
	
	//printf("Main Thread is now waiting for Child Thread!\n");
	
	//pthread_join(threadID, NULL);

	printf("Main Thread finish waiting Child Thread!\n");

	return 0;
}

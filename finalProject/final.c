#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "sonicSensor.h"
#include "lcd.h"


// define sonicSensor
#define trigger	28
#define echo	29

// define tilt
#define tilt		27

int distance = 0;
bool kittyIsSick = false;
bool kittyIsSleepy = false;
bool gameStart = false;
bool gameFinish = false;
bool sleeping = false;
int healScore = 0;
int sleepScore = 0;
char kittyName[100] = "duknyang\0";
clock_t start_time, end_time;
double elapsed_time;


void initSonicSensor()
{
	// setup OUTPUT or INPUT
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);

}
void initLCD()
{
	fd = wiringPiI2CSetup(I2C_ADDR);
	//printf("fd = %d ", fd);
	lcd_init(); // setup LCD
}

void initTILT()
{
	pinMode(tilt, INPUT);
}


void *threadSonicSensor(void *argumentPointer)
{
	initSonicSensor();
	long startTime;
	long endTime;
	int recentDistance = 0;
	while(1)
	{
		if (kittyIsSick)
		{
			recentDistance = sonicSensor(trigger, echo, startTime, endTime);
			if(recentDistance < 1000)
				distance = recentDistance;
			//printf("distance : %dcm\n", distance);
			if(distance < 10)
			{
				printf("You're doing it great!!\n");
				healScore = healScore + 1;
			}
			else
				printf("Come closer!\n");
		}
		if(gameFinish)
			break;

	}

}
void *threadTILT(void *argumentPointer)
{
	int pretilt = 0;
	initTILT();
	while(1)
	{
		pretilt = digitalRead(tilt);
		if (kittyIsSleepy)
		{
			delay(1500);
			if(digitalRead(tilt) != pretilt)
				sleepScore = sleepScore + 1;
			pretilt = digitalRead(tilt);
			printf("sleepScore : %d | %d\n", sleepScore, digitalRead(tilt));
		}
		if(gameFinish)
			break;
	}
}

void *threadLcd(void *argumentPointer)
{	
	while(1)
	{
		if(gameStart)
		{
			initLCD();
			while(1)
			{
				if(kittyIsSick)
					lcd_sick();
				if(kittyIsSleepy)
					lcd_sleepy();
				if(!kittyIsSick && !kittyIsSleepy && !sleeping)
					lcd_baby(kittyName);
				if(!kittyIsSick && !kittyIsSleepy && sleeping)
					lcd_sleeping();
				if(gameFinish)
					break;
				
			}
		}
		if(gameFinish)
		{
			printf("MISSION ACCOMPLISHED!\n");
			delay(1500);
			printf("YOUR FINAL SCORE IS...: \nHEAL SCORE : %d | SLEEP SCORE : %d\n", healScore, sleepScore);
			if(healScore > 6 && sleepScore > 5)
			{
				printf("%s was grown up so happy.\nshe became happiest cat ever!\n", kittyName);
				lcd_happy();
				lcd_happy();
				lcd_happy();
			}
			else if(healScore <= 6 && sleepScore > 5)
			{
				printf("Although %s was grown up happily, but She was not loved when she was sick.\nshe became naughty cat!\n", kittyName);
				lcd_naughty();
				lcd_naughty();
				lcd_naughty();	
			}
			else if(healScore > 6 && sleepScore <= 5)
			{
				printf("Although %s was grown up happily, but She was not able to sleep when she was sleepy.\nshe became lazy cat!\n", kittyName);
				lcd_lazy();
				lcd_lazy();
				lcd_lazy();
			}
			else
			{
				printf("Because you did not care of %s, she ran away to find new sister...\n", kittyName);
				lcd_gameover();
				lcd_gameover();
				lcd_gameover();	
			}
			break;
		}
	}

}

void *threadMaster(void *argumentPointer)
{
	printf("Hello!\n");
	delay(1000);
	printf("Raise your kitty and make her smart!\n");
	delay(1000);
	printf("Please name your kitty :");
	scanf("%s", &kittyName);
	delay(500);
	printf("Your kitty's name is %s\n", kittyName);
	delay(1000);
	printf("Now, Let's keep your kitty, %s!\n", kittyName);
	gameStart = true;
	int sick_time, sleepy_time;
	srand(time(NULL));
	sick_time = rand() % 4;
	sleepy_time = rand() % 4;
	sick_time = sick_time * 9000;
	sleepy_time = sleepy_time * 9000;
	// game start for about 2 minutes
	// sick
	printf("%d | %d\n", sick_time, sleepy_time);
	delay(sick_time);
	kittyIsSick = true;
	delay(16000);
	kittyIsSick = false;
	delay(27000 - sick_time);
	// sleepy
	delay(sleepy_time);
	kittyIsSleepy = true;
	delay(16000);
	kittyIsSleepy = false;
	sleeping = true;
	delay(27000 - sleepy_time);
	// game end
	sleeping = false;
	gameStart = false;
	gameFinish = true;
		

}

int main()
{
	if(wiringPiSetup() == -1) return -1;
	pthread_t threadID[4];
	threadID[0] = pthread_self();
	threadID[1] = pthread_self();
	threadID[2] = pthread_self();
	threadID[3] = pthread_self();

	printf("create thread\n");
	pthread_create(&(threadID[0]), NULL, threadLcd, NULL);
	pthread_create(&(threadID[1]), NULL, threadMaster, NULL);
	pthread_create(&(threadID[2]), NULL, threadSonicSensor, NULL);
	pthread_create(&(threadID[3]), NULL, threadTILT, NULL);

	for(int i = 0; i<3; i++)
		pthread_join(threadID[i], NULL);
}

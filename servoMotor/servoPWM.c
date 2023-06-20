#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
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
}
void input()
{
	printf("input PWM: ");
	scanf("%d", &pwm);

}

int main(){
	init();
	softPwmCreate(SERVO, 0, 200);
	while(1)
	{	
		printf("Input here: ");
		scanf("%d", &pwm);
		softPwmWrite(SERVO, pwm);
		delay(100);
	}
	


}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "LedControl.h"

#define LED_NUM		4
unsigned char LED_status[LED_NUM];

void setup_wPi(void)
{
	// wiringPiSetup()
	// pinMode()
	
	for(int i=0 ; i<LED_NUM ; i++)	LED_status[i] = LED_OFF;
}

void led_on(num)
{
	// digitalWrite(num, 1);
}

void led_off(num)
{
	// digitalWrite(num, 0);
}

void led_blink(num)
{
	// led blinking will be automatically progressed on thread.
}

void LED_control(unsigned char led_num, unsigned char cmd)
{
	switch(cmd)
	{
		case LED_ON:	led_on(led_num-1);	break;
		case LED_OFF:	led_off(led_num-1);	break;
		case LED_BLINK:	led_blink(led_num-1);	break;
		default:				break;
	}

	LED_status[led_num-1] = cmd;
}

int check_pkt(LCH_t *pkt)
{
	if(pkt->magic != MAGIC) return ERROR;
	if(pkt->Op != REQ)	return ERROR;

	if(pkt->SubOp == SET)	LED_control(pkt->led, pkt->cmd);
	else if(pkt->SubOp == GET)	printf("Do Nothing\n");
	else	return ERROR;

	printf("Rx Packet - Op:%d, SubOp:%d, cmd:%d, led:%d\n", pkt->Op, pkt->SubOp, pkt->cmd, pkt->led);

	return SUCCESS;	
}

void make_pkt(LCH_t *pkt, LCH_t *rx_pkt)
{
	pkt->magic = MAGIC;
	pkt->Op = REP;
	
	if(rx_pkt->SubOp == GET)
		pkt->cmd = LED_status[rx_pkt->led-1];
	else if(rx_pkt->SubOp == SET)
		pkt->cmd = LED_NOP;

	pkt->SubOp = rx_pkt->SubOp;
	pkt->led = rx_pkt->led;

}

void *led_blinking(void *arg)
{
	int i;
	while(1)
	{
		for(i=0 ; i<LED_NUM ; i++)  if(LED_status[i] == LED_BLINK) led_on(i);
		sleep(250);
		for(i=0 ; i<LED_NUM ; i++)  if(LED_status[i] == LED_BLINK) led_off(i);
		sleep(250);
	}
}

int main(void)
{
	int sock, client_sock;
	struct sockaddr_in addr, client_addr;
	int len, addr_len, recv_len;
	LCH_t rx_pkt, tx_pkt;

	if((sock = socket(AF_INET, SOCK_STREAM, 0))<0) {
		printf("socket error\n");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		printf("bind error\n");
		return 1;
	}
	listen(sock, 5);
	addr_len = sizeof(client_addr);
	printf("wait for client ...\n");

	setup_wPi();

	pthread_t thr;
	pthread_create(&thr, NULL, led_blinking, NULL);

	while((client_sock = accept(sock, (struct sockaddr *)&client_addr, &addr)) >0) {
		printf("client ip: %s\n", inet_ntoa(client_addr.sin_addr));
		while(1)
		{
			recv(client_sock, (void *)&rx_pkt, sizeof(rx_pkt), 0);
			if(check_pkt(&rx_pkt) == ERROR)
				printf("Received Packet was Corrupted\n");
		
			make_pkt(&tx_pkt, &rx_pkt);	
	
			send(client_sock, (void *)&tx_pkt, sizeof(tx_pkt), 0);
		}
		close(client_sock);
	}
	pthread_join(thr, NULL);
	close(sock);
}

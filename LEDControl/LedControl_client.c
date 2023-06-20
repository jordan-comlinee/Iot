#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "LedControl.h"


void fill_pkt(LCH_t *p)
{
	char str[100];
	p->magic = MAGIC;
	p->Op = REQ;
	printf("Select Type (1:Get,  2:SET)  :");
	gets(str);
	p->SubOp = (unsigned char)atoi(str);
	printf("Select LED Num (1~4) : ");
	gets(str);
	p->led = (unsigned char)atoi(str);
	if(p->SubOp == SET)
	{
		printf("Select Command (1:On, 2:Off, 3:blink) : ");
		gets(str);
		p->cmd = (unsigned char)atoi(str);
	}
	else	// GET
	{
		p->cmd = LED_NOP;
	}

}

void check(LCH_t *p)
{
	printf("Rx Packet - Op:%d, SubOp:%d, cmd:%d, led:%d\n", p->Op, p->SubOp, p->cmd, p->led);
	if(p->magic != MAGIC)	printf("Magic Error\n");
	if(p->Op != REP)	printf("Op Error\n");
	if(p->SubOp == GET)
	{
		printf("Status of LED %d :  ", p->led);
		switch(p->cmd)
		{
			case LED_ON:	printf("On\n");	break;
			case LED_OFF:	printf("Off\n"); break;
			case LED_BLINK:	printf("Blinking\n"); break;
			default:	break;
		}
	}
	else	printf("Message was successfully delivered.\n");

}

int main(void)
{
	int sock;
	struct sockaddr_in addr;

	LCH_t pkt;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);

	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		printf("connect error\n");
		return 1;
	}
	while(1)
	{
		fill_pkt(&pkt);
		send(sock, (void *)&pkt, sizeof(pkt), 0);
		recv(sock, (void *)&pkt, sizeof(pkt), 0);
		check(&pkt);
	}
	close(sock);

}

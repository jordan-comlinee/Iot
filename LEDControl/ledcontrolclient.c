#include "ledcontrol.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#define PORT 9999

void fill_pkt(LCH_t *p)
{
	char str[100];
	p->magic = MAGIC;
	p->operation = REQ;
	printf("select type (1: GET | 2: SET) :");
	p->subOperation = atoi(gets(str));
	printf("select LED num : ");
	p->led = atoi(gets(str));
	if(p->subOperation == SET) {
		printf("select command (1: ON | 2: OFF | 3: BLINK | 4: NOP) : ");
		p->cmd = atoi(gets(str));
	}

}
void check(LCH_t *p)
{
	if(p->magic != MAGIC)	printf("Magic Error!\n");
	if(p->operation != REP)	printf("Op Error!\n");
	if(p->cmd == GET)
	{
		printf("LED %d : ", p->led);
		switch(p->cmd)
		{
			case LED_ON :	printf("On\n"); break;
			case LED_OFF : 	printf("Off\n"); break;
		}
	}
}

int main(void) {


	LCH_t pkt;

	//file num
	int sock;
	struct sockaddr_in addr;
	char buffer[1024];
	const char s[128];
	int recv_len;
	printf("CLient says: ");
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket ");
		return 1;
	
	}

	memset(&addr, 0x00, sizeof(addr));

	addr.sin_family = AF_INET;

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	addr.sin_port = htons(PORT);
	
	if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		printf("connect ");
		return 1;
	}
	
	while(1) {

		fill_pkt(&pkt);
		if(send(sock, &pkt, sizeof(&pkt), 0) < 0) {
			printf("send ");
			return 1;
		}

		if((recv_len = recv(sock, buffer, 1024, 0)) < 0) {
			printf("recv ");
			return 1;
		}



		//buffer[recv_len] = '\0';
		//printf("received data: %s\n", buffer);
		
		//if(strcmp(buffer, "quit")==0) {
		//	break;
		//}
	}
	close(sock);


	return 0;



}

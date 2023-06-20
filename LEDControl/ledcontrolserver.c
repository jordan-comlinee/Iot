#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999

typedef struct ledControlHeader
{
	unsigned long magicCode;

	// 1 : LCH_REQUEST | 2 : LCH_RESPONSE
	unsigned char operation;
	// 1 : GET | 2 : SET
	unsigned char subOperation;
	// 1 : ON | 2 : OFF | 3: BLINK | 4 : NOP(not operating)
	unsigned char command;
	// 
	unsigned char LED_number;

} LCH_t;

int main(void) {
	LCH_t pkt;

	
	int sock, client_sock;
	struct sockaddr_in addr, client_addr;
	char buffer[1024];
	int len, addr_len, recv_len;
	printf("waiting for client. . . \n");

	if((sock = socket(AF_INET, SOCK_STREAM, 0))<0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		printf("bind ");
		return 1;
	}
	// if listen error -> memory allocation failed
	if(listen(sock, 5) < 0){
		printf("listen ");
		return 1;
	}

	addr_len = sizeof(client_addr);

	
	// accept only one client
	while((client_sock = accept(sock, (struct sockaddr *)&client_addr,&addr_len)) > 0) {
		
		printf("client ip: %s\n", inet_ntoa(client_addr.sin_addr));
		
		while(1) {
			printf("connect success\n");		
			if((recv_len = recv(client_sock, &pkt, sizeof(pkt), 0)) < 0){
				printf("recv ");
				return 1;
				break;
			}
			if (pkt.command == 1) {
				printf("pkt.command: %d\n", pkt.command);
				printf("pkt.operation: %d\n", pkt.operation);
				printf("quit\n");
				close(client_sock);
			}
			else {	
				printf("pkt.command: %d\n", pkt.command);
				printf("pkt.operation: %d\n", pkt.operation);
				printf("2\n");
			}

			//buffer[recv_len] = '\0';
			//send(client_sock, pkt, strlen(pkt), 0);
		}
	}
	close(sock);
	return 0;

}

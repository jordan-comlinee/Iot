#include <string.h>
#include <unistd.h>
// library for socket
#include <sys/types.h>
#include <sys/socket.h>
//
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#define PORT 9999

int main(void) {
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
		printf("Client says: ");


		scanf("%s", s);

		if(send(sock, s, sizeof(s), 0) < 0) {
			printf("send ");
			return 1;
		}

		if((recv_len = recv(sock, buffer, 1024, 0)) < 0) {
			printf("recv ");
			return 1;
		}


		buffer[recv_len] = '\0';
		

		printf("received data: %s\n", buffer);
		
		if(strcmp(buffer, "quit")==0) {
			break;
		}
	}
	close(sock);


	return 0;



}

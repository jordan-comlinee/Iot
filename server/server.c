#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999

int main(void) {
	int sock, client_sock;
	struct sockaddr_in addr, client_addr;
	char buffer[1024];
	int len, addr_len, recv_len;
	printf("waiting for client. . . ");

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

		if((recv_len = recv(client_sock, buffer, 1024, 0)) < 0){
			printf("recv ");
			return 1;
			break;
		}
		buffer[recv_len] = '\0';
		printf("received data: %s\n", buffer);
		send(client_sock, buffer, strlen(buffer), 0);
		
		close(client_sock);
	}
	close(sock);
	return 0;

}

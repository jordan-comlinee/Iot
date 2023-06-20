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
	scanf("%s", s);

	// if socket fd(file descript) is lower than 0, It's error, shut down the program
	// fd have 0, 1, 2 address....it never change. They have it's own meaning! 2 means error
	// AF_INET = IPv4(we'll use IPv4) | SOCK_STREAM = TCP (SOCK_DGRAM = UDP)
	// 3rd param, 0 is protocol, if errors, return -1
	// type <<man soscket>> to see the DETAILS!!!
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		//perror("socket "); -- It appears on error only terminal!
		printf("socket ");
		return 1;
	
	}
	// memset is to set the memory. where, to what, how much
	memset(&addr, 0x00, sizeof(addr));
	// fill the addr struct . . . IPv4, server's address, PORT
	addr.sin_family = AF_INET;
	// iner_addr make STRING address to int adddress..
	// So it gets string and returns unsigned long.
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// They get server's port number.
	addr.sin_port = htons(PORT);
	
	// connect, socket, address, size of address. If error, shut down
	if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		printf("connect ");
		return 1;
	}
	// msg is data, strlen(msg) is size of string... so send them in this size
	if(send(sock, s, sizeof(s), 0) < 0) {
		printf("send ");
		return 1;
	}
	// recieve it. If send, then recieve it asap.
	// If not, you'll cannot recieve the data. recv get the address of buffer.
	// So, when it recieve, they save the data in the address of buffer.
	// if data overs 1024, data overflow happens, so recv() get the size of buffer
	if((recv_len = recv(sock, buffer, 1024, 0)) < 0) {
		printf("recv ");
		return 1;
	}

	// after receive, you always have to end with 'null' data. so we append null(\0) at the end.
	buffer[recv_len] = '\0';

	printf("received data: %s\n", buffer);

	close(sock);

	return 0;



}

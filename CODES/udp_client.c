// 17114024 Deepansh Nagaria
// Client code using UDP

#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define IP_PROTOCOL 0 
#define IP_ADDRESS "127.0.0.1" 
#define PORT_NO 15050 
#define BUFF_SIZE 32 
#define cipherKey 'S' 
#define sendrecvflag 0 


// function for decryption 
char decrypt(char ch) 
{ 
	return ch ^ cipherKey; 
} 

// function to clear buffer 
void clear_buffer(char* b) 
{ 
	int i; 
	for (i = 0; i < BUFF_SIZE; i++) 
		b[i] = '\0'; 
} 

// function to receive file 
int receive_file(char* buf, int s) 
{ 
	int i; 
	char ch; 
	for (i = 0; i < s; i++) { 
		ch = buf[i]; 
		ch = decrypt(ch); 
		if (ch == EOF) 
			return 1; 
		else
			printf("%c", ch); 
	} 
	return 0; 
} 



// driver code 
int main() 
{ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
	char net_buf[BUFF_SIZE]; 
	FILE* fp; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, 
					IP_PROTOCOL); 

	if (sockfd < 0) 
		printf("\nfile descriptor not received!!\n"); 
	else
		printf("\nDescriptor %d received\n", sockfd); 

	while (1) { 
		printf("\nEnter file name :\n"); 
		scanf("%s", net_buf); 
		sendto(sockfd, net_buf, BUFF_SIZE, 
			sendrecvflag, (struct sockaddr*)&addr_con, 
			addrlen); 

		printf("\n Received !\n"); 

		while (1) { 
			// receive 
			clear_buffer(net_buf); 
			nBytes = recvfrom(sockfd, net_buf, BUFF_SIZE, 
							sendrecvflag, (struct sockaddr*)&addr_con, 
							&addrlen); 

			// process 
			if (receive_file(net_buf, BUFF_SIZE)) { 
				break; 
			} 
		} 
		printf("\n done \n"); 
	} 
	return 0; 
} 

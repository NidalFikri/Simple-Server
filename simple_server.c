/*
 ============================================================================
 Name        : simple_server.c
 Author      : Nidal Fikri
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handling.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 7892 // The port users will be connecting to.

int main(void) {

	int sock_fd, new_sock_fd;	//Listen on sock_fd, new connection on new_fd
	struct sockaddr_in host_addr, client_addr;   // My address information
	socklen_t sin_size;
	int recv_length=1,yes=1;
	char buffer[1024];

	//creating the socket.
	if((sock_fd = socket(PF_INET,SOCK_STREAM,0)) ==-1) die("in creating socket.");
	//Setting the socket opptions to reuse the port and take control of it.
	if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) ==-1) die("in setting socket options.");

	//Setting up the host struct.
	host_addr.sin_family = AF_INET;		//setting the address family.
	host_addr.sin_port = htons(PORT);	//convert to network byte order.
	host_addr.sin_addr.s_addr=0;		//Automatically fill with my IP.
	memset(&(host_addr.sin_zero),'\0',8);//set up the padding.

	//Bind the socket.
	if (bind(sock_fd,(struct sockaddr *)&host_addr,sizeof(struct sockaddr))==-1) die("in binding.");
	//activating listening mode.
	if(listen(sock_fd,10) ==-1) die("in listening");	//10 = queue size.

	while (1)	//accepting loop.
	{
		sin_size = sizeof(struct sockaddr_in);
		new_sock_fd = accept(sock_fd,(struct sockaddr *)&client_addr,&sin_size );
		if (new_sock_fd == -1) die("in accepting.");

		printf("Sever got connection from %s port %d\n",inet_ntoa(client_addr.sin_addr),5);
		send(new_sock_fd,"Hello World!",13,0);	//send hello message by the server.
		recv_length = recv(new_sock_fd,&buffer,1024,0);

		while(recv_length > 0)
		{
			printf("RECV : %d Bytes\n",recv_length);
			dump(buffer,recv_length);	//dumping the revived data.
			recv_length = recv(new_sock_fd,&buffer,1024,0);
		}
		close(new_sock_fd);
	}
	//close(sock_fd);	
	return EXIT_SUCCESS;
}

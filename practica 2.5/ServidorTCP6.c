#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#define BUF_SIZE 80

int main(int argc, char *argv[]) {

	struct addrinfo hints, *result;
	int sfd,clisd,rc;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;

	char buf[BUF_SIZE],host[NI_MAXHOST], service[NI_MAXSERV];

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE;  
  
	// .ej2 192.168.0.1 7777
	rc = getaddrinfo(argv[1], argv[2], &hints, &result);

	if(rc==-1){
		printf("Error getaddrinfo \n");
		return -1;
	}

	sfd = socket(result->ai_family, result->ai_socktype,0);

	bind(sfd, result->ai_addr, result->ai_addrlen);

	freeaddrinfo(result);           
	
	listen(sfd,15); //Añadir listen
	
	while (1) {
		
		clisd = accept(sfd,(struct sockaddr *)&peer_addr,&peer_addr_len);
		
		getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV);
		
		printf("Conexión desde Host: %s Puerto:%s\n",host,service);

		while(rc = recv(clisd,buf,79,0)){ //Tanto recv como send van con clisd
			printf("recibiendo \n");
			buf[rc]='\n';
			printf("\t mensaje :%s\n",buf);
			send(clisd, buf, BUF_SIZE, 0);

		}
		printf("saliendo ...\n");

	}

	return 0;
}

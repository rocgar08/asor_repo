#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>

#define BUF_SIZE 500


int main(int argc, char *argv[]) {

	struct addrinfo hints, *result;
	int sfd,clisd,rc,status;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;
	char buf[BUF_SIZE],host[NI_MAXHOST], service[NI_MAXSERV];

	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE;  
  
	// .ej2 192.168.0.1 7777
	rc = getaddrinfo(argv[1], argv[2], &hints, &result);

	if(rc!=0){
		printf("Error getaddrinfo %s\n",gai_strerror(rc));
		return -1;
	}

	sfd = socket(result->ai_family,result->ai_socktype,result->ai_protocol);

	if(sfd!=0){
		printf("Error sfd %s\n",gai_strerror(sfd));
		return -1;
	}

	if(bind(sfd, result->ai_addr, result->ai_addrlen)!=0){
		printf("Error en bind \n");
		return -1;
	}

	freeaddrinfo(result);           
	listen(sfd,50);

	while (1) {

		//Acepto las conexiones
		clisd = accept(sfd,(struct sockaddr *)&peer_addr,&peer_addr_len);
		if(clisd!=0){
			printf("No Aceptando las conexiones %s\n",gai_strerror(clisd));
			return -1;
		}
		//accept-and-fork
		pid_t pid = fork();
		
		switch(pid){

			case -1: 
				printf("Error \n");
				return -1;
			break;

			case 0:

				if(getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, 
						host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV)!=0){
					printf("Error en getnameinfo %s\n");						
					return -1;
				}

				while(rc =recv(clisd,buf,BUF_SIZE,0)){
					printf("[PID: %i]Received bytes from %s:%s\n", getpid(), host, service);
					buf[rc]='\n';
					printf("Mensaje: %s\n",buf);
					send(sfd,buf,BUF_SIZE,0);
				}
				
			break;
			case 1:
				wait(NULL);
				printf("Terminando proceso\n");
			break;
		}
	
	}
	close(sfd);
	close(clisd);
	return 0;
}

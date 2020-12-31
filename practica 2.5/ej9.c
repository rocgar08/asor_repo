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

void handle(){
	wait(NULL);
	printf("Terminando proceso\n");
}

int main(int argc, char *argv[]) {

	struct addrinfo hints, *result;
	int sfd,clisd,rc,status;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;
	char buf[BUF_SIZE],host[NI_MAXHOST], service[NI_MAXSERV];

	struct sigaction sa;
	sa.sa_handler = handle;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGCHLD,&sa,NULL);

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE;  /*0.0.0.0*/
  
	// .ej2 192.168.0.1 7777
	rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	if(rc!=0){
		printf("Error getaddrinfo \n");
		return -1;
	}

	sfd = socket(result->ai_family,result->ai_socktype,result->ai_protocol);

	if(sfd!=0){
		fprintf(stderr, "socket: %s\n", gai_strerror(sfd));
		return -1;
	}

	bind(sfd,result->ai_addr, result->ai_addrlen);
	

	freeaddrinfo(result);           
	listen(sfd,50);

	while (1) {

		//Acepto las conexiones
		clisd = accept(sfd,(struct sockaddr *)&peer_addr,&peer_addr_len);
		//accept-and-fork
		pid_t pid = fork();
		
		switch(pid){

			case -1: 
				printf("Error \n");
				return -1;
			break;

			case 0:
				getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, 
					    host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV);

				while(rc =recv(clisd,buf,BUF_SIZE,0)){
					printf("[PID: %i]Received bytes from %s:%s\n", getpid(), host, service);
					buf[rc]='\n';
					printf("Mensaje: %s\n",buf);
					send(sfd,buf,BUF_SIZE,0);
				}
				
			break;
			case 1:
				handle();
			break;
		}
	
	}
	close(sfd);
	close(clisd);
	return 0;
}

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>

#define BUF_SIZE 80

void trata_conexion(int cli_sd){
	
	char buf[BUF_SIZE];
	ssize_t nread;
	while(nread = recv(cli_sd, buf,79, 0)){
		buf[nread] = '\0';
		printf("Mensaje: %s[pid]: %i\n",buf,getpid());
		send(cli_sd, buf,nread, 0);
	}
	if(nread == 0){
		printf("Fin de la conexion \n");
		close(cli_sd);
	}
}
int main(int argc, char *argv[]){

	struct addrinfo hints;
	struct addrinfo *rp;
	int sfd, s;

	struct sigaction sa;
	sigaction(SIGCHLD,&sa,NULL);
	sa.sa_handler= SIG_IGN;
	sa.sa_flags = SA_RESTART; 

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	s = getaddrinfo(argv[1], argv[2], &hints, &rp);

	if (s == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	sfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
	if (sfd == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(sfd));
		exit(EXIT_FAILURE);
	}
	bind(sfd, rp->ai_addr, rp->ai_addrlen);
	freeaddrinfo(rp);           /* No longer needed */
	
	listen(sfd,16);

	while(1){
		struct sockaddr_storage peer_addr;
		socklen_t peer_addr_len = sizeof(struct sockaddr_storage);

		char host[NI_MAXHOST], service[NI_MAXSERV];
		int cli = accept(sfd,(struct sockaddr *) &peer_addr,&peer_addr_len);
		s = getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, host,NI_MAXHOST,service,NI_MAXSERV, NI_NUMERICSERV);
		printf("Conexion desde host %s: puerto%s\n",host, service);

		pid_t pid = fork();
		switch(pid){
			case -1:
				printf("Error %s\n",gai_strerror(pid));
				return -1;
			break;
			case 0:
				close(sfd);
				trata_conexion(cli);
				return 0;
			
			default:
				close(cli);
			break;
		}

	}
	return 0;
}
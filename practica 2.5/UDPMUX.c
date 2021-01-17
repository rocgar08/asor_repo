#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 80


int main(int argc, char *argv[]) {

	struct addrinfo hints, *rp;
	int sfd, s;
	
	char bufS[BUF_SIZE],buf[2],host[NI_MAXHOST], service[NI_MAXSERV];;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */

	// ./ej2 192.168.0.1 7777
	s = getaddrinfo(argv[1], argv[2], &hints, &rp);

	if (s == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	sfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
	
	if (sfd == -1) {
		fprintf(stderr, "socket: %s\n", gai_strerror(sfd));
		return -1;
	}
	
	int b = bind(sfd, rp->ai_addr, rp->ai_addrlen);
	if (b == -1) {
		fprintf(stderr, "bind: %s\n", gai_strerror(b));
		return -1;
	}
	
	freeaddrinfo(rp);      


	while (1) {
		struct sockaddr_storage peer_addr;
		socklen_t peer_addr_len;
		ssize_t nread;
		//Necesario para sacar el anho y la fecha
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		peer_addr_len = sizeof(struct sockaddr_storage);
		getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, 
			host, NI_MAXHOST,service, NI_MAXSERV,NI_NUMERICSERV|NI_NUMERICHOST);
		
		fd_set set;
		FD_ZERO(&set);
		FD_SET(0,&set);
		FD_SET(sfd,&set);
		select(sfd + 1, &set,NULL,NULL,NULL);

		if(FD_ISSET(sfd,&set)){
			nread = recvfrom(sfd, bufS,sizeof(char), 0,(struct sockaddr *) &peer_addr, &peer_addr_len);
			printf("[PID]:%i Received %ld bytes from %s:%s\n",getpid(),(long) nread, host, service);
			bufS[nread] = '\0';
			if(nread == -1){
				printf("Error \n");
				return -1;
			}
			size_t anho = strftime(bufS,BUF_SIZE,"%H:%M:%S",tm);
			bufS[anho] = '\0';
			sendto(sfd, bufS, anho, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
			printf("Año: %s\n",bufS);
		}
		if(FD_ISSET(0,&set)){
			nread = read(sfd, buf,79);
		  	buf[nread] = '\0';
			printf("DATOS 	%s\n", buf);
			if(nread == -1){
				printf("Error \n");
				return -1;
			}
			
		}
	}
	
	close(sfd);
	return 0;
}

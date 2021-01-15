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

#define BUF_SIZE 80

int main(int argc, char *argv[]) {

	struct addrinfo hints, *rp;
	int sfd, s;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;
	
	ssize_t nread;
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
	int i = 0;
	for(i; i < 5; i++){
		pid_t pid = fork();
		if(pid!=0) continue;
		while (1) {
			//Necesario para sacar el anho y la fecha
			time_t t = time(NULL);
			struct tm *tm = localtime(&t);
			peer_addr_len = sizeof(struct sockaddr_storage);
			nread = recvfrom(sfd, buf,sizeof(char), 0,(struct sockaddr *) &peer_addr, &peer_addr_len);
			buf[1]='\0';
			getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);
			printf("[PID]:%i Received %ld bytes from %s:%s\n",getpid(),(long) nread, host, service);

			if(buf[0] == 'q'){
				printf("Bye..\n");
				return 0;
			}
			else if(buf[0] == 't'){
				size_t anho = strftime(bufS,BUF_SIZE,"%H:%M:%S",tm);
				bufS[anho] = '\0';
				sendto(sfd, bufS, anho, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
				printf("Año: %s\n",bufS);

			}
			else if(buf[0] == 'd' ){
				size_t fecha = strftime(bufS,BUF_SIZE,"%Y-%M-%d",tm);
				bufS[fecha] = '\0';
				sendto(sfd, bufS, fecha, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
				printf("Fecha: %s\n",bufS);
			}

			else{
				printf(" Error al introducir el comando tiene que ser t,d o q \n");
				return -1;
			}
		}//WHILE(1)
		
	}//FOR
	close(sfd);
	return 0;
}

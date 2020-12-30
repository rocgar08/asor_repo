#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#define BUF_SIZE 500

int main(int argc, char *argv[]) {
	struct addrinfo hints, *result;

	int sfd, s;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;

	ssize_t nread;
	char bufS[BUF_SIZE],bufC[BUF_SIZE],host[NI_MAXHOST], service[NI_MAXSERV];;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; 
	hints.ai_flags = AI_PASSIVE;    
	// .ej2 192.168.0.1 7777
	s = getaddrinfo(argv[1], argv[2], &hints, &result);

	if (s == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	sfd = socket(result->ai_family, result->ai_socktype,0);

	bind(sfd, result->ai_addr, result->ai_addrlen);

	freeaddrinfo(result);           /* No longer needed */

	while (1) {
		//Necesario para sacar el anho y la fecha
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		peer_addr_len = sizeof(struct sockaddr_storage);

		nread = recvfrom(sfd, bufC, BUF_SIZE, 0,(struct sockaddr *) &peer_addr, &peer_addr_len);
		
		bufC[nread]='\0';

		getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV);
		
		printf("Received %ld bytes from %s:%s\n",(long) nread, host, service);

		if(bufC[0] == 'q'){
			printf("Bye..\n");
			return 0;
		}

		else if(bufC[0] == 't'){
			size_t anho = strftime(bufS,BUF_SIZE,"%Y",tm);
			bufS[anho] = '\0';
			sendto(sfd, bufS, nread, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
			printf("Año %s\n",bufS);
		}
		else if(bufC[0] == 'd' ){
			size_t fecha = strftime(bufS,BUF_SIZE,"%A,%d %B %Y",tm);
			bufS[fecha] = '\0';
			sendto(sfd, bufS, nread, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
			printf("Fecha %s\n",bufS);
		}
	
		else{
			printf("Error al introducir el comando %s, tiene que ser t,d o q\n",bufC[0]);
			return -1;
		}
		
	
	}
	return 0;
}

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>

#define BUF_SIZE 500

int main(int argc, char *argv[]) {
	struct addrinfo hints, *result;

	int sfd, s;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;

	ssize_t nread;
	char bufS[BUF_SIZE],bufC[2],host[NI_MAXHOST], service[NI_MAXSERV];;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; 
	hints.ai_flags = AI_PASSIVE;    
	
	s = getaddrinfo(argv[1], argv[2], &hints, &result);

	if (s == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	sfd = socket(result->ai_family, result->ai_socktype,0);

	bind(sfd, result->ai_addr, result->ai_addrlen);

	freeaddrinfo(result);           /* No longer needed */
	fd_set set;
	
	while (1) {
		//Necesario para sacar el anho y la fecha
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		peer_addr_len = sizeof(struct sockaddr_storage);

		FD_ZERO(&set);
		FD_SET(sfd, &set);
		FD_SET(0, &set); //Para el terminal

		select(sfd + 1,&set,NULL,NULL,NULL);

		if (FD_ISSET(sfd, &set)){ //Si lo recibo desde el cliente al servidor
			nread = recvfrom(sfd, bufC,BUF_SIZE, 0,(struct sockaddr *) &peer_addr, &peer_addr_len);
			bufC[nread]='\0';
			getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV);
			printf("Received %ld bytes from %s:%s\n",(long) nread, host, service);
			size_t anho = strftime(bufS,BUF_SIZE,"%H:%M:%S",tm);
			bufS[anho] = '\0';
			sendto(sfd, bufS, nread, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
			printf("Año: %s\n",bufS);
		}

		else if(FD_ISSET(0,&set)){ //Releer de la terminal 
			nread = read(0,bufC,BUF_SIZE);
			printf("Received[terminal] %ld bytes \n",(long) nread);
			bufC[nread] = '\0';
			size_t fecha = strftime(bufS,BUF_SIZE,"%Y-%M-%d",tm);
			bufS[fecha] = '\0';
			//sendto(sfd, bufS, nread, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
			printf("Fecha: %s\n",bufS);
		}
		else{
			printf("Error en select())\n");
			return -1;
		}
	
	}
	close(sfd);
	return 0;
}

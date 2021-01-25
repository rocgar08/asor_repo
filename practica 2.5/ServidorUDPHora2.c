#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#define BUF_SIZE 80

int main(int argc, char *argv[]){

	struct addrinfo hints;
	struct addrinfo *rp;
	int sfd, s;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;
	ssize_t nread;
	char buf[BUF_SIZE];


	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */


	s = getaddrinfo(argv[1], argv[2], &hints, &rp);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	sfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
	bind(sfd, rp->ai_addr, rp->ai_addrlen);
	freeaddrinfo(rp);           /* No longer needed */

	for (;;) {
		peer_addr_len = sizeof(struct sockaddr_storage);
		nread = recvfrom(sfd, buf, BUF_SIZE, 0,
		(struct sockaddr *) &peer_addr, &peer_addr_len);
		

		char host[NI_MAXHOST], service[NI_MAXSERV];

		s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);

		printf("Received %ld bytes from %s:%s\n",(long) nread, host, service);
		time_t t = time(0);
		struct tm *tm = localtime(&t);
		size_t fecha;
		if(buf[0] == 'q'){
			printf("Bye..\n");
			return 0;
		}
		if(buf[0] == 'd'){
			fecha = strftime(buf,79,"%H:%M",tm);
			buf[fecha] = '\0';
			sendto(sfd, buf, fecha, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
			printf("Datos %s\n", buf);
		}
		
		if(buf[0] == 't'){
			fecha = strftime(buf,79,"%d/%m/%y:",tm);
			buf[fecha] = '\0';
			sendto(sfd, buf, fecha, 0,(struct sockaddr *) &peer_addr,peer_addr_len);
			printf("Datos %s\n", buf);
		}
	}
	close(sfd);
	return 0;
}

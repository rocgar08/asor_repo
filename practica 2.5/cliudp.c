#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 80
int main(int argc, char **argv){

	struct addrinfo hints;
	struct addrinfo *rp;
	struct sockaddr_storage peer_addr;
        socklen_t peer_addr_len;

	ssize_t nread;
	char buf[BUF_SIZE];
	int s, sfd;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */

	s = getaddrinfo(argv[1], argv[2], &hints, &rp);
	if (s == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	sfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
	if (sfd ==-1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(sfd));
		return -1;
	}
	int c = connect(sfd, rp->ai_addr, rp->ai_addrlen);
	if (c ==-1) {
	       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(c ));
		return -1;
	 }
	freeaddrinfo(rp);        

	while(1){
		peer_addr_len = sizeof(struct sockaddr_storage);
		//argv[3] se refiere al comando t,d o q en el server bufc[2]
		sendto(sfd,argv[3],2, 0,(struct sockaddr *) 		                &peer_addr,peer_addr_len);
		recvfrom(sfd, buf,79, 0,(struct sockaddr *)&peer_addr, &peer_addr_len);
		buf[BUF_SIZE] = '\0';
		printf("Datos: %s\n",buf);
	}
	close(sfd);
	return 0;
	
 }


           

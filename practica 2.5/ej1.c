#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char **argv){

	struct addrinfo hints;
	struct addrinfo *result,*rp;
	int sfd, rc;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE;    

	rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	if(rc!=0){
		printf("Error GETADDRINFO %s\n", gai_strerror(rc));
		return -1;
	}
	
	for(rp = result;rp!=NULL;rp = rp->ai_next){
		char host[NI_MAXHOST], service[NI_MAXSERV];
		getnameinfo(rp->ai_addr,rp->ai_addrlen, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV);
		printf("HOST: %s PUERTO: %s\n",host,service);

	}
	freeaddrinfo(result);
	return 0;
}
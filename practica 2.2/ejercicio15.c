#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include<time.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){

	char buf[200];
	time_t t = time(NULL);
    struct tm *tmp = localtime(&t);

	int fd = open(argv[1],O_CREAT|O_TRUNC|O_RDWR, 0666);

	int rc = lockf(fd, F_TLOCK, 0);
	
	if(rc == -1 )
	{
	   perror("lockf");
	   return 0;
		
	}

	printf("Implementando el cerrojo de escritura...\n");
	strftime(buf,sizeof(char)*200,"%H:%M",tmp);
	sleep(3);
	
	printf("Se ha activado el cerrojo de escritura\n");
	printf("En el buffer hay: %s\n",buf);
	lockf(fd, F_ULOCK, 0);
	close(fd);

	return 0;
}
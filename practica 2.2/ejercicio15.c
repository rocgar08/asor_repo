#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include<time.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){

	struct flock l;
	l.l_type = F_RDLCK;
	l.l_whence = SEEK_SET;
	l.l_start= 0;
	l.l_len = 0;
	l.l_pid = getpid();

	char buf[200];
	time_t t = time(NULL);
        struct tm *tmp = localtime(&t);

	
	int fd = open(argv[1],O_CREAT|O_TRUNC|O_RDWR, 0666);

	int status = fcntl(fd,F_GETLK,&l);
	
	if(l.l_type == F_UNLCK )
	{
		
		l.l_type = F_WRLCK;
		l.l_whence = SEEK_CUR;
		l.l_start = 0;
		l.l_len = 0;
		l.l_pid = getpid();
		
	}

        else
	{
		printf("Implementando el cerrojo de escritura...\n");
		strftime(buf,sizeof(char)*200,"%H:%M",tmp);
		sleep(3);
		return 1;
	}

	printf("Se ha activado el cerrojo de escritura\n");
	printf("En el buffer hay: %s\n",buf);
	close(fd);

	return 0;
}
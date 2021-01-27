#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv){

	struct rlimit limit;
	printf("[H] %i [P] %i [G] %i [S] %i\n",getpid(),getppid(),getpgid(),getsid(getpid()));
	printf("Current directory %s\n", get_current_dir_name());
	//Necesario para obtener el máximo nº de fds
	getrlimit(RLIMIT_NOFILE,&limit);
	printf("Max limit %lli\n",limit.rlim_max);
	
	return 0;
}
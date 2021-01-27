#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <wait.h>
int main(int argc, char **argv){

	pid_t pid = fork();
	pid_t new;
	switch(pid){
		case -1:
			printf("Error\n");
		break;
		case 0:
			new = setsid();
			chdir("/tmp");
			printf("Current directory %s\n", get_current_dir_name());
			printf("[H] %i [P] %i [G] %i [S] %i\n",getpid(),getppid(),getpgid(getpid()),getsid(getpid()));
		break;
		default:
			
			printf("[P] %i [Pp] %i [G] %i [S] %i\n",getpid(),pid,getpgid(getpid()),getsid(getpid()));
		break;
	}
	return 0;
}
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include<pwd.h>

int main(int argv, char **argc){

	uid_t real = getuid();
	uid_t effec = geteuid();
	printf("Real id %i\n", real);
	printf("effective id %i\n", effec);

	struct passwd *pw=getpwuid(real);
	if(pw==0){
		perror("getpwid");
		printf("Error",strerror(errno));
		return -1;
	}
	printf("NAME %s\n",pw->pw_name);
	printf("HOME %s\n",pw->pw_dir);
	printf("SHELL %s\n",pw->pw_shell);

	return 0;
}
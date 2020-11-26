#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argv, char **argc){

	uid_t real = getuid();
	uid_t effec = geteuid();
	printf("Real id %i\n", real);
	printf("effective id %i\n", effec);

	return 0;
}
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

	long int max_length = sysconf(_SC_ARG_MAX);
	long int max_child = sysconf(_SC_CHILD_MAX);
	long int max_files = sysconf(_SC_OPEN_MAX);

	if( max_length == -1 || max_child == -1 || max_files == -1){
		perror("sysconf");
		return -1;
	}
	printf("Max length: %li\n", max_length);
	printf("Max child: %li\n", max_child);
	printf("Max files: %li\n", max_files);
	return 0;
}

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv){
	
	char *tmp = argv[1];
	mkdir("tmp",0777);
	long int max_links = pathconf(tmp,_PC_LINK_MAX);
	long int max_path = pathconf(tmp,_PC_PATH_MAX);
	long int max_name = pathconf(tmp,_PC_NAME_MAX);

	if( max_links == -1 || max_path == -1 || max_name == -1){
		perror("pathconf");
		return -1;
	}
	printf("Max links: %li\n", max_links);
	printf("Max path: %li\n", max_path);
	printf("Max name: %li\n", max_name);
	return 0;
}
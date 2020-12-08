#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <unistd.h>

int main( int argc, char **argv) {
	
	struct stat sb;
	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		return -1;
	}
	
	char* ln = malloc((strlen(argv[1]) * sizeof(char));
	char* sym = malloc((strlen(argv[1]) * sizeof(char));

	strcpy (ln,argv[1]);
	strcpy (sym,argv[1]);

	ln = strcat(ln,".hard");
	sym = strcat(sym,".sym");

	
	switch(sb.st_mode & S_IFMT) {

		case S_IFLNK: 
			symlink(argv[1],sym); 
		break;
		case S_IFREG: 
			link(argv[1],ln);  
		break;
		default:
			printf("Es otro tipo de archivo \n");
		break;
	}

	return 0;
}

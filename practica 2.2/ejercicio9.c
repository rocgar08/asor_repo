#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>



int main( int argc, char **argv){
	
	if(argc!=2){
		printf("Necesitas 2 argumentos\n");
		return -1;

	}

	struct stat sb;
	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		return -1;
	}

	printf("ID of containing device:  [%lx,%lx]\n",
	(long) major(sb.st_dev), (long) minor(sb.st_dev));

	printf("File type:                ");

	switch (sb.st_mode & S_IFMT) {
	
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFLNK:  printf("symlink\n");                 break;
		case S_IFREG:  printf("regular file\n");            break;
		default:       printf("unknown?\n");                break;
	
	}
	
	printf("I-node number:            %ld\n", (long) sb.st_ino);

	printf("Mode:                     %lo (octal)\n",
	(unsigned long) sb.st_mode);


	printf("Last status change:       %s", ctime(&sb.st_ctime));
	printf("Last file access:         %s", ctime(&sb.st_atime));
	printf("Last file modification:   %s", ctime(&sb.st_mtime));


	return 0;
}


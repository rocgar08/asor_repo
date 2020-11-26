#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

int main (int argc, char **argv){
	
	struct utsname buf;
	int rc = uname(&buf);
	
	if( rc == -1){
		perror("uname");
		return -1;	
	}
	
	printf("sysname %s\n",buf.sysname);
	printf("nodename %s\n",buf.nodename);
	printf("release %s\n",buf.release);
	printf("version %s\n",buf.version);
	printf("machine %s\n",buf.machine);

	return 0;
}

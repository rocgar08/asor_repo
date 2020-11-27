#include<stdio.h>
#include<string.h>
#include<time.h>
#include<errno.h>
#include<sys/time.h>

int main(int argc, char **argv){

	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char buff[100];
	
 	strftime(buff,100,"%A,%d %B %Y,%H:%M",tm);
	printf("Hoy es: %s\n",buff);

	return 0;
}
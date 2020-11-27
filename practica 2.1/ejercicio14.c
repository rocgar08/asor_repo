#include<stdio.h>
#include<string.h>
#include<time.h>
#include<errno.h>
#include<sys/time.h>

int main(int argv, char **argc){
	time_t t =time(NULL); 
	struct tm *local=localtime(&t);
	int anho = local->tm_year;
	printf("El año es %i\n",1900+anho);
	return 0;
}


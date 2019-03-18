#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "nCr.h"

int main(int argc, char ** argv){
	struct timeval tv;
	struct timezone tz;
	int time = gettimeofday(&tv, &tz);
	int former = tv.tv_usec;
	char * n1 = argv[1];
	int len = strlen(n1);
	int i = 0, power = 0;
	for(i = 0; i < len; i++){
		 power = power * 10 + n1[i] - '0';
	}
	if(power < 0){
		printf("ERROR, the input power is less than 0\n");
		return 0;
	}
	int coe = nCr(power,0);
	if(coe == 0){
		printf("ERROR, the input n is too large\n");
		return 0;
	}
	printf("(1 + x)^%d = 1",power);
	for( i = 1; i <= power; i++){
		 coe = nCr(power, i);
		printf(" + %d*x^%d",coe,i);
	}
	printf("\n");
	time = gettimeofday(&tv, &tz);
	int later = tv.tv_usec;
	int period = later - former;
	printf("Time Required = %d microsecond\n",period);
	return 0;
}

#include <stdio.h>
#include <string.h>
int num[400];
long add(long a, long b){
	return a + b;
}

long compute_fib(int i ){
	int temp = 0;
	
	if(num[i] == -1){
		if(i == 0){
			num[i] = 0;
		}else if(i == 1){
			num[i] = 1;
		}else{
			num[i] = add(compute_fib(i-2),compute_fib(i-1));
		}
	}
	temp = num[i];
	return temp;
}
int main(int argc, char ** argv){
	int i;
	int a = atoi(argv[1]);
	for ( i = 0; i <= 199; i++){
		num[i] = -1;
	}
	printf("Value :    %d\n",compute_fib(a));
	return 0;
}

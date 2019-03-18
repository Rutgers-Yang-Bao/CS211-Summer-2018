int nCr(int n, int r){
	int a = Factorial(n);
	int b = Factorial(r);
	int c = Factorial(n-r);
	if( a == 0){
		return 0;
	}
	return a / (b * c);
}
int Factorial(int n){
	if(n > 20 ){
		return 0;
	}
	if(n <= 0){
		return 1;
	}
	else{
		return n * Factorial((n-1));
	}
}

#include	<stdio.h>
#include	<string.h>
//#include	"intToDecASCII.h"
// Convert IEEE 32-bit floating point to printable ASCII string

// input:  x is the 32-bit input.
// output:  digit is the output ASCII character
// output:  pow10 is the original pre-normalization power of 10.
// output: remainder is x after subtracting the higi-digit value

static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
	int p10;
	if ( x == 0.0 )
	{
		*digit = '0';			// digit is always '0'
		*pow10 = 0;
		*remainder = 0.0;
	}
	else
	{
		*pow10 = 0;			// start with 10^0
		while ( x >= 10.0 )		// reduce
		{
			x /= 10.0;		// large values get smaller
			*pow10 += 1;
		}
		while ( x < 1.0 )		// increase
		{
			x *= 10.0;		// small values get larger
			*pow10 -= 1;
		}
		*digit = '0';
		do {				// 10.0 > x >= 1.0
			x -= 1.0;
			*digit += 1;		// digit is always non-'0'zero
		} while ( x >= 1.0 );
		p10 = 0;
		while ( p10 > *pow10 )		// leading digit is now removed from x
		{
			x /= 10;
			p10 -= 1;
		}
		while ( p10 < *pow10 )
		{
			x *= 10;
			p10 += 1;
		}
		*remainder = x;
	}	
}

static void
append( char * s, char c )
{
	char buf[2];

	buf[0] = c;
	buf[1] = '\0';
	strcat( s, buf );
}
union Number {
	int i;
	float f;
};

void
floatToASCII( float x, char * output )
{
	char c;
	int pow10, p10, plast;
	int i;
	float remainder;
	char exponent[10];
	union Number a;
	unsigned int biasedExp;
	unsigned int mantissa;
	int sign;

	a.f = x;
	biasedExp = a.i >> 23 & 0x000000ff;
	mantissa = a.i & 0x007fffff;
	sign = a.i >> 31;
	// +/- inf, +/- Nan stuff here
	output[0] = '\0';
	if ( x < 0.0 )
	{
		append( output, '-' );
		x = -x;					// make x positive
	}
	get_float_digit( x, &c, &pow10, &remainder );
	append( output, c );
	append( output, '.' );
	x = remainder;
	plast = p10 = pow10;			// pow10 set by get_float_digit()
	for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
	{
		get_float_digit( x, &c, &p10, &remainder );
		if ( (plast - p10) > 1 )
		{
			append( output, '0' );	// fill in zero to next nonzero digit
			plast -= 1;
		}
		else
		{
			append( output, c );
			x =  remainder;
			plast = p10;
		}
	}
	exponent[0] = 'e';
	strcat( output, exponent );
	for( i = 0; output[i] != '\0'; i++){
		printf("%c",output[i]);
	}
	printf("%d\n",pow10);
}

int transToInt(int val[]){
	int value = 0;
	int i = 0;
	for( i = 1; i <= val[0]; i++){
		value = value * 2 + val[i];
	}
	return value;
}

float power(int a){
	int i = 0;
	float value = 1;
	if( a > 0){
		for( i = 0; i < a; i++){
			value *= 2;
		}
	}
	else{
 		a = -a;
		for( i = 0; i < a; i++){
			value /= 2;
		}
	}
	return value;
} 

float transToFloat(int  s[]){
	int ex[9] = {0}, value[24] = {0};
	int i = 0;
	int isNeg = 0;
	if(s[0] == '1'){
		isNeg = 1;
	}
	for(i = 1; i < 9; i++){
		ex[++ex[0]] = s[i];
	}
	for(i = 9; i < 32; i++){
		value[++value[0]] = s[i];
	}
	int a = transToInt(&ex[0]);
	int b = transToInt(&value[0]);
	a = a - 127;
	float c = power(23);
	float answer = ( 1 + b / c) * power(a);
	if(isNeg == 1){
		answer = 0 - answer;
		return answer;
	}
	return answer;	
}	 


void toDecimal(int num[], int sign){
	int x = 0, i = 0, j = 0;
	int index = 0;
	if(sign == 1){
		int zero[32] = {0};
		for( i = 31; i >= 0; i--){
			int temp = zero[i] - num[i] - x;
			if(temp < 0){
				temp = temp + 2;
				x = 1;
			}
			num[i] = temp;
		}
	}
	while (num[index] == 0 && index < 32){
		index ++ ;
	}
	if(index == 32){
		printf("0");
		return;
	}
	int len = 32 - index;
	int start[33] = {0}, ans[33] = {0}, res[33] = {0};
	start[0] = len;
	j = 1;
	for(i = index; i < 32; i++){
		start[j] = num[i];
		j++;
	}
	while(start[0] >= 1){
		x = 0;
		i = 1;
		ans[0] = start[0];
		while(i <= start[0]){
			x = x * 2 + start[i];
			ans[i++] = x / 10;
			x %= 10;
		}
		res[++res[0]] = x;
		i = 1;
		while((i <= ans[0]) && (ans[i] == 0)) i++;
		memset(start,0,sizeof(start));
		for( j = i; j <= ans[0]; j++){
			start[++start[0]] = ans[j];
		}
		memset(ans,0,sizeof(ans));
	}
	if(sign == 1){
		printf("-");
	}
	for(i = res[0]; i > 0; i--){
		printf("%d",res[i]);
	}
	printf("\n");
}

int main(int argc, char ** argv){
	if(argv[1] == '\0' || argv[2] == '\0'){
		printf("ERROR, not enough input \n");
		return 0;
	}
	if(strlen(argv[1]) != 32){
		printf("ERROR, the bit length of the input is wrong.\n");
		return 0;
	}
	
	char * n = argv[1];
	char * type = argv[2];
	int num[32] = {0};
	int i = 0;
	int out = 0;
	int isNeg = 0;
	char final[100];
	for( i = 0; i < 32; i++){
		num[i] = n[i] - '0';
		if(num[i] != 0 && num[i] != 1){
			printf("ERROR, the format of input number is wrong.\n");
			return 0;
		}
	}
	if(strcmp(type, "int") == 0){
		out = 1;
	}else if (strcmp(type, "float") == 0){
		out = 2;
	}else{
		printf("ERROR, the output base is wrong.\n");
		return 0;
	}

	if(num[0] == 1){
		isNeg = 1;
	}
	
	if(out == 1){
		toDecimal(&num[0],isNeg);
	}		
	else{  	
		int check1 = 0;
		int check2 = 0;
		switch(num[1]){
		case(1):
			check1 = 1;
			for( i = 2; i < 9; i++){
				if(num[i] != 1){
					check1 = 2;
				}
			}
			break;
		case(0):
			check1 = 0;
			for( i = 2; i < 9; i++){
				if(num[i] != 0){
					check2 = 2;
				}
			}
			break;
		}
		switch(num[9]){
		case(1):
			check2 = 1;
			for( i = 10; i < 32; i++){
				if(num[i] != 1){
					check2 = 2;
				}
			}
			break;
		case(0):
			check2 = 0;
			for( i = 10; i < 32; i++){
				if(num[i] != 0){
					check2 = 2;
				}
			}
		}
		
		if(check1 == 0 && check2 == 0 ){
			if(isNeg == 1){
				printf("-");
			}
			printf("0.0e0\n");
			return 0;
		}

		if(check1 == 1){
			if(check2 == 0){
				if(isNeg == 1){
					printf("ninf\n");
				}
				else{
					printf("pinf\n");
				}
			}
			else{
				printf("NaN\n");
			}
			return 0;
		}
		
		float output = transToFloat(&num[0]);
		floatToASCII(output, final);
	}
	return 0;
}

#include <stdio.h>
#include <string.h>

void lowerCase(char * s){
	int i = 1;
	for( i = 1; s[i] != '\0'; i++){
		if(s[i] >= 'A' && s[i] <= 'F'){
			s[i] += 32;
		}
	}
}

int checkNum(char * s){
	int i = 1;
	int len = strlen(s);
	

	switch(s[0]){
	case'd':
		if(len > 19){ 
			return 0;
		}
		for ( i = 1; s[i] != '\0'; i++){
			if(s[i] - '0' > 9 || s[i] - '0' < 0){
				return 0;
			}
		}
		break;
	case'b':
		if(len > 65){
			return 0;
		}
		for ( i = 1; s[i] != '\0'; i++){
			if(s[i] - '0' > 1 || s[i] - '0' < 0){
				return 0;
			}
		}
		break;
	case'o':
		if(len > 23){
			return 0;
		}
		for ( i = 1; s[i] != '\0'; i++){
			if(s[i] - '0' > 7 || s[i] - '0' < 0){
				return 0;
			}
		}
		break;
	case'h':
		if(len > 17){
			return 0;
		}
		for ( i = 1; s[i] != '\0'; i++){
			if(s[i] - '0' > 9 || s[i] - '0' < 0){
				if(s[i] - 'a' > 5 || s[i] - 'a' < 0){
					return 0;
				}
			}
		}
		break;
	default:
		return 0;
	}
	return 1;
}





int isNeg(char * s){
	int i = 0;

	if(s[0] == '-'){
		for ( i = 0; s[i] != '\0'; i++){
			s[i] = s[i+1];
		}
		return 1;
	}
	return 0;
}	


int trans(int a[], char * s){
	int i = 1, j = 63, y = 0;
	int len = strlen(s);
	int old = 0, new = 2;
	int start[65] = {0}, ans[65] = {0}, res[100] = {0};

	start[0] = len - 1;
	switch(s[0]){
	case'b':
		for( i = len - 1; i > 0; i--){
			a[j] = s[i] - '0';
			j--;
		}
		break;
	case'd':
		old = 10;
		for( i = 1; s[i] != '\0'; i++){
			start[i] = s[i] - '0';
		}
		break;
	case'o':
		old = 8;
		for( i = 1; s[i] != '\0'; i++){
			start[i] = s[i] - '0';
		}
		break;
	case'h':
		old = 16;
		for( i = 1; s[i] != '\0'; i++){
			if(s[i] >= '0' && s[i] <= '9'){
				start[i] = s[i] - '0';
			}
			else if (s[i] >= 'a' && s[i] <= 'f'){
				start[i] = s[i] - 'a' + 10;
			}
		}
		break;
	}

	if(old == 0){
		return;
	}
	while(start[0] >= 1){
		y = 0;
		i = 1;
		ans[0] = start[0];
		while(i <= start[0]){
			y = y * old + start[i];
			ans[i++] = y / new;
			y %= new;
		}
		res[++res[0]] = y;
		i = 1;
		while( (i <= ans[0]) && (ans[i] == 0)){
			i++;
		}
		memset(start,0,sizeof(start));
		for(j = i; j <= ans[0]; j++){
			start[++start[0]] = ans[j];
		}		
		memset(ans,0,sizeof(ans));
	}	
	if(res[0] > 64){
		printf("ERROR, the input number is too big.\n");
		return 1;
	}
	else{
		j = 63;
		for(i = 1; i < 65; i++){
			a[j] = res[i];
			j--;
		}
	}
	return 0;
}

void operation(char op, int a[], int b[], int sol[]){
	int i = 0, x = 0, temp = 0;

	switch(op){
	case'+':
		for( i = 63; i >= 0; i--){
			temp = a[i] + b[i] + x;
			if( temp > 1){
				sol[i] = temp % 2;
				x = 1;
			}
			else{
				sol[i] = temp;
				x = 0;
			}
		}
		break;
	case'-':
		for( i = 63; i >=0; i--){
			temp = a[i] - b[i] - x;
			if(temp < 0){
				sol[i] = temp + 2;
				x = 1;
			}
			else{
				sol[i] = temp;
				x = 0;
			}
		}
		break;
	}
}

void output(int sol[], char base){
	int index = 0;
	int i = 0, value = 0, j = 0, y =0;
	int zero[64] = {0};
	int start[65] = {0}, ans[65] = {0}, res[65] = {0};
	int isNeg = 0;

	while (index < 64 && sol[index] == 0){
		index ++;
	}
	
	if(index == 64){
		printf("%c0\n",base);
		return;
	}
	
	switch(base){
	case'd':
		if(sol[0] == 1){
			operation('-', &zero[0], &sol[0], &sol[0]);
			isNeg = 1;
		}
		index = 0;
		while (index < 64 && sol[index] == 0){
			index ++;
		}
		start[0] = 64 - index;
		j = 1;
		for( i = index; i < 65; i++){
			start[j] = sol[i];
			j++;
		}
		while(start[0] >= 1){
			y = 0;
			i = 1;
			ans[0] = start[0];
			while (i <= start[0]){
				y = y * 2 + start[i];
				ans[i++] = y / 10;
				y %= 10;
			}
			res[++res[0]] = y;
			i = 1;
			while ((i <= ans[0]) && (ans[i] == 0)){
				i++;
			}
			memset(start,0,sizeof(start));
			for( j = i; j <= ans[0]; j++){
				start[++start[0]] = ans[j];
			}
			memset(ans,0,sizeof(ans));
		}
		if(isNeg == 1){
			printf("-");
		}
		printf("d");
		for( i = res[0]; i > 0; i--){
			printf("%d",res[i]);
		}
		printf("\n");
		break;		
	case'b':
		printf("b");
		for( i = index; i < 64; i++){
			printf("%d",sol[i]);
		}
		printf("\n");
		break;
	case'o':
		printf("o");
		for( i = index; i < 64; i = i + 3){
			value = 0;
			for ( j = i; (j < i + 3) && j < 64; j++){
				value = value * 2 + sol[j];
			}
			printf("%d",value);
		}
		printf("\n");
		break;
	case'h':
		printf("h");
		for( i = index; i < 64; i = i + 4){
			value = 0;
			for ( j = i; (j < i + 4) && j < 64; j++){
				value = value * 2 + sol[j];
			}
			if(value < 10){
				printf("%d",value);
			}
			else if (value == 10){
				printf("a");
			}
			else if (value == 11){
				printf("b");
			}
			else if (value == 12){
				printf("c");
			}
			else if (value == 13){
				printf("d");
			}
			else if (value == 14){
				printf("e");
			}
			else if (value == 15){
				printf("f");
			}
		}
		printf("\n");
		break;
	}			
 
}

int main (int argc, char ** argv){
	if(argv[1] == '\0' || argv[2] == '\0' || argv[3] == '\0' || argv[4] == '\0'){
		printf("ERROR, not enough input \n");
		return 0;
	}
	char op = *argv[1], out = *argv[4];

	char * n1 = argv[2];
	char * n2 = argv[3];

	int value1[64] = {0}, value2[64] = {0}, final[64] = {0};
	int zero[64] = {0};
	int index = 0;
	
	int check1 = isNeg(n1);
	int check2 = isNeg(n2);

	lowerCase(n1);
	lowerCase(n2);
	if( (op != '+' && op != '-') ||  
		checkNum(n1) == 0 ||
		checkNum(n2) == 0 ||
		(out != 'b' && out != 'd' && out != 'o' && out != 'h')){
		printf("ERROR, the format of the input is wrong \n");
		return 0;
	}
	
	if(trans(&value1[0], n1) == 1){
		return 0;;
	}
	if(trans(&value2[0], n2) == 1){
		return 0;
	}
	
	if(check1 ==1){
		operation('-', &zero[0], &value1[0], &value1[0]);
	}
	if(check2 ==1){
		operation('-', &zero[0], &value2[0], &value2[0]);
	}
	
	operation(op, &value1[0], &value2[0], &final[0]);

	output(&final[0], out);

	return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char temp[1000] = {0};
char spec[10] = {0};
char addr[10] = {0};
char value[1000] = {0};

void read(FILE * fp){
	memset(temp,0,sizeof(temp));
	memset(spec,0,sizeof(spec));
	memset(addr,0,sizeof(addr));
	memset(value,0,sizeof(value));
	fgets(temp, sizeof(temp)-1, fp);	
	int i = 0, j = 0;
	while(temp[i] != '\t' && temp[i] != ' ' && temp[i] != '\0'){
		spec[i] = temp[i];
		i++;
	}
	while(temp[i] == '\t' || temp[i] == ' ' || temp[i] == '\0'){

		i++;
	}
	j = i;
	while(temp[i] != '\t' && temp[i] != ' ' && temp[i] != '\0'){
		addr[i-j] = temp[i];
		i++;
	}
	while(temp[i] == '\t' || temp[i] == ' ' || temp[i] == '\0'){
		i++;
	}
	j = i;
	while(temp[i] != '\t' && temp[i] != ' ' && temp[i] != '\0' && temp[i] != '"'){
		value[i-j] = temp[i];
		i++;
	}
}

int trans(char * str){
	char temp[8] = {0};
	int answer = 0;
	temp[0] = str[6];
	temp[1] = str[7];
	temp[2] = str[4];
	temp[3] = str[5];
	temp[4] = str[2];
	temp[5] = str[3];
	temp[6] = str[0];
	temp[7] = str[1];
	sscanf(temp,"%x",&answer);
	return answer;
}

int main(int argc, char ** argv){
	char * file;
	if(argc == 2){
		file = argv[1];
	}else if (argc == 3){
		char * help = argv[1];
		if(strcmp(help,"-h") == 0){
			printf("The interface of this program is :\n");
			printf("        y86emul [-h] <y86 input file>\n");
			return 0;
		}
		else{
			printf("ERROR: Wrong input format\n");
			return 1;
		}
	}else{
		printf("ERROR: Wrong input format\n");
		return 1;
	}
	FILE * fp;
	if((fp = fopen(file,"r")) == NULL){
		printf("ERROR : Cannot find the input file\n");
		return 1;
	}
	int address,i,begin;
	int *start;
	char * code;
	int check1 = 0, check2 = 0;
	while(!feof(fp)){
		read(fp);
		sscanf(addr,"%x",&address);
		if(strcmp(spec,".size") == 0){
			start = malloc(address);
			if(start == NULL){
				printf("ERROR: fail to malloc\n");
				return 1;
			}
			check1 = 1;
		}
		else if(strcmp(spec,".string") == 0){
			char * pt = (char *) start;
			for(i = 0; i < address; i++){
				pt++;
			}
			*pt = *value;
		}
		else if(strcmp(spec,".long") == 0){
			long * pt = (long *)start;
			for(i = 0; i < address; i++){
				pt++;
			}
			*pt = atoi(value);
		}
		else if (strcmp(spec,".byte") == 0){
			int * pt = start;
			for(i = 0; i <address; i++){
				pt++;
			}
			sscanf(value,"%x", &pt);
			
		}
		else if(strcmp(spec,".text") == 0){
			begin = atoi(addr);
			code = value;
			check2 = 1;
		}
		else{
			printf("ERROR: the code in input file is wrong.\n");
			return 1;
		}
	}
	if(check1 == 0 || check2 == 0){
		printf("ERROR: the input file lost .text or .size");
		return 1;
	}
	int * pt;
	int *eax,*ecx,*edx,*ebx,*esp,*ebp,*esi,*edi;
	int * array[8] = {eax,ecx,edx,ebx,esp,ebp,esi,edi};
	int index = 0,len = 0,i1 = 0,i2 = 0, sum = 0;
	char op = code[index], ra,rb;
	char hex[8];
	while (index < strlen(code)){
		i1 = code[index + 2] - '0';
		i2 = code[index + 3] - '0';
		switch(op){
			case('0'):
				len = 2;
				break;
			case('1'):
				len = 2;
				break;
			case('2'):
				len = 4;
				*array[i2] = *array[i1];
				break;
			case('3'):
				len = 12;
				for (i = 0; i < 8; i++){
					hex[i] = code[index + i + 4];
				}
				*array[i2] = trans(hex);				
				break;
			case('4'):
				len = 12;
				for( i = 0; i < 8; i++){
					hex[i] = code[index + i + 4];
				}
				sum = trans(hex) + begin;
				pt = array[i2];
				for( i = 0; i < sum; i++){
					 pt++;
				}
				*pt = *array[i1];
				break;
			case('5'):
				len = 12;
				for( i = 0; i < 8; i++){
					hex[i] = code[index + i + 4];
				}
				sum = trans(hex) + begin;
				pt = array[i1];
				for( i = 0; i < sum; i++){
					 pt++;
				}
				*array[i2] = *pt;	
				break;
			case('6'):
				len = 4;
				switch(code[index + 1]){
					case('0'):		
						*array[i2] += *array[i1];
						break;
					case('1'):
						*array[i2] -= *array[i1];
						break;
					case('2'):
						*array[i2] = (*array[i2] )& (*array[i1]);
						break;
					case('3'):
						
					case('4'):
						*array[i2] *= *array[i1];
						break;
					case('5'):			//Further work needed
						break;
					default:
						printf("ERROR: the input code for op1 has problem.");
						return 1;
				}
				break;
			case('7'):
				len = 10;
				break;
			case('8'):
				len = 10;
				break;
			case('9'):
				len = 2;
				break;
			case('a'):
			case('A'):
				len = 4;
				break;
			case('b'):
			case('B'):
				len = 4;
				break;
			case('c'):
			case('C'):
				len = 12;
				break;
			case('d'):
			case('D'):
				len = 12;				
				break;
			case('e'):
			case('E'):
				len = 12;
				break;
			default:
				printf("ERROR, the .text of the input file has bug.\n");
				return 1;
		}
		index += len;
	}
	fclose(fp);
	free(start);
	return 0;
}


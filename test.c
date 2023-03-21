#include<stdio.h>
int main(){
	char n[5];
	scanf("%s",n);
	if(n[0]==n[4]&&n[1]==n[3]){
		printf("这个数是回文数\n");
	}
	else{
		printf("这个数不是回文数\n");
	}
	return 0;
}

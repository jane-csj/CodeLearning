#include<stdio.h>
int main(){
	char n[5];
	scanf("%s",n);
	if(n[0]==n[4]&&n[1]==n[3]){
		printf("������ǻ�����\n");
	}
	else{
		printf("��������ǻ�����\n");
	}
	return 0;
}

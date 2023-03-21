#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
const int M=2e5+5;
const int N=2e5;
#define ll long long
int n,m,s;
int main(){
	for(int a=1;a<=12;a++){
		int i;
		if(a==1||a==3||a==5||a==7||a==8||a==10||a==12)i=31;
		else i=30;
		if(a==2)i=28;
		for(int k=1;k<=i;k++){
		printf("%02d%02d\n",a,k);
		}
	} 
	return 0;
}	

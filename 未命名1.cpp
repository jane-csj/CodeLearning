#include<iostream>
using namespace std;
#define ll long long

int main(){
	double x,p;
	cin>>x>>p;
	double ans=0;
	for(double i=1;i<1000;i++){
		double win=i;
		double fal=(1.0-p/100)*win/(p/100);
		double sum=win-fal+(double)(fal-win)*x/100;
		cout<<win<<" "<<fal<<endl;
		ans=max(ans,sum);
	}
	printf("%lf",ans);
	return 0;
} 

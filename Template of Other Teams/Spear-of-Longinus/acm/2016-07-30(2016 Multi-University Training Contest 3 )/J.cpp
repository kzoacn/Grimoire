#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,v1,v2;
	while(scanf("%d%d%d",&a,&v1,&v2)==3){
		if(a==0){
			printf("%.10f\n",0);
			continue;
		}
		if(v1<=v2){
			puts("Infinity");
			continue;
		}
		double ans=1.0*a*v1/(1.0*v1*v1-1.0*v2*v2);
		printf("%.10f\n",ans);
	}
	return 0;
}

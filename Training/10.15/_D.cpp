#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n;
double pw;
double vw[maxn],pf[maxn],vf[maxn],th[maxn];

double calc(double w){
	double ans=w*pw;
	for(int i=1;i<=n;i++){
		double f=max(0.0,(th[i]-w*vw[i])/vf[i]);
		ans+=f*pf[i];
	}
	return ans;
}

int main(){
	while(scanf("%d",&n)==1&&n){
		scanf("%lf",&pw);
		for(int i=1;i<=n;i++){
			scanf("%lf%lf%lf%lf",&vw[i],&pf[i],&vf[i],&th[i]);
		}
		double l=0,r=1e8;
	
		while(1){
			double mid1=l+(r-l)/3;
			double mid2=r-(r-l)/3;
			double res1=calc(mid1);
			double res2=calc(mid2);
			if(res1>res2){
				l=mid1;
			}else{
				r=mid2;
			}
			if(fabs(res1-res2)<1e-7)break;
		}
		printf("%.10f\n",calc(l));
	}
	return 0;
}

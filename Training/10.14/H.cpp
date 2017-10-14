#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;

typedef __float128 LD;

LD logfac[maxn];
LD logC(int n,int m){
	return logfac[n]-logfac[m]-logfac[n-m];
}
LD h,w;
int n;

LD f(LD h,LD n){
	return h/(n+1)/(n+1);
}

int main(){
	double th,tw;
	cin>>th>>tw;
	cin>>n;
	h=th;w=tw;
	
	logfac[0]=logfac[1]=0;
	for(int i=2;i<=n;i++)
		logfac[i]=logfac[i-1]+logl(i);
		
	LD ans=0;
	LD ln2=logl(2);	
	for(int i=0;i<=n;i++){
		LD prob=logC(n,i)-n*ln2;
		prob=expl(prob);
		ans+=prob*f(h,i)*f(w,n-i);
	}
	
	printf("%.40f\n",(double)ans);
	return 0;
}

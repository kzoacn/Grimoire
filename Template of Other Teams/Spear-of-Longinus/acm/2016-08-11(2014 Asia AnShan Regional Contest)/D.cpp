#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=50010;
typedef long long LL;
int n,k;
LL sum[maxn],sum2[maxn];
int a[maxn];
long double sqr(long double x){return x*x;}
LL sqr(LL x){return x*x;}
LL S1,S2,xbar;
long double calc(){
	return (S2) - sqr(S1)/double(n-k);
}
int main(){
	int T;
	scanf("%d",&T);	
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			sum[i]=sum[i-1]+(LL)a[i];
			sum2[i]=sum2[i-1]+(LL)sqr((LL)a[i]);
		}	
		
		if(n==k){
			puts("0.000000000000");
			continue;
		}
		
		long double ans=1e50;
		for(int i=1;i+(n-k)-1<=n;i++){
			S1=sum[i+(n-k)-1]-sum[i-1];
			S2=sum2[i+(n-k)-1]-sum2[i-1];
			
			ans=min(ans,calc());
		}
		printf("%.12f\n",(double)ans);
	}
	return 0;
}



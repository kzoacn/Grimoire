#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
int n;
int w[maxn];
LL gcd(LL a,LL b){
	if(!b)return a;
	return gcd(b,a%b);
}
int main(){
	int T;scanf("%d",&T);	
	while(T--){
		scanf("%d",&n);
		LL sumsq=0,sqsum=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&w[i]);
			w[i]=abs(w[i]);
		}
		for(int i=1;i<=n;i++){
			sqsum+=w[i];
			sumsq+=(LL)w[i]*w[i];
		}
		sqsum=sqsum*sqsum;
		if(sqsum>=sumsq*n){
			puts("0/1");
			continue;
		}
		LL mom=n*sumsq-sqsum;
		LL son=n;
		LL d=gcd(mom,son);
		mom/=d;
		son/=d;
		cout<<mom<<"/"<<son<<endl;
	}
	return 0;
}

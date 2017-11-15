#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e6+1e5;
const LL mo=1e9+7;
LL fac[maxn],inv[maxn];

LL C(int n,int m){
	if(m>n)return 0;
	return fac[n]*inv[m]%mo*inv[n-m]%mo;
}

int main(){
	
	fac[0]=fac[1]=1;
	inv[0]=inv[1]=1;
	
	for(int i=2;i<maxn;i++){
		fac[i]=fac[i-1]*i%mo;
	}
	for(int i=2;i<maxn;i++){
		inv[i]=(mo-mo/i)*inv[mo%i]%mo;
	}
	for(int i=2;i<maxn;i++)
		inv[i]=inv[i]*inv[i-1]%mo;
		
	int T;
	cin>>T;
	for(int t=1;t<=T;++t){
		int n,m;
		scanf("%d%d",&n,&m);
		
		for(int i=1;i<=n;i++){
			int c;scanf("%d",&c);
			while(c--)scanf("%*d");
		}
		
		printf("Case #%d: %lld\n",t,C(m-1,n-1));
	}
		
	return 0;
}

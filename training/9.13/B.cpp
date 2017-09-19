#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
typedef long long LL;
const int mo=1e9+7;	
LL d[maxn],g[maxn];
int mu[maxn];

int p[maxn];
bool notp[maxn];

int BFg(int n){
	
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=(n+i-1)/i;
	}
	return ans;
}

void sieve(){
	mu[1]=1;
	for(int i=2;i<maxn;i++){
		if(!notp[i]){
			p[++p[0]]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=p[0]&&i*p[j]<maxn;j++){
			notp[i*p[j]]=1;
			if(i%p[j]==0){
				mu[i*p[j]]=0;
				break;
			}else{
				mu[i*p[j]]=-mu[i];
			}
		}
	}
	for(int i=1;i<maxn;i++){
		for(int j=i;j<maxn;j+=i){
			d[j]++;
		}
	}
	for(int i=1;i<maxn;i++){
		g[i]=(d[i-1]+i)%mo;
		d[i]+=d[i-1];
		d[i]%=mo;
		mu[i]+=mu[i-1];
	}
	for(int i=1;i<maxn;i++){
		g[i]+=g[i-1];
		g[i]%=mo;
	}
}


int main(){
	sieve();
	int n;
	while(scanf("%d",&n)==1){
		long long ans=0;
		for(int i=1,j;i<=n;i=j+1){
			j=n/(n/i);
			ans+=(mu[j]-mu[i-1]+mo)%mo*g[n/i]%mo;
		}
		printf("%lld\n",ans%mo);
	}
	return 0;
}

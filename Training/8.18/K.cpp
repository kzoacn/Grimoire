#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans%p;
}

LL C,k1,b1,k2;

bool check(LL a,LL b){
	return (pw(a,k1*2+b1,C)+pw(b,k2*2-k2+1,C))%C==0;
}

int main(){
	int T=0;
	while(cin>>C>>k1>>b1>>k2){
		printf("Case #%d:\n",++T);
		int sz=0;
		static pair<LL,LL> anss[int(2e5+5)];
		for(LL a=1;a<C;a++){
			LL b=(C-pw(a,k1+b1,C))%C;
			if(check(a,b)&&b){
				++sz;
				anss[sz].first=a;
				anss[sz].second=b;	
			}
		}
		if(!sz)puts("-1");
		else{
			for(int i=1;i<=sz;i++)
				printf("%lld %lld\n",anss[i].first,anss[i].second);
		}
	}
	return 0;
}

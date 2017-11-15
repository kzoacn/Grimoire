#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1e9+7;
LL pw(LL x,LL k,LL p=::mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans;
}

LL inv(LL x){
	return pw(x,mo-2,mo);
}
LL S(LL a,LL n){
	if(n==-1)return 0;
	
	LL ans=(pw(a,n+1)-1+mo)%mo;
	
	ans=ans*inv(a-1)%mo;
	return ans;
}

LL S(LL a,LL l,LL r){
	if(a==1)return r-l+1;
	return (S(a,r)-S(a,l-1)+mo)%mo;
}
int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		int n;
		scanf("%d",&n);
		LL ans=1;
		for(int i=1;i<=n;i++){
			LL a,b,c;
			scanf("%lld%lld%lld",&a,&b,&c);
			ans=ans*S(a,b,c)%mo;
		}
		printf("Case #%d: %lld\n",t,(ans%mo+mo)%mo);
	}
	return 0;
}

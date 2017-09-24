#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1e9+7;
LL pw(LL x,LL k,LL p=::mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%mo;
		x=x*x%mo;
	}
	return ans;
}
LL inv(LL x){
	return pw(x,mo-2,mo);
}

LL fix(LL x){
	while(x<0)
		x+=mo;
	x%=mo;
	return x;
}
int main(){
	int T;cin>>T;
	while(T--){
		LL p,q,k;
		cin>>p>>q>>k;
		LL x=q*inv(p)%mo;
		LL b1=fix(1-x-inv(2)+mo+mo);
		LL bk=b1*pw(fix(1-2*x),k-1)%mo;
		LL ak=bk+inv(2);
		ak%=mo;
		printf("%lld\n",ak);
	}
	return 0;
}

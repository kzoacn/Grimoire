#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL p=1000000000622593LL;
//const LL p=998244353;
//const LL p=1051721729LL;

vector<LL>dv;

LL mul(LL x,LL k,LL p){
	LL ans=0;
	
	for(;k;k>>=1){
		if(k&1)ans=(ans+x)%p;
		x=(x+x)%p;
	}
	return ans;
}


LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=mul(ans,x,p);
		x=mul(x,x,p);
	}
	return ans;
}
bool check(LL g){
	for(auto d:dv){
		if(pw(g,d,p)==1)
			return false;
	}
	return true;
}

int main(){
	for(LL i=2;i*i<=p-1;i++){
		if((p-1)%i==0){
			dv.push_back(i);
			dv.push_back((p-1)/i);
		}
	}
	
	cerr<<dv.size()<<endl;
	for(int i=2;;i++){
		if(check(i)){
			cout<<"proot = "<<i<<endl;
			return 0;
		}
	}
	
	return 0;
}

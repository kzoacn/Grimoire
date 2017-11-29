#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAGIC=200;
LL p;
int q;
LL g;
LL pw(LL x,LL k,LL p=::p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans%p;
}

LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;
		return a;
	}
	LL d=exgcd(b,a%b,x,y);
	LL t=x;x=y;y=t-a/b*x;
	return d;
}

LL inv(LL x,LL p){
	return pw(x,p-2,p);
}

unordered_map<LL,int>M;

LL BSGS(LL x){
	LL ginv=inv(g,p);
	LL e=x%p;
	for(LL b=0;b<MAGIC;b++){
		if(M.count(e))
			return (M[e]*MAGIC+b)%(p-1);
		e=e*ginv%p;
	}
	assert(0);
	return -1;
}


LL sol(LL a,LL b,LL m){
	LL d=__gcd(a,m);
	if(b%d)return -1;
	LL x,y;
	exgcd(a/d,m/d,x,y);
	
//	cerr<<"exgcd"<<endl;
//	cerr<<x<<" "<<y<<endl;
	
	x=x*b/d;
	m/=d;
	return (x%m+m)%m;
}
LL Q(LL x,LL y){

	if(x==0&&y==0)return 1;
	if(x==0&&y==1)return 0;
	if(x==0)return -1;
	if(x!=0&&y==0)return -1;

	LL i=BSGS(x);
	LL j=BSGS(y);
	
	//cerr<<x<<" "<<y<<endl;
	//cerr<<i<<" "<<j<<endl;
	
	return sol(i,j,p-1);
}
vector<LL>fac;
bool check(LL g){
	for(auto d:fac){
		if(pw(g,d,p)==1)
			return false;
	}
	return true;
	
}
int main(){
//freopen("alot.in","r",stdin);
//freopen("alot.out","w",stdout);
	cin>>p>>q;
	
	for(LL i=2;i*i<=p-1;i++){
		if((p-1)%i==0){
			fac.push_back(i);
			fac.push_back((p-1)/i);
		}
	}
	for(int i=2;;i++){
		if(check(i)){
			g=i;
			break;
		}
	}
	
	//cerr<<"g="<<g<<endl;
	
	LL gMAGIC=pw(g,MAGIC);
	LL e=1;
	for(int i=0;i<p/MAGIC+10;i++){
		if(!M.count(e))
			M[e]=i;
		e=e*gMAGIC%p;
	}
	/*cerr<<"M"<<endl;
	for(auto pr:M){
		cerr<<pr.first<<" "<<pr.second<<endl;
	}
	cerr<<"M end"<<endl;*/
	
	while(q--){
		LL x,y;
		cin>>x>>y;
		printf("%lld\n",Q(x,y));
	}
	return 0;
}

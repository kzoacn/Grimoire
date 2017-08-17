#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e6+6;
typedef pair<LL,LL> pii;
bool notp[maxn];
LL p[maxn];
LL pricnt[maxn];
pair<LL,LL>priprod[maxn];
LL prod[2020],inv[2020];
LL n,m;
void sieve(){
	memset(notp,0,sizeof notp);
	p[0]=0;
	for(int i=2;i<maxn;i++){
		if(!notp[i]){
			p[++p[0]]=i;
		}
		for(int j=1;j<=p[0]&&i*p[j]<maxn;j++){
			notp[i*p[j]]=1;
			if(i%p[j]==0)
				break;
		}
	}
	pricnt[1]=0;
	priprod[1]=pii(0,1);
	for(int i=2;i<maxn;i++){
		pricnt[i]=pricnt[i-1];
		priprod[i]=priprod[i-1];
		if(!notp[i]){
			pricnt[i]++;
			LL x=0,y=i;
			while(y%m==0){
				x++;
				y/=m;
			}
			priprod[i].first+=x;
			priprod[i].second=priprod[i].second*y%m;
		}
	}
}


LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans;
}
LL pprod=1;
pair<LL,LL>comput(LL n,LL p){
	if(n<=1)return make_pair(0,1);
	LL ans=1,cnt=0;
	ans=pw(pprod,n/p,p);
	
	cnt=n/p;
	
	pair<LL,LL>res=comput(n/p,p);
	cnt+=res.first;
	ans=ans*res.second%p;
	
	for(LL i=n-n%p+1;i<=n;i++)if(i%p){
		ans=ans*i%p;		
	}
	
	return make_pair(cnt,ans);
}
pair<LL,LL> calc(LL n,LL p){
	pprod=1;
	for(int i=1;i<p;i++)if(i%p)pprod=pprod*i%p;
	return comput(n,p);
}

pair<LL,LL>fact(LL n){//n! = m^first *second	

	return calc(n,m);
	
	LL ans1=0,ans2=1;
	for(;n;n/=m){
		ans1+=n/m;
		ans2=ans2*prod[n%m]%m;
	}
	return make_pair(ans1,ans2);
}

map<pair<LL,LL>,pair<LL,LL> >M;

pii divd(pii a,pii b){
	return pii(a.first-b.first,a.second*inv[b.second]%m);
}
map<pair<LL,LL>,LL>gMap;
LL g(LL n,LL k){
	if(n<maxn&&p[k]*p[k]<n)
		return pricnt[n];
	if(gMap.count({n,k}))
		return gMap[{n,k}];
	if(k==0)
		return n;
	return gMap[{n,k}]=g(n,k-1)-g(n/p[k],k-1);
}
pii f(LL n,LL k){
	if(M.count({n,k}))
		return M[{n,k}];
	if(n<maxn&&p[k]*p[k]<n)
		return priprod[n];
	if(k==0)
		return M[{n,k}]=fact(n);
	if(n<=p[k])
		return pii(0,1);
	M[{n,k}]=divd(f(n,k-1),f(n/p[k],k-1));
	if(p[k]==m){
		M[{n,k}].first-=g(n/p[k],k-1);
		
	}else{	
		int p = pw(::p[k], g(n / ::p[k], k - 1), m);
		p = pw(p, m - 2, m);
		M[{n, k}].second = 1LL * M[{n, k}].second * p % m;
	}
	return M[{n,k}];
}


LL bf(LL n,LL m){
	LL ans=1;
	for(int i=1;i<=p[0]&&p[i]<=n;i++){
		if(p[i]!=m)
			ans=ans*p[i]%m;
	}
	return ans;
}
LL solve(){
	scanf("%lld%lld",&n,&m);
	sieve();
	if(n<=m*m){
		return bf(n,m);
	}
	
	//M.clear();
	
	prod[0]=1;
	for(int i=1;i<m;i++)
		prod[i]=prod[i-1]*i%m;
	inv[0]=inv[1]=1;
	for(int i=2;i<m;i++)
		inv[i]=(m-m/i)*inv[m%i]%m;
	
	int k=1;
	for(;p[k]*p[k]<=n;k++);
	
	pii ans=f(n,k);
	
//	for(int i=1;i<=n;i++)
//		printf("fact(%d)=m^%lld * %lld\n",i,calc(i,m).first,calc(i,m).second);
	/*
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++)
			printf("f(%d,%d)=%lld^%lld * %lld\n",i,j,m,f(i,j).first,f(i,j).second);
	}
	*/
	for(int i=1;i<=k;i++){
		if(p[i]==m)continue;
		ans.second=ans.second*p[i]%m;
	}
	//cerr<<"bf is "<<bf(n,m)<<endl;
	return ans.second;
}
int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %lld\n",t,solve());
	}
	
	return 0;
}

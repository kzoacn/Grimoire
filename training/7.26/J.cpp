#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL mul(LL a,LL b,LL p){
	LL t=(a*b-LL((long double)a*b/p)*p)%p;
	return (t+p)%p;
}

LL pow(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=mul(ans,x,p);
		x=mul(x,x,p);
	}
	return ans%p;
}

LL prod=1;
pair<LL,LL> comput(LL n,LL p){
	if(n<=1)return make_pair(0,1);
	LL ans=1,cnt=0;
	ans=pow(prod,n/p,p);
	cnt=n/p;
	pair<LL,LL>res=comput(n/p,p);
	cnt+=res.first;
	ans=mul(ans,res.second,p);
	for(LL i=n-n%p+1;i<=n;i++)if(i%p){
		ans=mul(ans,i,p);
	}	
	return make_pair(cnt,ans);
}
pair<LL,LL>calc(LL n,LL p){
	prod=1;
	for(LL i=1;i<p;i++)if(i%p)prod=mul(prod,i,p);
	pair<LL,LL>res=comput(n,p);
	return res;
}
LL inv(LL x,LL p){
	return pow(x,p-2,p);
}
LL calc(LL n,LL m,LL p){
	pair<LL,LL>A,B,C;
	A=calc(n,p);
	B=calc(m,p);
	C=calc(n-m,p);
	if(A.first-B.first-C.first>0)return 0;
	LL ans=1;
	ans=mul(ans,A.second,p);
	ans=mul(ans,inv(B.second,p),p);
	ans=mul(ans,inv(C.second,p),p);
	return ans;
}
LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;
		return a;
	}else{
		LL d=exgcd(b,a%b,x,y);
		LL t=x;x=y;y=t-a/b*y;
		return d;
	}
}
LL mo[20],a[20];
LL china(int n,LL *a,LL *m){
	LL M=1,d,x=0,y;
	for(int i=0;i<n;i++)
		M*=m[i];
	for(int i=0;i<n;i++){
		LL w=M/m[i];
		d=exgcd(m[i],w,d,y);
		y=(y%M+M)%M;
		x=(x+mul(mul(y,w,M),a[i],M))%M;
	}
	while(x<0)x+=M;
	return x;
}
void solve(){
	LL n,m,k;
	cin>>n>>m>>k;
	for(int i=0;i<k;i++){
		cin>>mo[i];
		a[i]=calc(n,m,mo[i]);
	}		
	LL ans=china(k,a,mo);
	printf("%lld\n",ans);
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}

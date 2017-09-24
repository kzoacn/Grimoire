#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;


int q,M,m;

LL pri[maxn],pk[maxn],Pk[maxn];// for m=p^k  Pk=p^k
LL a[maxn],ak[maxn];// x=a* p^ ak (mod p^k)
int num[maxn];
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

LL china(int n,LL *a,LL *m){
	LL M=1,d,x=0,y;
	for(int i=0;i<n;i++)M*=m[i];
	for(int i=0;i<n;i++){
		LL w=M/m[i];
		d=exgcd(m[i],w,d,y);
		x=(x+y*w%M*a[i])%M;
	}
	if(x<0)x+=M;
	return x;
}
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans;
}
LL inv(LL a,LL p){
	LL d,x,y;
	d=exgcd(a,p,x,y);
	return d==1?(x+p)%p:-1;
}
void solve(){
	scanf("%d%d",&q,&M);
	m=0;
	
	for(int i=2;i*i<=M;i++){
		if(M%i==0){
			pri[m]=i;
			pk[m]=0;
			Pk[m]=1;
			while(M%i==0){
				pk[m]++;
				Pk[m]*=i;
				M/=i;
			}
			m++;
		}
	}
	if(M>1){
		pri[m]=M;
		pk[m]=1;
		Pk[m]=M;
		m++;
	}
	for(int i=0;i<m;i++){
		a[i]=1;
		ak[i]=0;
	}
	
	for(int j=1;j<=q;j++){
		int ty;scanf("%d",&ty);
		if(ty==1){
			scanf("%d",&num[j]);
			for(int i=0;i<m;i++){
				LL p=pri[i],k=0;
				LL tmp=num[j];
				while(tmp%p==0){
					k++;
					tmp/=p;
				}
				tmp%=Pk[i];
				
				a[i]=a[i]*tmp%Pk[i];
				ak[i]+=k;
				
			}
		}else{
			int t;scanf("%d",&t);
			for(int i=0;i<m;i++){
				LL p=pri[i],k=0;
				LL tmp=num[t];
				while(tmp%p==0){
					k++;
					tmp/=p;
				}
				tmp%=Pk[i];
				
				a[i]=a[i]*inv(tmp,Pk[i])%Pk[i];
				ak[i]-=k;
				
			}
		}
		
		static LL tmpa[maxn];
		for(int i=0;i<m;i++){
			tmpa[i]=a[i]*pw(pri[i],ak[i],Pk[i]);
		}
		LL ans=china(m,tmpa,Pk);
		printf("%lld\n",ans);
	}
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		solve();
	}
	return 0;
}

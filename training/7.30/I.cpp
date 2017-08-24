#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1e9+7;
const int maxn=2e5+5;
int a[maxn],n;
LL mu[maxn];
LL inv[maxn];

LL bf(){
	LL ans=0;
	int mn=*min_element(a+1,a+1+n);
	for(int d=2;d<=mn;d++){
		LL prod=1;
		for(int i=1;i<=n;i++){
			prod*=(a[i]/d);
			prod%=mo;
		}
		ans+=(mu[d]*prod%mo+mo)%mo;
		ans%=mo;
	}
	ans+=mo;
	ans%=mo;
	ans=(mo-ans)%mo;
	return ans;
}

int count(int x){
	int ans=0;
	for(int j=1,k;j<=x;j=k+1){
			k=x/(x/j);
			ans++;
	}return ans;
}

LL pw(LL x,LL k,LL p){
	LL ans=1%p;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans;
}
int cnt[maxn];
LL sum[maxn];

#define S(l,r) (sum[r]-sum[l-1])

int main(){
	
	mu[1]=1;
	for(int i=1;i<maxn;i++){
		for(int j=i+i;j<maxn;j+=i)
			mu[j]-=mu[i];
	}
	inv[1]=1;
	for(int i=2;i<maxn;i++){
		inv[i]=(mo-mo/i)*inv[mo%i]%mo;
	}
	
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		memset(cnt,0,sizeof cnt);//T<=10
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			cnt[a[i]]++;
		}
		for(int i=1;i<maxn;i++)
			sum[i]=sum[i-1]+cnt[i];
		int mn=*min_element(a+1,a+1+n);
		LL ans=0;
		for(int d=2;d<=mn;d++){
			LL prod=1;
			for(int i=1;(i+1)*d-1<maxn;i++){
				prod=prod*pw(i,S(i*d,(i+1)*d-1),mo)%mo;
			}
			//cerr<<d<<" "<<prod<<endl;
			ans+=(mu[d]*prod%mo+mo)%mo;
			ans%=mo;
		}		
		ans=(mo-ans)%mo;
		printf("Case #%d: %lld\n",t,ans);
	}

	return 0;
}

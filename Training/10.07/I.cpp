#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1e9+7;
const LL MOD = mo;
const LL M = 5000;
const LL maxn=100000000000LL / M + 100;
const LL B = sqrt(100000000000.0);
LL inv2=(mo+1)/2;

LL l,r,k;

bool isprime(LL x){
	for(LL i=2;i*i<=x;i++)
		if(x%i==0)
			return false;
	return true;
}
int mnp(LL x){
	for(LL i=2;i*i<=x;i++)
		if(x%i==0)
			return i;
	return x;
}


bool notp[maxn];
int p[maxn];
int maxp[maxn];
int sum[maxn];
int mu[maxn];// TODO!
void sieve(){
	mu[1]=1;
	for(int i=2;i<maxn;i++){
		if(!notp[i]){
			p[++p[0]]=i;
			mu[i]=-1;
			maxp[i]=i;
		}
		for(int j=1;j<=p[0]&&i*p[j]<maxn;j++){
			notp[i*p[j]]=1;
			maxp[i*p[j]]=max(p[j],maxp[i]);
			if(i%p[j]==0){
				mu[i*p[j]]=0;
				
				break;
			}else{
				mu[i*p[j]]=-mu[i];
			}
		}
	}
}

LL f(LL n,LL k){
	if (n == 0) {
		return 0;
	}
	if(k==0){
		n %= MOD;
		return n%mo*(n+1)%mo*inv2%mo;
	}
	if (p[k] >= n) {
		return 1;
	}
	if(1LL * p[k]*p[k]>=n) {
		int r = n >= maxn ? p[0] + 1 : upper_bound(p + 1, p + p[0] + 1, n) - p - 1;
		return (sum[r] - sum[k] + 1 + MOD) % MOD;
	}
	return (f(n,k-1)-f(n/p[k],k - 1)*p[k]%mo+mo)%mo;
}
LL get(LL n){
	if (n == 0) {
		return 0;
	}
	if(k > M){
		LL ans=0;
		for(LL d=1;;d++){
			LL l=(n/d/k)%mo;
			if(n / d / k == 0) break;
			if(maxp[d]>=k||d%k==0)
				continue;
			LL tmp = l * (l + 1) % MOD * inv2 % MOD * ((k * d) % MOD) % MOD;
			ans=(ans+mu[d] * tmp)%mo;
		}
		return (ans + mo) % mo;
	}
	/*if (k > B) {
		return (k <= n) * k % MOD;
	}
	else*/{
		for (int i = 1; i <= p[0]; ++i) {
			sum[i] = sum[i - 1] + p[i];
			sum[i] %= MOD;
		}
		int l=1;
		while(1ll*p[l]<k)
			l++;
		--l;
		return f(n/k,l)*k%mo;
	}
}

LL bf(int l,int r){
	LL ans=0;
	for(int i=l;i<=r;i++){
		if(mnp(i)==k){
			ans+=i;
			ans%=mo;
		}
	}
	return ans;
}


int main(){
	sieve();
	scanf("%*d");
	while(scanf("%lld%lld%lld",&l,&r,&k)==3){
		static int T=0;
		if(!isprime(k)){
			printf("Case #%d: %lld\n",++T,0LL);
			continue;
		}
		//cout << get(r) << endl;  return 0;
		LL ans=(get(r)-get(l - 1)+mo)%mo;
		//cout << get(l - 1) << " " << get(r) << endl;
		//LL res=bf(l,r);
		//cerr<<res<<endl;
		printf("Case #%d: %lld\n",++T,ans);
		//assert(res==ans);
	}
	return 0;
}



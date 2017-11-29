#include<bits/stdc++.h>
using namespace std;
const int maxn=262144+10;
typedef __int128 L128;
typedef long long LL;
const L128 MOD=1000000000622593LL;
const L128 PRT=5;

int n;
#define mul(a,b,p) ((L128)a*b%p)
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=mul(ans,x,p);
		x=mul(x,x,p);
	}
	return ans;
}


void DFT(LL *a,int n,int f){
	for(register int i=0,j=0;i<n;i++){
		if(i>j)swap(a[i],a[j]);
		for(register int t=n>>1;(j^=t)<t;t>>=1);
	}
	for(register int i=2;i<=n;i<<=1){
		static LL exp[maxn];
		exp[0]=1;exp[1]=pw(PRT,(MOD-1)/i,MOD);
		if(f==1)exp[1]=pw(exp[1],MOD-2,MOD);
		for(register int k=2;k<(i>>1);k++){
			exp[k]=mul(exp[k-1],exp[1],MOD);
		}
		for(register int j=0;j<n;j+=i){
			for(register int k=0;k<(i>>1);k++){
				register LL &pA=a[j+k],&pB=a[j+k+(i>>1)];
				register L128 B=(L128)pB*exp[k];
				pB=(pA-B)%MOD;
				pA=(pA+B)%MOD;
			}
		}
	}
	if(f==1){
		register LL rev=pw(n,MOD-2,MOD);
		for(register int i=0;i<n;i++){
			a[i]=mul(a[i],rev,MOD);
			if(a[i]<0)a[i]+=MOD;
		}
	}
}

void multiply(int n,LL *a,LL *b,LL *c){
	int l=1;
	while((1<<l)<n)l++;
	l++;
	for(int i=n;i<=(1<<l);i++)a[i]=b[i]=0;
	n=1<<l;
	DFT(a,n,0);
	DFT(b,n,0);
	for(int i=0;i<n;i++)	
		c[i]=mul(a[i],b[i],MOD);
	DFT(c,n,1);
}
int sum,a[maxn],s[maxn];

LL fl[maxn],fr[maxn],tmp[maxn];

int main(){
	int T;scanf("%d",&T);	
	while(T--){
		scanf("%d",&n);
		sum=s[0]=0;		
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			s[i]=s[i-1]+a[i];
			sum+=a[i];
		}
		static LL ans[maxn];
		
		ans[0]=0;
		LL l=0;
		a[n+1]=1;
		for(int i=1;i<=n+1;i++){
			if(a[i]){
				ans[0]+=l*(l+1)*(l+1)/2 - l*(l+1)*(2*l+1)/6;
				l=0;
			}else{
				l++;
			}
		}
		fill(fl,fl+sum+1,0);
		fill(fr,fr+sum+1,0);
		for(int i=0;i<n;i++)	
			fl[sum-s[i]]++;
		for(int i=1;i<=n;i++)
			fr[s[i]]+=i;
			

		multiply(sum+1,fl,fr,tmp);
		

		for(int i=sum+1;i<=2*sum;i++){
			ans[i-sum]=tmp[i];
		}
		
		
		fill(fl,fl+sum+1,0);
		fill(fr,fr+sum+1,0);
		for(int i=0;i<n;i++)	
			fl[sum-s[i]]+=i;
		for(int i=1;i<=n;i++)
			fr[s[i]]++;

		
		multiply(sum+1,fl,fr,tmp);
		

		
		for(int i=sum+1;i<=2*sum;i++){
			ans[i-sum]-=tmp[i];
		}
		
		
		for(int i=0;i<=sum;i++){
			printf("%lld\n",ans[i]);
		}
	}

	return 0;
}

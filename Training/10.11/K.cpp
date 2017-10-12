#include<bits/stdc++.h>

#define __zzq __attribute__((optimize("O3"))) __inline

using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
const int maxn=65536+10;
LL pw(LL x,LL k,LL mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%mo;
		x=x*x%mo;
	}
	return ans;
}


struct NTT{

#define meminit(A,l,r) memset(A+(l),0,sizeof(*A)*((r)-(l))
#define memcopy(B,A,l,r) memcpy(B,A+(l),sizeof(*A)((r)-(l)))

int MOD,PRT;

__zzq void DFT(int *a,int n,int f){
	for(register int i=0,j=0;i<n;i++){
		if(i>j)swap(a[i],a[j]);
		for(register int t=n>>1;(j^=t)<t;t>>=1);
	}
	for(register int i=2;i<=n;i<<=1){
		static int exp[maxn];
		exp[0]=1;exp[1]=pw(PRT,(MOD-1)/i,MOD);
		if(f==1)exp[1]=pw(exp[1],MOD-2,MOD);
		for(register int k=2;k<(i>>1);k++){
			exp[k]=1ll*exp[k-1]*exp[1]%MOD;
		}
		for(register int j=0;j<n;j+=i){
			for(register int k=0;k<(i>>1);k++){
				int &pA=a[j+k],&pB=a[j+k+(i>>1)];
				LL B=1ll*pB*exp[k];
				pB=(pA-B+MOD)%MOD;
				pA=(pA+B)%MOD;
			}
		}
	}
	if(f==1){
		register int rev=pw(n,MOD-2,MOD);
		for(register int i=0;i<n;i++){
			a[i]=1ll*a[i]*rev%MOD;
			if(a[i]<0){a[i]+=MOD;}
		}
	}
}

}*FFT[3];

int inv[3][3];
__zzq int CRT(int *a){
//cerr<<"sfd"<<endl;
	static int x[3];
	for(int i=0;i<3;i++){
		x[i]=a[i];
		for(int j=0;j<i;j++){
			int t=(x[i]-x[j]+FFT[i]->MOD)%FFT[i]->MOD;
			if(t<0)t+=FFT[i]->MOD;
			x[i]=1ll*t*inv[j][i]%FFT[i]->MOD;
		}
	}
	int sum=1,ret=x[0]%MOD;
	for(int i=1;i<3;i++){
		sum=1ll*sum*FFT[i-1]->MOD%MOD;
		ret+=1ll*x[i]*sum%MOD;
		if(ret>=MOD)ret-=MOD;
	}
	return ret;
}


__zzq void mul(int n,int a[],int b[],int c[]){
	int l=0;
	while((1<<l)<n)l++;
	l++;
	for(int i=n;i<=(1<<l);i++)a[i]=b[i]=0;
	n=1<<l;
	static int tmpa[maxn],tmpb[maxn];
	static int tmpc[3][maxn];
	
	for(int j=0;j<3;j++){
		for(int i=0;i<n;i++){
			tmpa[i]=a[i];
			tmpb[i]=b[i];
		}
		FFT[j]->DFT(tmpa,n,0);
		FFT[j]->DFT(tmpb,n,0);
		for(int i=0;i<n;i++)
			tmpc[j][i]=1ll*tmpa[i]*tmpb[i]%FFT[j]->MOD;
		FFT[j]->DFT(tmpc[j],n,1);
	}
	static int x[3];
	for(int i=0;i<n;i++){
		x[0]=tmpc[0][i];
		x[1]=tmpc[1][i];
		x[2]=tmpc[2][i];
		c[i]=CRT(x);
	}
}

LL fac[maxn],_inv[maxn],invf[maxn];


int f[maxn],g[maxn];


__zzq int calc(int N,int *a){
	int n;
	n=N+5;
	
	
	for(int j=0;j<=a[0];j++)
		g[j]=invf[j];
	for(int j=a[0]+1;j<=n;j++)
		g[j]=0;
	
	for(int i=1;i<=4;i++){
		for(int j=0;j<=a[i];j++)
			f[j]=invf[j];
		for(int j=a[i]+1;j<=n;j++)
			f[j]=0;
		mul(n,g,f,g);
	}
	
	int ans=0;
	ans=g[N];
	ans=1ll*ans*fac[N]%MOD;
	return ans;
}

__zzq int solve(){
	int N,a[5];
	scanf("%d%d%d%d%d%d",&N,&a[0],&a[1],&a[2],&a[3],&a[4]);	
	int ans1=calc(N,a);
	int ans2=0;
	if(a[0]){
		a[0]--;
		N--;
		ans2=calc(N,a);
	}
	
	return (ans1-ans2+MOD)%MOD;
	
}

int main(){
	
	fac[0]=_inv[1]=_inv[0]=1;
	for(int i=1;i<maxn;i++)
		fac[i]=fac[i-1]*i%MOD;
	for(int i=2;i<maxn;i++){
		_inv[i]=(MOD-MOD/i)*_inv[MOD%i]%MOD;
	}
	invf[0]=1;
	for(int i=1;i<maxn;i++)
		invf[i]=invf[i-1]*_inv[i]%MOD;
		
	FFT[0]=new NTT();
	FFT[0]->MOD=1053818881;
	FFT[0]->PRT=7;
	
	FFT[1]=new NTT();
	FFT[1]->MOD=1051721729;
	FFT[1]->PRT=6;
	
	FFT[2]=new NTT();
	FFT[2]->MOD=1045430273;
	FFT[2]->PRT=3;
	
	for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
		inv[i][j]=pw(FFT[i]->MOD,FFT[j]->MOD-2,FFT[j]->MOD);	
	
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %d\n",t,solve());
	}	
		
	return 0;
}

/*
n=9
calcf 0
1 0 0 0 0 0 0 0 0 
calcf 1
1 1 0 0 0 0 0 0 0 
calcf 2
1 1 500000004 0 0 0 0 0 0 
calcf 3
1 1 500000004 166666668 0 0 0 0 0 
calcf 4
1 1 500000004 166666668 41666667 0 0 0 0 
Case #1: 147520573

*/

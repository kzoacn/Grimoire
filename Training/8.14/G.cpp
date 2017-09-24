#include<bits/stdc++.h>
using namespace std;

#define __advance __attribute__((optimize("O3")))

int CNT = 0;

const int maxn=1e5+5;
const int mo=998244353;
__advance int pw(int x,int k,int mo=::mo){
	int ans=1;
	for(;k;k>>=1){
		if(k&1)ans=1ll*ans*x%mo;
		x=1ll*x*x%mo;
	}
	return ans%mo;
}

typedef long long LL;
int rev[maxn];
__advance void NTT(int a[],int n,int f){
	const int G=3;
	for(register int i=0;i<n;i++)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(register int i=2;i<=n;i<<=1){
		static int exp[maxn];
		exp[0]=1;exp[1]=pw(G,(mo-1)/i);
		if(f==-1)exp[1]=pw(exp[1],mo-2);
		for(register int j=0;j<n;j+=i){
			for(register int k=0;k<(i>>1);k++){
				register int &pA=a[j+k],&pB=a[j+k+(i>>1)];
				register LL A=pA,B=1ll*pB*exp[k];
				pA=(A+B)%mo;
				pB=(A-B+mo)%mo;
				
				//++CNT;
			}
		}
	}
	if(f==-1){
		int rv=pw(n,mo-2)%mo;
		for(int i=0;i<n;i++)
			a[i]=1ll*a[i]*rv%mo;
	}
}
__advance void mul(int m,int a[],int b[],int c[]){
	int n=1,len=0;
	while(n<m)n<<=1,len++;
	for(int i=1;i<n;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
	NTT(a,n,1);
	NTT(b,n,1);
	for(int i=0;i<n;i++)
		c[i]=1LL*a[i]*b[i]%mo;
	NTT(c,n,-1);
}

__advance void modi(int m,int a[]){
	for(int i=m;i<m*2;i++){
		a[i-m]=(a[i-m]+a[i])%mo;
		a[i]=0;
	}
}

int f[int(5e4+4)][2][205];
int n,m;

vector<int>G[maxn];
int fa[maxn];

__advance void dfs(int u){


	memset(f[u][0],0,sizeof(int)*(m+1));
	memset(f[u][1],0,sizeof(int)*(m+1));
	
	bool leaf=true;
	for(auto v:G[u]){
		if(v==fa[u])continue;
		leaf=false;
		fa[v]=u;
		dfs(v);
	}
	if(leaf){
		f[u][0][0]=1;
		return ;
	}

	static int a[maxn],b[maxn],c[maxn];

	for(int i=0;i<4*m+1;i++){
		a[i]=b[i]=c[i]=0;
	}
	b[0]=1;
	for(auto v:G[u]){
		if(v==fa[u])continue;
		
		for(register int i=0;i<m;i++){
			a[i]=(f[v][0][i]+f[v][1][i]*2)%mo;
		}
		
		mul(m,a,b,c);
		for(register int i=0;i<m*2;i++){
			b[i]=c[i];
			if(i>=m)
				b[i-m]=(b[i-m]+c[i])%mo;
		}
	}
	for(int i=0;i<m;i++)
		f[u][0][i]=b[i];
	
	
	
	for(int i=0;i<4*m+1;i++){
		a[i]=b[i]=c[i]=0;
	}
	b[0]=1;
	for(auto v:G[u]){
		if(v==fa[u])continue;
		
		for(register int i=0;i<m;i++){
			a[i]=(f[v][0][i]*2+f[v][1][i]*2)%mo;
		}
		
		mul(m,a,b,c);
		for(register int i=0;i<m*2;i++){
			b[i]=c[i];
			if(i>=m)
				b[i-m]=(b[i-m]+c[i])%mo;
		}
	}
	for(int i=0;i<m;i++)
		f[u][1][i]=(b[(i-1+m)%m]-f[u][0][(i-1+m)%m]+mo)%mo;
	
	
}

__advance int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)G[i].clear();
		for(int i=1;i<n;i++){
			int u,v;scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1);
		long long ans=0;
		ans=f[1][0][0]+f[1][1][0];
		printf("%lld\n",ans%mo);
		
		//fprintf(stderr, "%d\n", CNT);
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m;
double p[7][33];
int pre[33];
int base[7];
int U;
int get(int S,int x){
	return S/base[x-1]%U;
}

int newS(int S,int x,int y){
	int t=S/base[x-1]%U;
	S-=t*base[x-1];
	S+=y*base[x-1];
	return S;
}
int addS(int S,int x){
	int t=S/base[x-1]%U;
	S-=t*base[x-1];
	S+=(t+1)*base[x-1];
	return S;
}
int OneMoreTimeOneMoreChance;
int vis[100000][2];
double f[100000][2];
double dfs(int i,int S,int cor){
	//printf("%d\t%d\t%d\n",i,S,cor);
	if(i==m){
		int mx=0,mn=233;
		for(int j=1;j<=n;j++){
			mx=max(mx,get(S,j));
			mn=min(mn,get(S,j));
		}
		if(mx-mn<=1)
			return 0;
		else
			return -inf;
	}
	double &ans=f[S][cor];
	if(vis[S][cor]==OneMoreTimeOneMoreChance)
		return ans;
	
		
	vis[S][cor]=OneMoreTimeOneMoreChance;	
	ans=-inf;
	for(int j=1;j<=n;j++){
		if(get(S,j)+1>=U)continue;
		int nS=addS(S,j);
		double tmp;
		if(!cor&&pre[i+1]){
			tmp=dfs(i+1,nS,0);
		}else{
			tmp=(1+dfs(i+1,nS,1))*p[j][i+1]+dfs(i+1,nS,0)*(1-p[j][i+1]);
		}
		//if(tmp<=-1e-7)tmp=-inf;
		ans=max(ans,tmp);
	}
	return ans;
}
void solve(){
	OneMoreTimeOneMoreChance++;
	scanf("%d%d",&n,&m);
	U=(m+n-1)/n;U++;
	
	base[0]=1;
	for(int i=1;i<7;i++)
		base[i]=base[i-1]*U;
	
	for(int i=0;i<=m;i++)
		pre[i]=0;
	int K;scanf("%d",&K);	
	for(int i=1;i<=K;i++){
		int x;scanf("%d",&x);
		pre[x]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&p[i][j]);
	double ans=0;
	ans=dfs(0,0,1);	
	static int t=0;
	printf("Case %d: %.4f\n",++t,ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}



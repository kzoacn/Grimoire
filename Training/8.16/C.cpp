#include<bits/stdc++.h>
using namespace std;
const int BIT=20;
const int maxn=20020;
vector<int>G[maxn];
int sum[maxn],a[maxn];
int fa[maxn][BIT];
int n,m,dep[maxn];
void dfs(int u){
	for(int i=1;i<BIT;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]){
		if(v==fa[u][0])continue;
		fa[v][0]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
}
int ans;
void dfs2(int u){
	sum[u]=a[u];
	for(auto v:G[u]){
		if(v==fa[u][0])continue;
		dfs2(v);
		sum[u]+=sum[v];
	}
	if(u!=1){
		ans=min(ans,sum[u]+1);
	}
}
int u[int(2e5+4)],v[int(2e5+5)];
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<BIT;i++)if(d>>i&1){
		u=fa[u][i];
		
	}
	if(u==v)return u;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i]){
		u=fa[u][i];
		v=fa[v][i];
	}
	return fa[u][0];
}
int solve(){
	ans=int(1e9);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		G[i].clear();
		for(int j=0;j<BIT;j++)
			fa[i][j]=0;
		sum[i]=a[i]=0;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u[i],&v[i]);
		if(i<=n-1){
			G[u[i]].push_back(v[i]);
			G[v[i]].push_back(u[i]);
		}
	}
	
	dfs(1);
	
	for(int i=n;i<=m;i++){
		int LCA=lca(u[i],v[i]);
		a[u[i]]++;
		a[v[i]]++;
		a[LCA]-=2;
	}
	dfs2(1);
	return ans;
}
int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;
const int inf=1e9;
int a[maxn],dep[maxn];
struct edge{int u,v,w;};
vector<edge>G[maxn];
int n;
int ans=0;

int mx1[maxn],mx2[maxn];
int fa[maxn];
int son[maxn];
void dfs(int u){
	for(auto e:G[u]){
		if(e.v==fa[u])continue;
		fa[e.v]=u;
		dep[e.v]=dep[u]+e.w;
		dfs(e.v);
	}
}

void dp(int u){
	for(auto e:G[u]){
		if(e.v==fa[u])continue;
		dp(e.v);
		mx1[u]=max(mx1[u],mx1[e.v]);
		mx2[u]=max(mx2[u],mx2[e.v]);
	}
	int mxad1=a[u]-dep[u],mxad2=-a[u]-dep[u];
	for(auto e:G[u]){
		if(e.v==fa[u])continue;
		ans=max(ans,mxad1+mx2[e.v]+2*dep[u]);
		ans=max(ans,mx1[e.v]+mxad2+2*dep[u]);
		mxad1=max(mxad1,mx1[e.v]);
		mxad2=max(mxad2,mx2[e.v]);
	}
	/*
	reverse(G[u].begin(),G[u].end());
	mxad1=a[u]-dep[u],mxad2=-a[u]-dep[u];
	for(auto e:G[u]){
		if(e.v==fa[u])continue;
		ans=max(ans,mxad1+mx2[e.v]+2*dep[u]);
		ans=max(ans,mx1[e.v]+mxad2+2*dep[u]);
		mxad1=max(mxad1,mx1[e.v]);
		mxad2=max(mxad2,mx2[e.v]);
	}*/
		
	
}	



void solve(){
	scanf("%d",&n);
	ans=0;
	for(int i=1;i<=n;i++){
		G[i].clear();
		mx1[i]=mx2[i]=-inf;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});
	}
	
	ans=0;
	dfs(1);
	
	for(int i=1;i<=n;i++){
		mx1[i]=a[i]-dep[i];
		mx2[i]=-a[i]-dep[i];
	}
	
//	for(int i=1;i<=n;i++){
//		printf("%d %d %d\n",i,mx1[i],mx2[i]);
//	}
	
	dp(1);

	printf("%d\n",ans);
}

int main(){
	int T;cin>>T;
	while(T--)	
		solve();
	return 0;
}

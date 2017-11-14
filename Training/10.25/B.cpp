#include<bits/stdc++.h>
using namespace std;
const int maxn=303;

bitset<maxn>bs[maxn];
int n,m,q;
int col[maxn];
vector<int>G[maxn];
int vis[maxn];
int ans;
void dfs(int u){
	if(vis[u])return ;
	vis[u]=1;
	bs[u].reset();
	if(col[u])bs[u][u]=1;
	for(auto v:G[u]){
		dfs(v);
		if(col[u]){
			bs[u]=bs[u]|bs[v];
		}
	}
	ans+=bs[u].count();
}
int main(){
	while(scanf("%d%d%d",&n,&m,&q)==3){
		for(int i=1;i<=n;i++){
			col[i]=1;
			G[i].clear();
		}
		for(int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);
			G[u].push_back(v);
		}
		int whi=n;
		while(q--){
			int x;scanf("%d",&x);
			if(col[x]){
				whi--;
			}else{
				whi++;
			}
			col[x]^=1;
			ans=0;
			memset(vis,0,sizeof vis);
			for(int i=1;i<=n;i++)if(!vis[i])
				dfs(i);
/*
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)
					printf("%d",(int)bs[i][j]);
				puts("");
			}
*/			ans-=whi;
			printf("%d\n",ans);
		}
	}
	return 0;
}

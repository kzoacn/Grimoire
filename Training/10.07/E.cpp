#include<bits/stdc++.h>
using namespace std;

const int maxn=1010;

vector<int>G[maxn];

int n,m;
int mp[maxn][maxn],vis[maxn];
void dfs(int u){
	vis[u]=1;
	for(auto v:G[u]){
		if(!vis[v])
			dfs(v);
	}
}
int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			G[i].clear();
			for(int j=1;j<=n;j++)
				mp[i][j]=0;
		}
		for(int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);
			G[u].push_back(v);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				vis[j]=0;
			dfs(i);
			for(int j=1;j<=n;j++)
				mp[i][j]=vis[j];
		}
		int ans=1;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(i!=j){
			ans&=(mp[i][j]|mp[j][i]);
		}
		puts(ans?"I love you my love and our love save us!":"Light my fire!");
	}
	return 0;
}

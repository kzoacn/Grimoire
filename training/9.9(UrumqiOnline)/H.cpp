#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+4;
int dp[maxn];
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
int n,m,in[maxn];

void dfs(int u){
	if(dp[u])return ;
	dp[u]=0;
	for(auto e:G[u]){
		dfs(e.v);
		dp[u]=max(dp[u],dp[e.v]+e.w);
	}
	return ;
}

int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++){
			G[i].clear();
			in[i]=0;
			dp[i]=0;
		}
		while(m--){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			G[u].push_back((edge){u,v,w});
			in[v]++;
		}
		for(int i=1;i<=n;i++)if(!in[i])
			G[0].push_back((edge){0,i,0});
		dfs(0);
		printf("%d\n",dp[0]);
	}
	return 0;
}

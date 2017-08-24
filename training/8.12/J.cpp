#include<bits/stdc++.h>
using namespace std;
const int maxn=555;
vector<int>G[maxn];
int fa[maxn];
int deg[maxn];
int n,k;
int match[maxn];
int flag=0;
void dfs(int u){
	int cnt=0;
	for(auto v:G[u]){
		dfs(v);
		if(!match[v]){
			cnt++;
		}
	}
	if(cnt>1)flag=0;
	if(cnt==1)match[u]=1;
}
void solve(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		deg[i]=0;
		match[i]=0;
		G[i].clear();
	}
	for(int i=2;i<=n;i++){
		scanf("%d",&fa[i]);
		G[fa[i]].push_back(i);
		deg[fa[i]]++;
	}
	flag=1;
	dfs(1);
	
	puts((flag&&k>=n/2-1&&n%2==0)?"Bob":"Alice");
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}

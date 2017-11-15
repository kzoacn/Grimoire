#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;

vector<int>G[maxn];
int siz[maxn],fa[maxn],son[maxn],top[maxn];
int n,len[maxn];
void dfs(int u){
	siz[u]=1;
	for(auto v:G[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	} 
}
void build(int u,int tp){
	top[u]=tp;
	len[top[u]]++;
	if(son[u])build(son[u],tp);
	for(auto v:G[u]){
		if(v==fa[u]||v==son[u])continue;
		build(v,v);
	}
}

pair<int,int>ans[maxn];
int cur[23];
void solve(int u,int y){
	if(top[u]==u){
		int v=u;
		while(v){
			ans[v]=make_pair(++cur[y],y);
			v=son[v];
		}
	}
	for(auto v:G[u]){
		if(v!=son[u]&&v!=fa[u]){
			solve(v,y+1);
		}
	}
	if(son[u])
		solve(son[u],y);
	
}


int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		int u,v;
		u=i;
		
		if(i<=1000)
			v=i-1;
		else
			v=rand()%(i-1)+1;
		
//		v=i-1;
//		v=rand()%min(10,i-1)+1;
//		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
		if(i>1000)
			cerr<<u<<" "<<v<<endl;
	}
	dfs(1);
	build(1,1);
	
	solve(1,1);
	for(int i=1;i<=n;i++){
		if(i>1000)
		printf("%d %d\n",ans[i].first,ans[i].second);
		assert(ans[i].first<=int(1e6));
		assert(ans[i].second<=20);
	}
	return 0;
}

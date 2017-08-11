#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=5e4+4;
int n,m;
struct edge{
	int u,v;
	LL w;
	edge(){}
	edge(int _u,int _v,LL _w):u(_u),v(_v),w(_w){}
};
vector<edge>G[maxn];
LL base[66];
bool insert(LL x){
	for(int i=60;i>=0;i--){
		if(x>>i&1){
			if(!base[i]){
				base[i]=x;
				return true;
			}else x^=base[i];
		}
	}
	return false;
}
int vis[maxn];
LL d[maxn];
void dfs(int u){
	vis[u]=1;
	for(auto e:G[u]){
		if(!vis[e.v]){
			d[e.v]=(d[u]^e.w);
			dfs(e.v);
		}else{
			LL we=(d[e.v]^e.w^d[e.u]);
			insert(we);
		}
	}
}
LL solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		G[i].clear();
		vis[i]=0;
		d[i]=0;
	}
	memset(base,0,sizeof base);
	for(int i=1;i<=m;i++){
		int u,v;LL w;scanf("%d%d%lld",&u,&v,&w);
		G[u].push_back(edge(u,v,w));
		G[v].push_back(edge(v,u,w));
	}
	dfs(1);
	LL ans=0;
	for(int i=60;i>=0;i--){
		ans=max(ans,ans^base[i]);
	}
	return ans;
}

int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %lld\n",t,solve());
	}
	return 0;
}

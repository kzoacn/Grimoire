#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
int n,fa[maxn],faw[maxn];
LL d[maxn];
void bfs(int s){
	static int vis[maxn];
	for(int i=1;i<=n;i++)vis[i]=0;
	queue<int>q;q.push(s);vis[s]=1;fa[s]=0;faw[s]=0;d[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto e:G[u]){
			if(!vis[e.v]){
				vis[e.v]=1;
				fa[e.v]=u;
				faw[e.v]=e.w;
				d[e.v]=d[u]+e.w;
				q.push(e.v);
			}
		}
	}
}

int root=0;
int siz[maxn],f[maxn];
void dfs(int u){
	siz[u]=1;
	f[u]=0;
	for(auto e:G[u]){
		if(e.v==fa[u])continue;
		fa[e.v]=u;
		dfs(e.v);
		siz[u]+=siz[e.v];
		f[u]=max(f[u],siz[e.v]);
	}
	f[u]=max(f[u],n-siz[u]);
	if(f[u]<f[root])
		root=u;
}

LL solve(){
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)G[i].clear();
	
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});
	}
	for(int i=1;i<=n;i++)fa[i]=0;
	f[0]=n+1;
	root=0;
	dfs(1);
//	cerr<<root<<endl;
	bfs(root);
//	cerr<<root<<endl;
	LL ans=accumulate(d+1,d+1+n,0LL);
//	for(int i=1;i<=n;i++)
//		cerr<<d[i]<<" ";
//	cerr<<endl;
	return ans*2;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %lld\n",t,solve());
	}
	return 0;
}

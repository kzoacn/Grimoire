#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
struct edge{
	int u,v;
	char w;
};
vector<edge>G[maxn];
int f[maxn],g[maxn];
int n,m;
char s[maxn];
int fa[maxn];
int mxf[maxn],mxg[maxn];
void dfs(int u){
	mxf[u]=mxg[u]=u;
	for(auto e:G[u]){
		if(e.v==fa[u])continue;
		fa[e.v]=u;
		dfs(e.v);
	}
	for(auto e:G[u]){
		if(e.v==fa[u])continue;
		//cerr<<u<<" -> "<<e.v<<endl;
		if(g[u]+f[e.v]+(s[f[e.v]+1]==e.w)>=m){
			printf("%d %d\n",mxf[e.v],mxg[u]);
			exit(0);
		}
		
		if(f[u]+g[e.v]+(s[m-g[e.v]]==e.w)>=m){
			printf("%d %d\n",mxf[u],mxg[e.v]);
			exit(0);
		}
	
		if(f[e.v]+(s[f[e.v]+1]==e.w)>f[u]){
			f[u]=f[e.v]+(s[f[e.v]+1]==e.w);
			mxf[u]=mxf[e.v];
		}
		if(g[e.v]+(s[m-g[e.v]]==e.w)>g[u]){
			g[u]=g[e.v]+(s[m-g[e.v]]==e.w);
			mxg[u]=mxg[e.v];
		}
	}
	
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v;char s[4];
		scanf("%d%d%s",&u,&v,s);
		G[u].push_back((edge){u,v,s[0]});
		G[v].push_back((edge){v,u,s[0]});
	}
	scanf("%s",s+1);
	dfs(1);
	
	/*for(int i=1;i<=n;++i){
		cerr<<f[i]<<" ";
	}cerr<<endl;
	for(int i=1;i<=n;++i){
		cerr<<g[i]<<" ";
	}cerr<<endl;
	*/
	puts("-1 -1");
	return 0;
}

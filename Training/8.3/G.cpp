#include<bits/stdc++.h>
using namespace std;
const int N=1e4+4;
const int M=2e5+5;
struct Graph{
	int e,nxt[M],v[M],adj[N],n;
	bool base;
	__inline void init(bool _base,int _n=0){
		assert(n<N);
		n=_n;base=_base;
		e=0;memset(adj+base,-1,sizeof(*adj)*n);
	}
	__inline int new_node(){
		adj[n+base]=-1;
		return n++ + base;
	}
	__inline void ins(int u0,int v0){
		v[e]=v0;nxt[e]=adj[u0];adj[u0]=e++;
	}
	__inline void bi_ins(int u0,int v0){
		ins(u0,v0);
		ins(v0,u0);
	}
};
struct BCC{
	Graph *g,forest;
	int dfn[N],low[N],stk[N],tot[N],belong[N],vis[N],top,dfs_clock;
	pair<int,int>ori[M];
	bool is_bridge[M];
	__inline void init(Graph *raw_graph){
		g=raw_graph;
		memset(is_bridge,false,sizeof(*is_bridge)*g->e);
		memset(vis+g->base,0,sizeof(*vis)*g->n);
	}
	void tarjan(int u,int from){
		dfn[u]=low[u]=++dfs_clock;vis[u]=1;stk[++top]=u;
		for(int p=g->adj[u];~p;p=g->nxt[p]){
			if((p^1)==from)continue;
			int v=g->v[p];
			if(vis[v]){
				if(vis[v]==1)low[u]=min(low[u],dfn[v]);
			}else{
				tarjan(v,p);
				low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u])is_bridge[p/2]=true;
			}
		}
		if(dfn[u]!=low[u])return ;
		tot[forest.new_node()]=0;
		do{
			belong[stk[top]]=forest.n;
			vis[stk[top]]=2;
			tot[forest.n]++;
			--top;
		}while(stk[top+1]!=u);
	}
	
	int cnt=0;
	int col[N];
	void dfs(int u){
		col[u]=1;cnt++;
		for(int p=forest.adj[u];~p;p=forest.nxt[p]){
			int v=forest.v[p];
			if(!col[v]){
				dfs(v);
			}
		}
	}
	
	int solve(){
		forest.init(g->base);
		int n=g->n;
		for(int i=0;i<n;i++){
			if(!vis[i+g->base]){
				top=dfs_clock=0;
				tarjan(i+g->base,-1);
			}
		}
		for(int i=0;i<g->e/2;i++){
			if(is_bridge[i]){
				forest.bi_ins(belong[g->v[i*2]],belong[g->v[i*2+1]]);
			}
		}
		
		for(int i=1;i<=forest.n;i++){
			if(tot[i]>1){
				col[i]=1;
			}else col[i]=0;
		}
		
		int ans=0;
		for(int i=1;i<=forest.n;i++){
			cnt=0;
			if(col[i]==0)		
				dfs(i);	
			ans+=cnt*(cnt-1)/2;
		}
		
		return ans;
	}
	
}bcc;
Graph g;
int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		int n,m;scanf("%d%d",&n,&m);
		g.init(1,n);
		for(int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);
			g.bi_ins(u,v);
		}
		bcc.init(&g);
		printf("Case #%d: %d\n",t,bcc.solve());
	}
	return 0;
}

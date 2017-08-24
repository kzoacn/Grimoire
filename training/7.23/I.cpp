#include<bits/stdc++.h>
using namespace std;

const int maxn=5e4+5;


int n,m,r;
int parent[maxn],label[maxn],cnt,rel[maxn];
vector<int>edge[maxn],succ[maxn],pred[maxn];
int semi[maxn],idom[maxn],ancestor[maxn],best[maxn];
vector<int>bucket[maxn];
int reldom[maxn];

void dfs(int u){
	label[u]=++cnt;rel[cnt]=u;
	for(auto v:edge[u]){
		if(v==parent[u]||label[v]!=-1)continue;
		parent[v]=u;
		dfs(v);
	}
}
void link(int v,int w){
	ancestor[w]=v;
}
void compress(int v){
	int a=ancestor[v];
	if(ancestor[a]==0)return ;
	compress(a);
	if(semi[best[v]]>semi[best[a]])best[v]=best[a];
	ancestor[v]=ancestor[a];
}
int eval(int v){
	if(ancestor[v]==0)return v;
	compress(v);return best[v];
}
void dominator(){
	cnt=0;
	for(int i=1;i<=n;i++)succ[i].clear(),pred[i].clear();
	for(int i=1;i<=n;i++)label[i]=-1;
	parent[r]=-1;dfs(r);
	for(int u=1;u<=n;u++){
		for(auto v:edge[u]){
			if(label[u]!=-1&&label[v]!=-1){
				succ[label[u]].push_back(label[v]);
				pred[label[v]].push_back(label[u]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		semi[i]=best[i]=i;
		idom[i]=ancestor[i]=0;
		bucket[i].clear();
	}
	for(int w=cnt;w>=2;w--){
		int p=label[parent[rel[w]]];
		for(auto v:pred[w]){
			int u=eval(v);
			if(semi[w]>semi[u])
				semi[w]=semi[u];
		}
		bucket[semi[w]].push_back(w);
		link(p,w);
		for(auto v:bucket[p]){
			int u=eval(v);
			idom[v]=(semi[u]<p?u:p);
		}
		bucket[p].clear();
	}
	for(int w=2;w<=cnt;w++){
		if(idom[w]!=semi[w])
			idom[w]=idom[idom[w]];
	}
	idom[1]=0;
	for(int i=1;i<=n;i++)reldom[i]=-1;
	for(int i=2;i<=cnt;i++){
		int u=rel[idom[i]],v=rel[i];
		reldom[v]=u;
	}
}
long long sum[maxn];
void make(int u){
	if(sum[u])return ;
	sum[u]=u;
	if(reldom[u]!=-1){
		make(reldom[u]);
		sum[u]+=sum[reldom[u]];
	}
}
int main(){
	while(scanf("%d%d",&n,&m)==2){
		r=n;
		for(int i=1;i<=n;i++)
			edge[i].clear();
		for(int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		dominator();
		for(int i=1;i<=n;i++)sum[i]=0;
		for(int i=1;i<=n;i++)
			make(i);
		for(int i=1;i<=n;i++)
			printf("%lld%c",sum[i]," \n"[i==n]);
	}	
	return 0;
}

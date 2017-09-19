#include<bits/stdc++.h>
using namespace std;

#define __advance __attribute__((optimize("O3")))

const int maxn=1e5+5;


vector<int>G[maxn];
struct edge{int u,v;bool tree;};
int e;
edge E[maxn];
int n,m,q;

struct BIT{
	int d[maxn];
	__advance void init(int n){
		for(int i=1;i<=n;i++)
			d[i]=0;
	}
	__advance int get(int x){
		int ans=0;
		while(x){
			ans+=d[x];
			x-=x&-x;
		}
		return ans;
	}
	__advance void add(int x,int y){
		assert(x);
		while(x<maxn){	
			d[x]+=y;
			x+=x&-x;
		}
	}
	void add(int l,int r,int y){
		add(l,y);
		add(r+1,-y);
	}
}bit;

struct UFSet{
	int fa[maxn];
	__advance void init(int n){
		for(int i=1;i<=n;i++)fa[i]=i;
	}
	__advance int find(int x){
		return fa[x]==x ? x :fa[x]=find(fa[x]);
	}
	__advance void merge(int x,int y){
		fa[find(x)]=find(y);
	}
	__advance bool conn(int u,int v){return find(u)==find(v);}
}S;
int fa[maxn][20],dep[maxn],lef[maxn],rig[maxn],z;

__advance void dfs(int u){
	lef[u]=++z;
	for(int i=1;i<20;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]){
		if(v==fa[u][0])continue;
		fa[v][0]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
	rig[u]=z;
}
__advance int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<20;i++)if(d>>i&1){
		u=fa[u][i];
	}
	
	if(u==v)return u;
	for(int i=19;i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}

__advance void Jump(int u,int LCA){
	for(u=S.find(u);dep[u]>dep[LCA];u=S.find(u)){
		bit.add(lef[u],rig[u],-1);
		S.merge(u,fa[u][0]);	
	}
}

__advance void Add(int u,int v){
	int LCA=lca(u,v);
	//cerr<<"LCA "<<LCA<<endl;
	Jump(u,LCA);
	Jump(v,LCA);		

}
namespace Reader{
	const int L=(1<<20)+5;
	char buffer[L],*S,*T;
	__advance __inline bool getchar(char &ch){
		if(S==T){
			T=(S=buffer)+fread(buffer,1,L,stdin);
			if(S==T){
				ch=EOF;
				return false;
			}
		}
		ch=*S++;
		return true;
	}
	__advance __inline bool getint(int &x){
		char ch;
		for(;getchar(ch)&&!isdigit(ch););
		if(ch==EOF)return false;
		x=ch-'0';
		for(;getchar(ch),isdigit(ch);)
			x=x*10+ch-'0';
		return true;
	}
}

__advance void solve(){
	//scanf("%d%d",&n,&m);
	Reader::getint(n);
	Reader::getint(m);
	for(int i=1;i<=n;i++){
		G[i].clear();
	}
	for(int i=0;i<m;i++){
		Reader::getint(E[i].u);
		Reader::getint(E[i].v);
		
		//scanf("%d%d",&E[i].u,&E[i].v);
		E[i].tree=0;
	}
	S.init(n);bit.init(n);
	for(int i=0;i<m;i++){
		if(!S.conn(E[i].u,E[i].v)){
			S.merge(E[i].u,E[i].v);
			E[i].tree=1;
			G[E[i].u].push_back(E[i].v);
			G[E[i].v].push_back(E[i].u);
		}
	}
	
	z=0;
	dfs(1);

	for(int i=1;i<=n;i++)
		bit.add(lef[i],lef[i],dep[i]);

	S.init(n);	
	for(int i=0;i<m;i++){
		if(!E[i].tree){
			Add(E[i].u,E[i].v);
		}
	}
	
	
	Reader::getint(q);
	while(q--){
		int ty,u,v;
		Reader::getint(ty);
		Reader::getint(u);
		Reader::getint(v);
		//scanf("%d%d%d",&ty,&u,&v);
		//cerr<<ty<<" "<<u<<" "<<v<<endl;
		if(ty==1){
			Add(u,v);
		}else{
			int ans=0;
			ans=bit.get(lef[u])+bit.get(lef[v])-2*bit.get(lef[lca(u,v)]);
			printf("%d\n",ans);
		}
	}
}

__advance int main(){
	int T;
	Reader::getint(T);
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		solve();
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
typedef long long LL;
const LL inf=1LL<<61;
typedef pair<LL,int> pii;
namespace SP{
	
	LL d[int(5e5+300)];
	int n;
	struct edge{
		int u,v,w;
	};
	vector<edge>G[int(5e5+300)];
	void add(int u,int v,int w){
		G[u].push_back({u,v,w});
		cerr<<u<<"->"<<v<<" "<<w<<endl;
	}
	void clear(){
		for(int i=1;i<=n;i++)
			G[i].clear();
	}
	void dijk(int s){
//	cerr<<"s="<<s<<endl;
		priority_queue<pii,vector<pii>,greater<pii> >q;
		for(int i=0;i<=n;i++)d[i]=inf;
		q.push({d[s]=0,s});
		while(!q.empty()){
			int u=q.top().second;
			if(d[u]!=q.top().first){
				q.pop();
				continue;
			}
			q.pop();
			for(auto e:G[u]){
				if(d[e.v]>d[u]+e.w){
					d[e.v]=d[u]+e.w;
					q.push({d[e.v],e.v});
				}
			}
			
		}
	}

}
int n,m;
int pt[maxn*2],sz;
int id(int l,int r){
	return l+r|l!=r;
}
void get(int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r){
		pt[++sz]=id(l,r);
		return;
	}
	int mid=(l+r)>>1;
	if(l0<=mid)get(l,mid,l0,r0);
	if(r0>mid)get(mid+1,r,l0,r0);
}
int dep[maxn],son[maxn],siz[maxn],z,mp[maxn],top[maxn],fa[maxn];
vector<int>G[maxn];
void dfs(int u){
	siz[u]=1;
	for(auto v:G[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])
			son[u]=v;
	}
}
void build(int u,int tp){
	mp[u]=++z;top[u]=tp;
	if(son[u])build(son[u],tp);
	for(auto v:G[u]){
		if(v==son[u]||v==fa[u])continue;
		build(v,v);
	}
}
int shift;
void buildT(int l,int r){
	if(l==r){
		SP::add(id(l,r)+shift,id(l,r),0);
		return;
	}
	int mid=(l+r)>>1;
	SP::add(id(l,mid),id(l,r),0);
	SP::add(id(mid+1,r),id(l,r),0);
	
	SP::add(id(l,r)+shift,id(l,mid)+shift,0);
	SP::add(id(l,r)+shift,id(mid+1,r)+shift,0);
	
	buildT(l,mid);
	buildT(mid+1,r);
}
void get(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		get(1,n,mp[top[u]],mp[u]);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])
		swap(u,v);
	get(1,n,mp[v],mp[u]);
}
void solve(){
	scanf("%d%d",&n,&m);
	shift=n*2+4;
	
	SP::n=n+n+1+shift+m;
	SP::clear();
	for(int i=1;i<=n;i++){
		G[i].clear();
		dep[i]=0;
		son[i]=0;
		siz[i]=0;
		z=0;
		mp[i]=0;
		top[i]=0;
		fa[i]=0;
	}
	//TODO clear	
	//array size!
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	build(1,1);
	buildT(1,n);
	int mxnode=shift+n+n+1;
	for(int _=1;_<=m;_++){
		sz=0;
		int a,b,c,d,w;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&w);
		get(a,b);
		get(c,d);
		++mxnode;
		for(int i=1;i<=sz;i++){
			SP::add(pt[i],mxnode,0);
		}
		for(int i=1;i<=sz;i++){
			SP::add(mxnode,pt[i]+shift,w);
		}
	}
	SP::dijk(id(1,1));
	int cnt=0;
	LL cost=0;
//	cerr<<SP::d[6]<<endl;
	for(int i=1;i<=n;i++)
		if(SP::d[id(mp[i],mp[i])]!=inf){
			cnt++;
			cost+=SP::d[id(mp[i],mp[i])];
			cerr<<i<<" "<<SP::d[id(mp[i],mp[i])]<<endl;
		}
	printf("%d %lld\n",cnt,cost);
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++)
		solve();
	return 0;
}

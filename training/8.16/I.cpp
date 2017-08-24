#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;

vector<int>G[maxn];
int n,m,q;

int fa[maxn];
struct UF{
	int fa[maxn];
	void init(int n){
		for(int i=1;i<=n;i++)fa[i]=i;
	}
	int find(int x){
		return fa[x]==x ? x :fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		fa[find(x)]=find(y);
	}
	bool conn(int x,int y){
		return find(x)==find(y);
	}
}F;
int siz[maxn],son[maxn],z,mp[maxn],top[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1;
	son[u]=0;
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
void HLD(int u,int tp){
	mp[u]=++z;top[u]=tp;
	if(son[u])HLD(son[u],tp);
	for(auto v:G[u]){
		if(v==fa[u]||v==son[u])continue;
		HLD(v,v);
	}
}

struct SGT{
	struct node{
		int all,sum;
	}t[maxn*2];
	inline int id(int l,int r){
		return (l+r)|(l!=r);
	}
	void make(int l,int r,int val){
		t[id(l,r)].all=val;
		t[id(l,r)].sum=val*(r-l+1);
	}
	void pd(int l,int r){
		int x=id(l,r),mid=(l+r)>>1;
		
		//int ls=id(l,mid),rs=id(mid+1,r);
		if(t[x].all!=-1){
			make(l,mid,t[x].all);
			make(mid+1,r,t[x].all);
			t[x].all=-1;
		}
	}
	void rz(int l,int r){
		int x=id(l,r),mid=(l+r)>>1;
		int ls=id(l,mid),rs=id(mid+1,r);
		t[x].sum=t[ls].sum+t[rs].sum;
	}
	void C(int l,int r,int l0,int r0,int val){
		if(l0<=l&&r0>=r){
			make(l,r,val);
			return ;
		}
		pd(l,r);
		int mid=(l+r)>>1;
		if(l0<=mid)C(l,mid,l0,r0,val);
		if(r0>mid)C(mid+1,r,l0,r0,val);
		rz(l,r);
	}
	
	int Q(int l,int r,int l0,int r0){
		if(l0<=l&&r0>=r)
			return t[id(l,r)].sum;
		pd(l,r);
		int mid=(l+r)>>1,ans=0;
		if(l0<=mid)ans+=Q(l,mid,l0,r0);
		if(r0>mid)ans+=Q(mid+1,r,l0,r0);
		return ans;
	}
	void build(int l,int r){
		t[id(l,r)].all=-1;
		t[id(l,r)].sum=0;
		if(l==r)
			return ;
		int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
	}
	
}T;
multiset<pair<int,int> >S;
pair<int,int> pack(int x,int y){
	if(x>y)swap(x,y);
	return make_pair(x,y);
}
int qty[maxn],qa[maxn],qb[maxn];
pair<int,int>qe[maxn];
pair<int,int>new_e[maxn];


void C(int u,int v,int val){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.C(1,n,mp[top[u]],mp[u],val);
		u=fa[top[u]];
	}
	if(mp[u]>mp[v])swap(u,v);
	if(mp[u]<mp[v])
		T.C(1,n,mp[u]+1,mp[v],val);	
}
int Q(int u,int v){
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=T.Q(1,n,mp[top[u]],mp[u]);
		u=fa[top[u]];
	}
	if(mp[u]>mp[v])swap(u,v);
	if(mp[u]<mp[v])
		ans+=T.Q(1,n,mp[u]+1,mp[v]);
	return ans;
}

void add(int u,int v){
	if(F.conn(u,v)){
		C(u,v,0);
	}else{
		C(u,v,1);
		F.merge(u,v);
	}
}

void solve(){
	scanf("%d%d%d",&n,&m,&q);
	//TODO clear!!!
	z=0;S.clear();
	for(int i=1;i<=n;i++){
		G[i].clear();
		
	}
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		S.insert(pack(u,v));
	}
	int e=0;
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&qty[i],&qa[i],&qb[i]);
		if(qty[i]==1){
			qe[++e]=pack(qa[i],qb[i]);
			S.erase(S.find(pack(qa[i],qb[i])));
		}
	}
	reverse(qe+1,qe+1+e);
	F.init(n);
	int sz=0;
	for(auto e:S)
		new_e[++sz]=e;
	for(int i=1;i<=e;i++)
		new_e[++sz]=qe[i];
	
	for(int i=1;i<=sz;i++){
		int u=new_e[i].first;
		int v=new_e[i].second;
		if(!F.conn(u,v)){
			F.merge(u,v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
	}	
	dfs(1);
	HLD(1,1);
	T.build(1,n);
	
	F.init(n);	
	for(auto e:S)
		add(e.first,e.second);
	static int ans[maxn];
	int ansz=0,edgesz=S.size();
	for(int i=q;i>=1;i--){
		if(qty[i]==1){
			add(qa[i],qb[i]);
			edgesz++;
		}else{
			int u=qa[i],v=qb[i];
			if(F.conn(u,v)){
				if(u!=v)
					ans[++ansz]=Q(u,v);
				else
					ans[++ansz]=0;
			}else{
				ans[++ansz]=edgesz;
			}
		}
	}
	for(int i=ansz;i>=1;i--)
		printf("%d\n",ans[i]);
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		solve();
	}
	return 0;
}

/*
Case #1:
0
0
0
0
2
3
3
3
2
3
4

*/

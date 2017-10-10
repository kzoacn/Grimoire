#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
const int maxn=2e5+5;
int id(int l,int r){return l+r|l!=r;}

struct Info{
	int ls,ss,rs,sum;
	int len;
	
	Info flip(){
		Info c=*this;
		swap(c.ls,c.rs);
		return c;
	}
	
	void print(){
		printf("ls=%d ss=%d rs=%d len=%d sum=%d\n",ls,ss,rs,len,sum);
	}
};
Info operator+(Info a,Info b){

	if(a.len==0)return b;
	if(b.len==0)return a;

	Info c;
	c.ls=max(a.ls,a.sum+b.ls);
	c.rs=max(b.rs,b.sum+a.rs);
	c.ss=max(a.ss,b.ss);
	c.ss=max(c.ss,a.rs+b.ls);
	c.len=a.len+b.len;
	c.sum=a.sum+b.sum;
	return c;
}
Info operator+(Info a,int b){
	Info c;
	if(b>0){
		c.ls=c.rs=c.ss=c.sum=b*a.len;
		c.len=a.len;
	}else{
		c.ls=c.rs=c.ss=b;
		c.sum=a.len*b;
		c.len=a.len;
	}
	return c;
}

struct node{
	int laz;
	Info info;
}t[maxn*2];

vector<int>G[maxn];
int z,mp[maxn],rmp[maxn],top[maxn],dep[maxn],son[maxn],siz[maxn],fa[maxn],a[maxn];
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	}	
}
void HLD(int u,int tp){
	mp[u]=++z;rmp[z]=u;
	top[u]=tp;
	if(son[u])HLD(son[u],tp);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v!=fa[u]&&v!=son[u])
			HLD(v,v);
	}
}
void build(int l,int r){
	int x=id(l,r);
	t[x].laz=inf;
	if(l==r){
		t[x].info.ls=t[x].info.ss=t[x].info.rs=t[x].info.sum=a[rmp[l]];
		t[x].info.len=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid);
	build(mid+1,r);
	t[x].info=t[id(l,mid)].info+t[id(mid+1,r)].info;
	//cerr<<l<<" "<<r<<endl;
	//t[x].info.print();
}
void pd(int l,int r){
	int x=id(l,r),mid=(l+r)>>1;
	int ls=id(l,mid),rs=id(mid+1,r);
	if(t[x].laz!=inf){
		t[ls].info=t[ls].info+t[x].laz;
		t[ls].laz=t[x].laz;
		t[rs].info=t[rs].info+t[x].laz;
		t[rs].laz=t[x].laz;
		t[x].laz=inf;	
	}
}
Info Q(int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r)
		return t[id(l,r)].info;
	pd(l,r);
	int mid=(l+r)>>1;
	if(l0<=mid&&r0>mid)
		return Q(l,mid,l0,r0)+Q(mid+1,r,l0,r0);
	if(l0<=mid)
		return Q(l,mid,l0,r0);
	if(r0>mid)
		return Q(mid+1,r,l0,r0);
}

void C(int l,int r,int l0,int r0,int y){
	int x=id(l,r);
	if(l0<=l&&r0>=r){
		t[x].info=t[x].info+y;
		t[x].laz=y;
		return ;
	}
	pd(l,r);
	int mid=(l+r)>>1;
	if(l0<=mid)C(l,mid,l0,r0,y);
	if(r0>mid)C(mid+1,r,l0,r0,y);
	t[x].info=t[id(l,mid)].info+t[id(mid+1,r)].info;
}
int n,q;

int Q(int u,int v){
	Info pref,suf;
	pref.len=suf.len=0;
	
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			pref=pref+Q(1,n,mp[top[u]],mp[u]).flip();
			//cerr<<u<<" "<<top[u]<<endl;
			u=fa[top[u]];
		}else{
			suf=Q(1,n,mp[top[v]],mp[v])+suf;
			//cerr<<top[v]<<" "<<v<<endl;
			v=fa[top[v]];
		}	
	}
	Info ans;
	
	//pref.print();
	//suf.print();
	//cerr<<u<<" "<<v<<endl;
	//cerr<<mp[v]<<" "<<mp[u]<<endl;
	//Q(1,n,mp[v],mp[u]).print();
	if(mp[u]<=mp[v]){
		ans=pref+Q(1,n,mp[u],mp[v])+suf;
	}else{
		ans=pref+Q(1,n,mp[v],mp[u]).flip()+suf;
	}
	return ans.ss;
	
}
void C(int u,int v,int y){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			C(1,n,mp[top[u]],mp[u],y);
			u=fa[top[u]];
		}else{
			C(1,n,mp[top[v]],mp[v],y);
			v=fa[top[v]];
		}	
	}
	if(mp[u]<=mp[v]){
		C(1,n,mp[u],mp[v],y);
	}else{
		C(1,n,mp[v],mp[u],y);
	}	
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	HLD(1,1);
	build(1,n);
	
	//cerr<<Q(1,n,1,3).len<<endl;
	
	while(q--){
		int ty,a,b,c;scanf("%d%d%d%d",&ty,&a,&b,&c);
		if(ty==1){
			C(a,b,c);
		}else{
			printf("%d\n",Q(a,b));
		}
	}
	return 0;
}

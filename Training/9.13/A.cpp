#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;


const int maxnp=1768928+122;
int c[maxnp][2];
int siz[maxnp];
LL sum[maxnp],ans[maxnp],anss[maxn];
int tot;
int a[maxn],root[maxn];
int n;
pair<int,int> b[maxn];
int son[maxn][3];
char sz[maxn];
int newnode(){
	++tot;
	
	c[tot][0]=c[tot][1]=0;
	siz[tot]=0;
	sum[tot]=ans[tot]=0;
	
	return tot;
}

void rz(int x){
#define ls c[x][0]
#define rs c[x][1]
	siz[x]=siz[ls]+siz[rs];
	sum[x]=sum[ls]+sum[rs];
	ans[x]=ans[ls]+ans[rs]+siz[rs]*sum[ls];
	
#undef ls
#undef rs
}

int insert(int l,int r,int ps){
	int x=newnode();
	if(l==r){
		siz[x]=1;
		sum[x]=b[ps].first;
		ans[x]=b[ps].first;
		return x;
	}
	int mid=(l+r)>>1;
	if(ps<=mid)
		c[x][0]=insert(l,mid,ps);
	else
		c[x][1]=insert(mid+1,r,ps);
	rz(x);
	return x;
}

int merge(int rt1,int rt2,int l,int r){//rt1 <- rt2
	if(!rt1||!rt2)
		return rt1|rt2;
	if(l==r){
		return rt1;
	}
	int mid=(l+r)>>1;
	c[rt1][0]=merge(c[rt1][0],c[rt2][0],l,mid);
	c[rt1][1]=merge(c[rt1][1],c[rt2][1],mid+1,r);
	rz(rt1);
	return rt1;
}
int fa[maxn];
void dfs(int u){
	for(int i=0;i<sz[u];i++){
		int v=son[u][i];
		if(v==fa[u])continue;
		fa[v]=u;
		dfs(v);
		merge(root[u],root[v],1,n);
	}
	anss[u]=ans[root[u]];
}


void add_edge(int u,int v){
	son[u][sz[u]++]=v;
}

void solve(){
	tot=0;
	scanf("%d",&n);
	//clear
	for(int i=1;i<=n;i++){
		//G[i].clear();
		sz[i]=0;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=make_pair(a[i],i);
	}
	sort(b+1,b+1+n);
	
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	
	for(int i=1;i<=n;i++)
		a[b[i].second]=i;
	for(int i=1;i<=n;i++){
		root[i]=insert(1,n,a[i]);
	}
	//cerr<<tot<<endl;
	dfs(1);
	for(int i=1;i<=n;i++)
		printf("%lld ",anss[i]);
	puts("");
}


int main(){
	
	int T;scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}

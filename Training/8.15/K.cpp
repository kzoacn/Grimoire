#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const int inf=1e9;
int siz[maxn],f[maxn],dep[maxn],cant[maxn],root,All;
vector<int>G[maxn];
int ans=0;
int D;
int a[maxn],n;
struct FenwickTree1{
	int d[maxn];
	int vis[maxn];
	int T;
	void clear(){
		T++;
	}
	FenwickTree1(){T=1;}
	
	void add(int x,int y){
		while(x>0){
			if(vis[x]!=T){
				vis[x]=T;
				d[x]=-inf;
			}
			d[x]=max(d[x],y);
			x-=x&-x;
		}
	}
	int get(int x){
		x=max(x,1);
		int ans=-inf;
		while(x<maxn){
			if(vis[x]!=T){
				vis[x]=T;
				d[x]=-inf;
			}
			ans=max(d[x],ans);
			x+=x&-x;
		}
		return ans;
	}	
}decT;

struct FenwickTree2{
	int d[maxn];
	int vis[maxn];
	int T;
	void clear(){
		T++;
	}
	FenwickTree2(){T=1;}
	
	void add(int x,int y){
		while(x<maxn){
			if(vis[x]!=T){
				vis[x]=T;
				d[x]=-inf;
			}
			d[x]=max(d[x],y);
			x+=x&-x;
		}
	}
	int get(int x){
		x=min(x,maxn-1);
		int ans=-inf;
		while(x>0){
			if(vis[x]!=T){
				vis[x]=T;
				d[x]=-inf;
			}
			ans=max(d[x],ans);
			x-=x&-x;
		}
		return ans;
	}	
}incT;

void makert(int u,int fa){
	siz[u]=1;f[u]=0;
	for(auto v:G[u]){
		if(v!=fa&&!cant[v]){
			dep[v]=dep[u]+1;
			makert(v,u);
			siz[u]+=siz[v];
			f[u]=max(f[u],siz[v]);
		}
	}
	f[u]=max(f[u],All-f[u]);
	if(f[root]>f[u])
		root=u;
}

int sz1=0,sz2=0;
pair<int,int> indata[maxn],dedata[maxn];

void dfs(int u,int fa,int in,int de){
	if(in!=-1)
		indata[++sz1]=make_pair(in,dep[u]);
	if(de!=-1)
		dedata[++sz2]=make_pair(de,dep[u]);
	for(auto v:G[u]){
		if(cant[v]||v==fa)continue;
		int tin=(in==-1?-1:(a[v]>=in?a[v]:-1));
		int tde=(de==-1?-1:(a[v]<=de?a[v]:-1));
		dep[v]=dep[u]+1;
		dfs(v,u,tin,tde);
	}
}

void calc(int u){
	incT.clear();
	decT.clear();
	incT.add(a[u],0);
	decT.add(a[u],0);
	
	for(auto v:G[u]){
		if(cant[v])continue;
		dep[v]=1;
		
		sz1=0;sz2=0;
		dfs(v,u,a[u]<=a[v]?a[v]:-1,a[u]>=a[v]?a[v]:-1);
		int res=0;
		for(int i=1;i<=sz1;i++){
			res=max(res,indata[i].second+decT.get(indata[i].first-D));
		}
		for(int i=1;i<=sz2;i++){
			res=max(res,dedata[i].second+incT.get(dedata[i].first+D));
		}
		
		for(int i=1;i<=sz1;i++){
			incT.add(indata[i].first,indata[i].second);
		}
		for(int i=1;i<=sz2;i++){
			decT.add(dedata[i].first,dedata[i].second);
		}
		//cerr<<u<<" "<<v<<" "<<res<<endl;
		ans=max(ans,res);
	}
}
void solve(int u){
	calc(u);cant[u]=1;
	for(auto v:G[u]){
		if(cant[v])continue;
		All=siz[v];
		f[root=0]=n+1;
		makert(v,0);
		solve(root);
	}
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		scanf("%d%d",&n,&D);
		for(int i=1;i<=n;i++){
			//TODO cleear
			G[i].clear();
			cant[i]=0;
		}
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<n;i++){
			int u,v;scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		ans=0;
		All=n;
		f[root=0]=n+1;
		makert(1,1);
		solve(root);
		printf("Case #%d: %d\n",t,ans+1);
	}
	return 0;
}

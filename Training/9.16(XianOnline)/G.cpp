#include<bits/stdc++.h>
using namespace std;
const int maxn=50050;
const int MAGIC=233;
const int BIT=18;

int n,q;
vector<int>G[maxn];
int a[maxn];
int fa[maxn];
int faB[maxn][BIT];
int faM[maxn][MAGIC];
int dp[maxn][MAGIC];
int dep[maxn];
pair<int,int> sta[maxn];
void dfs(int u){
	for(auto v:G[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		faB[v][0]=u;
		faM[v][1]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
}


int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<BIT;i++){
		if(d>>i&1){
			u=faB[u][i];
		}
	}
	if(u==v)return u;
	for(int i=BIT-1;i>=0;i--)if(faB[u][i]!=faB[v][i]){
		u=faB[u][i];
		v=faB[v][i];
	}
	return faB[u][0];
}
int Jump(int u,int k){
	if(k<MAGIC)
		return faM[u][k];
	for(int i=0;i<BIT;i++)if(k>>i&1){
		u=faB[u][i];
	}
	return u;
}

int First(int u,int k,int m){
//cerr<<"Jump "<<u<<" "<<k<<" "<<m<<endl;
	int h=(dep[u]%k-m+k)%k;
	u=Jump(u,h);
	return u;
}

int calc(int u,int LCA,int k,int m){
	int ans=0;
	//cerr<<u<<" "<<LCA<<" "<<k<<" "<<m<<endl;
	u=First(u,k,m);
	
	if(k<MAGIC){
		
			LCA=First(fa[LCA],k,m);
		
		
			//cerr<<u<<" "<<LCA<<endl;
			ans= dp[u][k]^dp[LCA][k];
		
	}else{
		while(dep[u]>=dep[LCA]){
			
			ans^=a[u];
			
			u=Jump(u,k);
		}
	}
	//cerr<<"ans="<<ans<<endl;
	return ans;
}

int Q(int u,int v,int k){
	int LCA=lca(u,v);
	
	int ans=0;
	
	ans=calc(u,LCA,k,dep[u]%k);
	
	ans^=calc(v,LCA,k,(2*dep[LCA]%k-dep[u]%k+k)%k);
	
	if(dep[LCA]%k==dep[u]%k)
		ans^=a[LCA];
	
	return ans;
}


void solve(){
//clear
	for(int i=1;i<=n;i++){
		G[i].clear();
		
	}
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)	
		scanf("%d",&a[i]);
	dep[1]=1;
	dfs(1);
	for(int j=1;j<BIT;j++)
	for(int i=1;i<=n;i++)
		faB[i][j]=faB[faB[i][j-1]][j-1];
	
	for(int i=1;i<=n;i++)
		faM[i][0]=i;
	
	for(int j=2;j<MAGIC;j++)
	for(int i=1;i<=n;i++)
		faM[i][j]=fa[faM[i][j-1]];
	
	
	
	for(int i=1;i<=n;i++)
		sta[i]=make_pair(dep[i],i);
	sort(sta+1,sta+1+n);
	for(int i=1;i<=n;i++){
		int u=sta[i].second;
		for(int j=1;j<MAGIC;j++){
			dp[u][j]=dp[faM[u][j]][j]^a[u];
		}
	}
	
	
	while(q--){
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		//cerr<<u<<" "<<v<<" "<<k<<endl;
		printf("%d\n",Q(u,v,k));
	}
}

int main(){
	while(scanf("%d%d",&n,&q)==2&&n){
		solve();
	}
	return 0;
}

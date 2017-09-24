//20:40 -> 21:30
//id:kzoacn
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const int inf=1e9;
int f[maxn][2];
int g[maxn],sum[maxn];
int n,T,ans[maxn],V[maxn];
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
int fa[maxn],faW[maxn];
void dp(int u){
	sum[u]=0;
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];int v=e.v;
		if(fa[u]==v)continue;
		fa[v]=u;
		faW[v]=e.w;
		dp(v);
		sum[u]+=f[v][1];		
	}
	f[u][0]=sum[u];
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];int v=e.v;
		if(fa[u]==v)continue;
		if(f[v][0]-f[v][1]+sum[u] > f[u][0]){
			f[u][0]=f[v][0]-f[v][1]+sum[u];
			g[u]=v;
		}
	}
	
	f[u][0]+=V[u]-faW[u];
	f[u][1]=sum[u]+V[u]-faW[u]*2;
	if(f[u][1]<0)
		f[u][1]=0;
		
//	f[u][0]+=V[u]-faW[u];
//	printf("u=%d\t%d\t%d\t%d\n",u,f[u][0],f[u][1],g[u]);
}
void recalc(int u,int fa,int faW){
	f[u][0]=sum[u];
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];int v=e.v;
		if(fa==v)continue;
		if(f[v][0]-f[v][1]+sum[u] > f[u][0]){
			f[u][0]=f[v][0]-f[v][1]+sum[u];
			g[u]=v;
		}
	}
	
	f[u][0]+=V[u]-faW;
	f[u][1]=sum[u]+V[u]-faW*2;
	if(f[u][1]<0)
		f[u][1]=0;
}
void dfs(int u){

	ans[u]=f[u][0];
		
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];int v=e.v;
		if(fa[u]==v)continue;
		
		int _fu0=f[u][0],_fu1=f[u][1],_gu=g[u],_fv0=f[v][0],_fv1=f[v][1],_gv=g[v],_su=sum[u],_sv=sum[v];
		
		sum[u]-=f[v][1];
		
		if(g[u]==v){
			recalc(u,v,e.w);
		}else{
			f[u][0]-=f[v][1];
			f[u][0]-=e.w;
			f[u][1]=sum[u]+V[u]-e.w*2;
			if(f[u][1]<0)
				f[u][1]=0;
		}
		
		sum[v]+=f[u][1];
		recalc(v,0,0);
		
		dfs(v);
		
		f[u][0]=_fu0;
		f[u][1]=_fu1;
		g[u]=_gu;
		sum[u]=_su;
		
		f[v][0]=_fv0;
		f[v][1]=_fv1;
		g[v]=_gv;
		sum[v]=_sv;
	}
}
int main(){
	scanf("%d",&T);
	for(int t=1;t<=T;t++){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			fa[i]=0;
			ans[i]=0;
			faW[i]=0;
			sum[i]=0;
			G[i].clear();
		}
		
		for(int i=1;i<=n;i++)
			scanf("%d",&V[i]);
		for(int i=1;i<n;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			G[u].push_back((edge){u,v,w});
			G[v].push_back((edge){v,u,w});
		}
		
		dp(1);
		ans[1]=f[1][0];
		dfs(1);
		printf("Case #%d:\n",t);
		for(int i=1;i<=n;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}

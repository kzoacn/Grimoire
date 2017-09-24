#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+1e4+233;
const int BIT=18;
int n,m,q;
struct edge{
	int u,v,w;
	bool operator==(edge oth)const{
		return u==oth.u && v==oth.v && w==oth.w;
	}
	bool operator!=(edge oth)const{
		return !(*this==oth);
	}
};
vector<edge>G[maxn],T[maxn];

int dfn[maxn],low[maxn],tot,rlen[maxn];
bool ins[maxn];
stack<edge>S;
int Rcnt=0;
vector<edge>ring[maxn];
vector<int>bel[maxn],sum[maxn],dis[maxn];
int fa[maxn][BIT];
int dep[maxn],dep2[maxn],fw[maxn];
vector<pair<int,int> >ind[maxn];
map<pair<int,int>,int>Mw;
pair<int,int>pack(int a,int b){
	if(a>b)swap(a,b);
	return make_pair(a,b);
}
void tarjan(int u){
	dfn[u]=low[u]=++tot;
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(dfn[e.v])
			low[u]=min(low[u],dfn[e.v]);
		else{
			S.push(e);
			tarjan(e.v);
			if(low[e.v]==dfn[u]){
				
				if(S.top()==e){
					fa[e.v][0]=u;
					fw[e.v]=e.w;
					S.pop();
					continue;
				}
				
				Rcnt++;
				edge ed;
				do{  
                    ed=S.top();S.pop(); 
                    ring[Rcnt].push_back(ed); 
                }while(ed!=e);  
            	reverse(ring[Rcnt].begin(),ring[Rcnt].end());
                int last=ring[Rcnt].back().v;
            	ring[Rcnt].push_back((edge){last,u,Mw[pack(last,u)]});
			}
			low[u]=min(low[u],low[e.v]);  
		}
	}
}
void up(int u){
	if(dep[u]||u==1)return ;
	if(fa[u][0])up(fa[u][0]);
	dep[u]=dep[fa[u][0]]+1;
	fw[u]+=fw[fa[u][0]];
}
void build(){
	S.push((edge){0,1,0});
	tarjan(1);
	
	for(int i=1;i<=Rcnt;i++){
		rlen[i]=0;
		sum[i].resize(ring[i].size());
		dis[i].resize(ring[i].size());
		for(int j=0;j<ring[i].size();j++){
			rlen[i]+=ring[i][j].w;
			ind[i].push_back(make_pair(ring[i][j].u,j));
		}
		sum[i][0]=0;
		fw[i+n]=0;
		fa[i+n][0]=ring[i][0].u;
		for(int j=1;j<ring[i].size();j++){
			sum[i][j]=sum[i][j-1]+ring[i][j-1].w;
			dis[i][j]=min(sum[i][j],rlen[i]-sum[i][j]);
			fw[ring[i][j].u]=dis[i][j];
			fa[ring[i][j].u][0]=i+n;
		}
		sort(ind[i].begin(),ind[i].end());
	}
	
	for(int i=1;i<=n+Rcnt;i++)
		up(i);
		
	for(int j=1;j<BIT;j++)
	for(int i=1;i<=n+Rcnt;i++)if(fa[i][j-1])
		fa[i][j]=fa[fa[i][j-1]][j-1];
	
}
pair<int,int>second_lca;
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<BIT;i++)if(d>>i&1)
		u=fa[u][i];
	if(u==v)return u;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i]){
		u=fa[u][i];
		v=fa[v][i];
	}
	second_lca=make_pair(u,v);
	return fa[u][0];
}
int main(){
	
	freopen("bzoj2125.in","r",stdin);
	
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});
		Mw[pack(u,v)]=w;
	}
	
	build();
	while(q--){
		int u,v;
		scanf("%d%d",&u,&v);
		int LCA=lca(u,v);
		if(LCA<=n)printf("%d\n",fw[u]+fw[v]-2*fw[LCA]);
		else{
			if(dep[u]<dep[v])swap(u,v);
			int R=LCA-n;
			int uu=second_lca.first;
			int vv=second_lca.second;
			int ans=fw[u]-fw[uu]+fw[v]-fw[vv];
			int uid,vid;
			uid=lower_bound(ind[R].begin(),ind[R].end(),make_pair(uu,-1))->second;
			vid=lower_bound(ind[R].begin(),ind[R].end(),make_pair(vv,-1))->second;
			ans+=min(abs(sum[R][uid]-sum[R][vid]),rlen[R]-abs(sum[R][uid]-sum[R][vid]));
			printf("%d\n",ans);
		}
	}
	return 0;
}

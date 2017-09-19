#include<bits/stdc++.h>
using namespace std;
const int maxn=4e4+4;

int n,m;

unordered_map<string,int>M;
int id(string s){
	if(M.count(s))
		return M[s];
	return M[s]=++n;
}

struct edge{
	int u,v,cap,flow,cost;
};

vector<int>G[maxn];
vector<edge>E;
void add_edge(int u,int v,int cap,int cost){
//cerr<<u<<" "<<v<<" "<<cap<<" "<<cost<<endl;
	E.push_back((edge){u,v,cap,0,cost});
	G[u].push_back(E.size()-1);
	E.push_back((edge){v,u,0,0,-cost});
	G[v].push_back(E.size()-1);
}
int cost,flow,s,t;
bool spfa(){
	static int vis[maxn],d[maxn],a[maxn],pre[maxn];
	const int inf=1e9;
	for(int i=s;i<=t;i++){
		d[i]=inf;
	}
	a[s]=INT_MAX;
	queue<int>q;q.push(s);vis[s]=1;d[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=E[G[u][i]];
			if(e.cap==e.flow||d[e.v]<=d[u]+e.cost)continue;
			a[e.v]=min(e.cap-e.flow,a[u]);
			pre[e.v]=G[u][i];
			d[e.v]=d[u]+e.cost;
			if(!vis[e.v]){
				vis[e.v]=1;
				q.push(e.v);
			}
		}
	}
	if(d[t]==inf)return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	int u=t;
	while(u!=s){
		E[pre[u]].flow+=a[t];
		E[pre[u]^1].flow-=a[t];
		u=E[pre[u]].u;
	}
	return true;

}


int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d",&m);
		M.clear();
		n=0;
		id("Dalian");
		id("Shanghai");
		id("Xian");
		//in[x]=x*2 out[x]=x*2+1
		int e=0;
		static edge ed[maxn];
		for(int i=1;i<=m;i++){
			static char s1[2000],s2[2000];	
			int u,v,w;
			scanf("%s%s%d",s1,s2,&w);
			u=id(s1);v=id(s2);
			ed[e++]=(edge){u,v,0,0,w};
			//cerr<<u<<" "<<v<<" "<<w<<endl;
		}
		
		
		s=1;t=n*2+2;
		E.clear();
		for(int i=s;i<=t;i++)
			G[i].clear();
		
		add_edge(s,2*2+1,2,0);
		
		for(int i=0;i<e;i++){
			add_edge(ed[i].u*2+1,ed[i].v*2,1,ed[i].cost);
			
			add_edge(ed[i].v*2+1,ed[i].u*2,1,ed[i].cost);
		}
		
		for(int i=1;i<=n;i++){
			add_edge(i*2,i*2+1,1,0);
		}		
		add_edge(1*2+1,t,1,0);
		add_edge(3*2+1,t,1,0);
		
		
		cost=flow=0;
		while(spfa());
		if(flow==2){
			printf("%d\n",cost);
		}else
			puts("-1");
			
	}
	return 0;
}

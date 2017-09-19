#include<bits/stdc++.h>

using namespace std;
const int maxn=2e4+5;
const int inf=1e9;
int n,m;
struct D_MT{
	struct Edge{
		int u,v,w;
		inline Edge(){}
		inline Edge(int _u,int _v,int _w):u(_u),v(_v),w(_w){
		
		}
	};
	int nn,mm,n,m,vis[maxn],pre[maxn],id[maxn],in[maxn];
	Edge edges[maxn],bac[maxn];
	void init(int _n){
		n=_n;
		m=0;
	}
	void AddEdge(int u,int v,int w){
		edges[m++]=Edge(u,v,w);
//		fprintf(stderr,"%d -> %d w:%d\n",u,v,w);
	}
	int work(int root){
		int ret=0;
		while(true){
			for(int i=0;i<n;i++)in[i]=inf+1;
			for(int i=0;i<m;i++){
				int u=edges[i].u,v=edges[i].v;
				if(edges[i].w<in[v]&&u!=v){
					in[v]=edges[i].w;
					pre[v]=u;
				}
			}
			for(int i=0;i<n;i++){
				if(i==root)continue;
				if(in[i]==inf+1)return inf;	
			}
			
			int cnt=0;
			//TODO memst
			for(int i=0;i<n;i++){
				id[i]=-1;
				vis[i]=-1;
			}
			in[root]=0;
			for(int i=0;i<n;i++){
				ret+=in[i];
				int v=i;
				while(vis[v]!=i&&id[v]==-1&&v!=root){
					vis[v]=i;
					v=pre[v];
				}
				if(v!=root&&id[v]==-1){
					for(int u=pre[v];u!=v;u=pre[u])id[u]=cnt;
					id[v]=cnt++;
				}
			}
			if(!cnt)break;
			for(int i=0;i<n;i++)
				if(id[i]==-1)id[i]=cnt++;
			for(int i=0;i<m;i++){
				int u=edges[i].u,v=edges[i].v;
				edges[i].v=id[v];
				edges[i].u=id[u];				
				if(id[u]!=id[v])edges[i].w-=in[v];
			}
			n=cnt;
			root=id[root];
		}
		return ret;
	}
}MT;

int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&m);
		MT.init(n);
		for(int i=1;i<=m;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			
			u--;v--;
			
			w=10000*(101-w);
			if(v==n-1)
				w-=n-u;
			MT.AddEdge(u,v,w);
		}
		int ans=MT.work(0);
		ans=10000*101*(n-1)-ans;
//		cerr<<ans<<endl;
		printf("%d %d\n",ans/10000,n-ans%10000+1);
	}
	return 0;
}

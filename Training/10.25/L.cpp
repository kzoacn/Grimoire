#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
int n;
void bfs(int s,LL *d){
	static int vis[maxn];
	for(int i=1;i<=n;i++)vis[i]=0;
	queue<int>q;q.push(s);
	d[s]=0;vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto e:G[u]){
			if(vis[e.v])continue;
			d[e.v]=d[u]+e.w;
			vis[e.v]=1;
			q.push(e.v);
		}
	}
}
int main(){
	while(scanf("%d",&n)==1){
		for(int i=1;i<=n;i++)G[i].clear();
		for(int i=1;i<n;i++){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			G[u].push_back((edge){u,v,w});
			G[v].push_back((edge){v,u,w});
		}
		static LL d1[maxn],d2[maxn];
		bfs(1,d1);
		int s=max_element(d1+1,d1+1+n)-d1;
		bfs(s,d2);
		int t=max_element(d2+1,d2+1+n)-d2;
		bfs(s,d1);
		bfs(t,d2);
		long long ans=0;
		for(int i=1;i<=n;i++)
			ans+=max(d1[i],d2[i]);
		ans-=d1[t];
		cout<<ans<<endl;
	}
	return 0;
}

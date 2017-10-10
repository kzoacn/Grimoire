#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
const LL inf=1LL<<61;
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
int n,m;
LL d[maxn];
bool spe[maxn],st[maxn];
LL ans;
typedef pair<LL,int>par;
void dijk(){
	priority_queue<par,vector<par>,greater<par> >q;
	for(int i=1;i<=n;i++){
		d[i]=inf;
		if(spe[i]&&st[i]){
			q.push({d[i]=0,i});
		}
	}
	while(!q.empty()){
		int u=q.top().second;
		if(d[u]!=q.top().first){
			q.pop();
			continue;
		}
		q.pop();
		for(auto e:G[u]){
			if(d[e.v]>d[u]+e.w){
				d[e.v]=d[u]+e.w;
				q.push({d[e.v],e.v});
			}
		}
	}
	for(int i=1;i<=n;i++)if(spe[i]&&!st[i])
		ans=min(ans,d[i]);
}

LL solve(){
	scanf("%d%d",&n,&m);
	//clear
	for(int i=1;i<=n;i++){
		spe[i]=0;
		G[i].clear();
	}
	
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back((edge){u,v,w});
	}
	int k;scanf("%d",&k);
	for(int i=0;i<k;i++){
		int x;scanf("%d",&x);
		spe[x]=1;
	}	
	ans=inf;
	for(int i=0;i<=20;i++){
		for(int j=1;j<=n;j++){
			st[j]=(j>>i&1);
		}
		dijk();
		
		for(int j=1;j<=n;j++){
			st[j]^=1;
		}
		dijk();
	}
	return ans;
}
int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %lld\n",t,solve());
	}
	return 0;
}

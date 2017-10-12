#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+1e5+5;
typedef long long LL;
typedef pair<LL,int>par;
int n,m;
const LL inf=1LL<<61;
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
void dijk(LL *d,int s){
	for(int i=1;i<=n+m;i++)
		d[i]=inf;
	priority_queue<par,vector<par>,greater<par> >q;
	q.push({d[s]=0,s});
	while(!q.empty()){
		int u=q.top().second;
		if(d[u]!=q.top().first){
			q.pop();continue;
		}
		q.pop();
		for(auto e:G[u]){
			if(d[e.v]>d[u]+e.w){
				d[e.v]=d[u]+e.w;
				q.push({d[e.v],e.v});
			}
		}
	}
}

int main(){
	int T;cin>>T;
	for(int tt=1;tt<=T;tt++){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n+m;i++){
			G[i].clear();
		}
		for(int i=1;i<=m;i++){
			int t,k;
			scanf("%d%d",&t,&k);
			while(k--){
				int x;scanf("%d",&x);
				G[i+n].push_back((edge){i+n,x,0});
				G[x].push_back((edge){x,i+n,t});
//				cerr<<x<<" "<<i+n<<" "<<t<<endl;
			}
		}
		printf("Case #%d: ",tt);
		static LL d1[maxn],d2[maxn];
		dijk(d1,1);
		dijk(d2,n);

		
		vector<int>ans;
		LL mn=inf;
		for(int i=1;i<=n;i++){
			LL t=max(d1[i],d2[i]);
			//cerr<<i<<" is "<<t<<endl;
			if(t<mn){
				mn=t;
				ans.clear();
			}
			if(t==mn)
				ans.push_back(i);
		}
		if(mn!=inf){
			printf("%lld\n",mn);
			for(int i=0;i<ans.size();i++)
				printf("%d%c",ans[i]," \n"[i+1==ans.size()]);
		}else{
			puts("Evil John");
		}
	}	
	return 0;
}

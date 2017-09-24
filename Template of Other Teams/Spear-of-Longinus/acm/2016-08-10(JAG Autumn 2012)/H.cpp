#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=2111;
typedef long long LL;
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
void add(int u,int v,int w){
	G[u].push_back((edge){u,v,w});
	G[v].push_back((edge){v,u,w});
}
int n,m,S1,S2,T;
char s[233];
int getint(char *s){
	int len=strlen(s);
	if(s[0]=='x')return -1;
	int r=0;
	for(int i=0;i<len;i++)
		r=r*10+s[i]-'0';
	return r;
}
LL d[maxn][110];
int xcnt=0;
typedef pair<int,int> par;
void dijk(int s){
	for(int i=0;i<=n;i++)
	for(int j=0;j<=xcnt;j++)
		d[i][j]=1LL<<50;
	d[s][0]=0;
	priority_queue<pair<LL,par>,vector<pair<LL,par> >,greater<pair<LL,par> > >q;
	q.push(make_pair(d[s][0],make_pair(s,0)));
	while(!q.empty()){
		int u=q.top().second.first;
		int cnt=q.top().second.second;
		
		if(q.top().first!=d[u][cnt]){
			q.pop();
			continue;
		}
		
		q.pop();
		for(int i=0;i<G[u].size();i++){
			edge e=G[u][i];
			if(e.w==-1){
				if(cnt>=xcnt)continue;
				if(d[e.v][cnt+1] > d[u][cnt]){
					d[e.v][cnt+1]=d[u][cnt];
					q.push(make_pair(d[e.v][cnt+1],make_pair(e.v,cnt+1)));
				}
			}else{
				if(d[e.v][cnt] > d[u][cnt]+e.w){
					d[e.v][cnt] = d[u][cnt]+e.w;
					q.push(make_pair(d[e.v][cnt],make_pair(e.v,cnt)));
				}	
			}
		}
		
	}
}
LL Abs(LL x){return x>0?x:-x;}
LL calc(LL a,LL b,LL l,LL r){

	LL ans=min(Abs(a*l+b),Abs(a*r+b));
	if(a!=0){
		LL t=(long double)-b/a;
		for(LL i=t-3;i<=t+3;i++){
			if(l<=i&&i<=r)
				ans=min(ans,Abs(a*i+b));
		}
	}
	return ans;
}
pair<LL,LL> a[maxn],b[maxn];

LL Ceil(LL p,LL q){
	if (q < 0) p = -p, q = -q;
	if (p < 0) return -1;
	return (p + q - 1) / q;
}
LL Floor(LL p,LL q){
	if (q < 0) p = -p, q = -q;
	if (p < 0) return -1;
	return p / q;
}

int main(){
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	while(cin>>n>>m>>S1>>S2>>T){
		if(!n)break;
		for(int i=1;i<=n;i++)
			G[i].clear();
		xcnt=0;
		
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			cin>>s;
			int w=getint(s);
			xcnt+=(w==-1);
			add(u,v,w);
		}
		dijk(T);
		
		const LL inf=1LL<<50;
		
		LL ans=1LL<<50;
		
		for(int i=0;i<=xcnt;i++){
			a[i]=make_pair(0,1LL<<50);
			b[i]=make_pair(0,1LL<<50);
			for(int j=0;j<=xcnt;j++){
				if (i < j) {
					if (d[S1][j] != inf && d[S1][i] != inf) 
						a[i].first = max(a[i].first, Ceil(d[S1][j] - d[S1][i],i - j));
					if (d[S2][j] != inf && d[S2][i] != inf) 	
						b[i].first = max(b[i].first, Ceil((d[S2][j] - d[S2][i]),(i - j)));
					
				}
				if (i > j) {
					if (d[S1][j] != inf && d[S1][i] != inf) 
						a[i].second= min(a[i].second, Floor((d[S1][j] - d[S1][i]),(i - j)));
					if (d[S2][j] != inf && d[S2][i] != inf) 	
						b[i].second = min(b[i].second, Floor((d[S2][j] - d[S2][i]),(i - j)));
				}					
			}
		}
		
		
		
		for(int i=0;i<=xcnt;i++)
		for(int j=0;j<=xcnt;j++){
			if(d[S1][i]!=inf && d[S2][j]!=inf){
				LL l=max(a[i].first,b[j].first);
				LL r=min(a[i].second,b[j].second);
				l=max(l,0LL);
				if(l<=r)
					ans=min(ans,calc(i-j,d[S1][i]-d[S2][j],l,r));
			}
		}
		cout<<ans<<endl;
		//printf("%lld\n",ans);
	}
	return 0;
}

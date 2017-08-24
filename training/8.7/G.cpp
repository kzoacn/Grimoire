#include<bits/stdc++.h>
using namespace std;
const int maxn=6e5+5;
typedef long long LL;
const LL mo=998244353;
int T;
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];
int d[maxn];
int n;

int vis[maxn],w[maxn],fa[maxn];
int sz,tmp[maxn],dep[maxn];

LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans;
}

void dfs(int u){
	vis[u]=1;
	tmp[++sz]=u;
	for(auto e:G[u]){
		if(!vis[e.v]){
			dfs(e.v);
		}
	}
}
LL topsort(){
	queue<int>q;
	static int pt[maxn];
	static int vis[maxn];
	for(int i=1;i<=sz;i++){
		vis[tmp[i]]=0;
		if(d[tmp[i]]==1){
			q.push(tmp[i]);
			vis[tmp[i]]=1;
		}
	}
	pt[0]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		pt[++pt[0]]=u;
		for(auto e:G[u]){
			if(vis[e.v])continue;
			fa[u]=e.v;
			w[u]=e.w;
			if(--d[e.v] == 1){
				q.push(e.v);
				vis[e.v]=1;
			}
		}
	}
	
	int st=0;
	for(int i=1;i<=sz;i++)if(!vis[tmp[i]]){
		st=tmp[i];
		break;
	}
	LL odd=1,even=1;
	int u=st;
	int cur=0;
	int lastval=-1;
	//cerr<<endl;
	while(!vis[u]){
		cur^=1;vis[u]=2;
		//cerr<<u<<endl;
		for(auto e:G[u]){
			//cerr<<e.u<<"->"<<e.v<<" "<<e.w<<endl;
			if(e.v==st)lastval=e.w;
			if(!vis[e.v]){
				
				//cerr<<u<<"->"<<e.v<<" "<<e.w<<endl;
				if(cur){
					odd=odd*e.w%mo;
				}else{
					even=even*e.w%mo;				
				}
				u=e.v;
				break;
			}
		}
	}
	//cerr<<lastval<<endl;
	if(cur){
		odd=odd*lastval%mo;
	}else{
		even=even*lastval%mo;
	}
	
	LL tot=1;
	for(int i=pt[0];i>=1;i--){
		int u=pt[i];
		dep[u]=dep[fa[u]]+1;
		if(dep[u]%2==0)
			tot=tot*w[u]%mo;
	}

//	cerr<<tot<<" "<<odd<<" "<<even<<endl; 	
	return tot*(odd+even)%mo;
}


void solve(){
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++){
		G[i].clear();
		vis[i]=0;
		d[i]=0;
		dep[i]=0;
	}
	for(int i=1;i<=n;i++){
		int v1,w1,v2,w2;
		scanf("%d%d%d%d",&v1,&w1,&v2,&w2);
		v1+=n;v2+=n;
		G[i].push_back((edge){i,v1,w1});
		G[i].push_back((edge){i,v2,w2});
		G[v1].push_back((edge){v1,i,w1});
		G[v2].push_back((edge){v2,i,w2});
		d[i]+=2;
		d[v1]++;
		d[v2]++;
	}
	
	LL ans=1;
	for(int i=1;i<=2*n;i++){
		if(!vis[i]){
			sz=0;
			dfs(i);
			ans=ans*topsort()%mo;
		}
	}
	cout<<ans<<endl;
	
}
int main(){
	cin>>T;
	for(int t=1;t<=T;t++)
		solve();
	return 0;
}

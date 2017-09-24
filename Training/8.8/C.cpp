#include<bits/stdc++.h>
using namespace std;
const int maxn=20020;
typedef double LD;
struct tupl{
	LD x,y,z;
	tupl(){}
	tupl(LD _x,LD _y,LD _z):x(_x),y(_y),z(_z){}
	
	
	void print(){
		printf("%.3f,%.3f,%.3f\n",x,y,z);
	}
};
tupl operator+(tupl a,tupl b){
	return tupl(a.x+b.x,a.y+b.y,a.z+b.z);
}
tupl operator-(tupl a,tupl b){
	return tupl(a.x-b.x,a.y-b.y,a.z-b.z);
}
tupl operator*(tupl a,LD b){
	return tupl(a.x*b,a.y*b,a.z*b);
}
tupl operator/(tupl a,LD b){
	return tupl(a.x/b,a.y/b,a.z/b);
}
tupl dp[maxn];

LD p[maxn];
int s[maxn];

int n,m;
int fa[maxn];
vector<int>G[maxn];
LD sum=0;
void dfs1(int u){
	
	tupl son(0,0,0);
	for(auto v:G[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		dfs1(v);
		son=son+dp[v];
	}
	
	son=son/G[u].size();
	son=son*(1-sum);
	LD c=1-son.z;
	//cerr<<u<<" "<<c<<endl;
	dp[u].x=(1+son.x)/c;
	dp[u].y=((1-sum)+son.y)/c;
	dp[u].z=(1-sum)/G[u].size()/c;
	
}
void dfs2(int u){
	
	for(auto v:G[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		
		dp[v]=dp[v]+dp[u]*dp[v].z;
		
		dfs2(v);
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		fa[i]=0;
		G[i].clear();
	}
	sum=0;
	
	bool contain=0;
	
	for(int i=1;i<=m;i++){
		double _p;
		scanf("%d%lf",&s[i],&_p);
		p[i]=_p;
		sum+=p[i];
		if(s[i]==n&&p[i]>0)
			contain=1;
	}
	
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	if(sum>=1-1e-9){
		if(!contain)
			puts("impossible");
		else
			puts("0");
		return ;
	}
	
	dfs1(n);
	
//	for(int i=1;i<=n;i++)
//		dp[i].print();
	
	dp[n]=tupl(0,0,0);
	dfs2(n);
	
//	cerr<<"after"<<endl;
//	for(int i=1;i<=n;i++)
//		dp[i].print();
		
	
	LD a=0,b=0;
	for(int i=1;i<=m;i++){
		a+=dp[s[i]].x*p[i];
		b+=dp[s[i]].y*p[i];
	}
	LD x=-b/(a-1);
	
	
	printf("%.9f\n",(double)(dp[1].x*x+dp[1].y));
	
}
int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: ",t);
		solve();
	}
		
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
typedef long long LL;
int n;
struct P{
	LL x,y;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
};

P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
bool onLine(P p,P a,P b){
	return (p-a)*(b-a)==0;
}
bool onLine(P a1,P b1,P a2,P b2){
	if(onLine(a1,a2,b2)&&onLine(b1,a2,b2))
		return true;
	return false;
}
bool touch(P a1,P b1,P a2,P b2){
	if(!onLine(a1,b1,a2,b2))
		return false;
	LL lx=max(min(a1.x,b1.x),min(a2.x,b2.x));
	LL rx=min(max(a1.x,b1.x),max(a2.x,b2.x));
	
	LL ly=max(min(a1.y,b1.y),min(a2.y,b2.y));
	LL ry=min(max(a1.y,b1.y),max(a2.y,b2.y));
	return (lx<rx) || (ly<ry);
}
vector<P>poly[55];

int deg[50];
vector<int>G[maxn];

bool touch(vector<P> a,vector<P> b){
	for(int i=0;i<a.size();i++){
		for(int j=0;j<b.size();j++){
			if(touch(a[i],a[(i+1)%a.size()],b[j],b[(j+1)%b.size()])){
				return true;
			}
		}
	}
	return false;
}

int col[55],vis[55],ok,tdeg[55];
void dfs2(int u){
	vis[u]=1;
	for(int i=0,v;i<G[u].size();i++){
		v=G[u][i];
		if(vis[v]){
			if(col[u]==col[v])
				ok=0;
			continue;
		}
		col[v]=3-col[u];
		dfs2(v);
	}
}

int nxtmax(){
	int mx=-1,pos=-1;
	for(int i=1;i<=n;i++)if(!vis[i]){
		if(deg[i]>mx){
			mx=deg[i];
			pos=i;
		}
	}
	return pos;
}

void addDeg(int u,int y){
	for(int i=0,v;i<G[u].size();i++){
		v=G[u][i];
		deg[v]+=y;
	}
}

bool checkpos(int u,int c){
	for(int i=0,v;i<G[u].size();i++){
		v=G[u][i];
		if(col[v]==c)
			return false;
	}
	return true;
}

void dfs3(int u){

	if(u==-1){
		ok=1;
		return ;
	}
	if(tdeg[u]<=2){
		vis[u]=1;			
		dfs3(nxtmax());
		return ;
	}

	for(int i=1;i<=3;i++){
		if(checkpos(u,i)){
			col[u]=i;
			vis[u]=1;
			addDeg(u,-1);
			
			dfs3(nxtmax());
			if(ok)return ;
			addDeg(u,1);
			vis[u]=0;
			col[u]=0;
		}
	}
}

int main(){
	while(scanf("%d",&n)==1&&n){
		for(int i=1;i<=n;i++){
			poly[i].clear();
			int m;scanf("%d",&m);
			poly[i].resize(m);
			for(int j=0;j<poly[i].size();j++){
				poly[i][j].read();
			}
		}
		for(int i=1;i<=n;i++){
			G[i].clear();
			tdeg[i]=deg[i]=0;
			for(int j=1;j<=n;j++)if(i!=j){
				if(touch(poly[i],poly[j])){
					G[i].push_back(j);
					deg[i]++;
					tdeg[i]++;
					//cerr<<i<<" "<<j<<endl;
				}
			}
		}
		
		if(*max_element(deg+1,deg+1+n)==0){
			puts("1");
			continue;
		}
		ok=1;
		for(int i=1;i<=n;i++){
			col[i]=0;
			vis[i]=0;
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				col[i]=1;
				dfs2(i);
			}
		}
		if(ok){
			puts("2");
			continue;
		}
		
		
		ok=0;
		for(int i=1;i<=n;i++){
			col[i]=0;
			vis[i]=0;
		}
		
		dfs3(nxtmax());
		
		if(ok){
			puts("3");
		}else{
			puts("4");
		}
	}
	return 0;
}

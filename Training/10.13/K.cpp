#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
map<tuple<int,int,int>,int>M;

int n;
tuple<int,int,int> read(){
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	return make_tuple(x,y,z);
}


tuple<int,int,int> p[maxn][2];
int fa[maxn];

int find(int x){
	return fa[x]==x ? x :fa[x]=find(fa[x]);
}

int tot=0;
int id(tuple<int,int,int> tp){
	if(!M[tp])M[tp]=++tot;
	return M[tp];
}
pair<int,int>pack(int x,int y){
	if(x>y)swap(x,y);
	return make_pair(x,y);
}
set<pair<int,int> >E;


int main(){

	bool ans1=false,ans2=false;

	scanf("%d",&n);
	
	for(int i=1;i<=n*2;i++)
		fa[i]=i;
	
	for(int i=1;i<=n;i++){
		p[i][0]=read();
		p[i][1]=read();
		int u=id(p[i][0]);
		int v=id(p[i][1]);
		//cerr<<u<<" "<<v<<endl;
		if(u==v)continue;
		if(E.count(pack(u,v)))continue;
		E.insert(pack(u,v));
		if(find(u)==find(v)){
			ans1=true;
		}
		
		fa[find(u)]=find(v);
	}
	
	tot=0;
	M.clear();
	E.clear();
	
	for(int i=1;i<=n*2;i++)
		fa[i]=i;
	

	for(int i=1;i<=n;i++){
		get<2>(p[i][0])=0;
		get<2>(p[i][1])=0;
		int u=id(p[i][0]);
		int v=id(p[i][1]);
		//cerr<<u<<" "<<v<<endl;
		
		if(u==v)continue;
		
		if(E.count(pack(u,v)))continue;
		E.insert(pack(u,v));
		if(find(u)==find(v)){
			ans2=true;
		}
		
		fa[find(u)]=find(v);
	}
	
	puts(ans1?"True closed chains":"No true closed chains");
	puts(ans2?"Floor closed chains":"No floor closed chains");
	
	return 0;
}

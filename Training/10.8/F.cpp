#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef pair<int,int> P;
const int maxn=5e4+4;

int fa[maxn];
set<int>S[maxn],Q[maxn];
int find(int x){return fa[x]==x ? x :fa[x]=find(fa[x]);}

int cntW,cntB;

map<P,int>ID;
P pos[maxn];
int col[maxn];

const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int n;
int tot=0;

template<class T>
void clear(T &t){
	T().swap(t);
}

void as(bool x){
	if(!x){
		int *p=0;
		(*p)++;
	}
}

void test_dead(int x){
	x=find(x);
	if(Q[x].size())return;
	
	//cerr<<pos[x].X<<","<<pos[x].Y<<" die"<<endl;
	for(auto s:S[x]){
		for(int k=0;k<4;k++){
			P p;
			p.X=pos[s].X+dx[k];
			p.Y=pos[s].Y+dy[k];
			as(pos[s].X);
			if(p.X>=1&&p.Y>=1){
				if(col[ID[p]]==-col[x])
					Q[find(ID[p])].insert(s);
			}
		}
	}
	if(col[x]==1){
		cntB-=S[x].size();
	}else{
		cntW-=S[x].size();
	}
	for(auto s:S[x]){
		fa[s]=s;
		col[s]=0;
	}
	
	clear(Q[x]);
	clear(S[x]);
}

void merge(P a,P b){
	if(!ID[b]){
		ID[b]=++tot;
		pos[tot]=b;
		col[ID[b]]=0;
		fa[ID[b]]=ID[b];
	}
	int x=ID[a],y=ID[b];
	
	//cerr<<"other "<<b.X<<","<<b.Y<<endl;
	if(col[y]==0){
		Q[find(x)].insert(y);
	//	cerr<<"make Qi"<<endl;
	}else
	if(col[y]==col[x]){
		if(find(x)==find(y))return;
	//	cerr<<"Merge "<<endl;
		//x <- y
		if(S[find(x)].size()>S[find(y)].size()){
			for(auto s:S[find(y)])
				S[find(x)].insert(s);
			clear(S[find(y)]);
		}else{
			for(auto s:S[find(x)])
				S[find(y)].insert(s);
			swap(S[find(x)],S[find(y)]);
			clear(S[find(y)]);
		}
		
		if(Q[find(x)].size()>Q[find(y)].size()){
			for(auto q:Q[find(y)])
				Q[find(x)].insert(q);
			clear(Q[find(y)]);
		}else{
			for(auto q:Q[find(x)])
				Q[find(y)].insert(q);
			swap(Q[find(x)],Q[find(y)]);
			clear(Q[find(y)]);
		}
		Q[find(x)].erase(x);
		fa[find(y)]=find(x);
	}else{
	//	cerr<<"Erase Qi"<<endl;
		Q[find(y)].erase(x);
	}
	
}

void put(P p){
	S[ID[p]].insert(ID[p]);
	//cerr<<"put "<<p.X<<" "<<p.Y<<endl;
	for(int k=0;k<4;k++){
		int x=p.X+dx[k];
		int y=p.Y+dy[k];
		if(x>=1&&y>=1){
			merge(p,make_pair(x,y));
		}
	}
	for(int k=0;k<4;k++){
		int x=p.X+dx[k];
		int y=p.Y+dy[k];
		if(x>=1&&y>=1){
			if(col[ID[make_pair(x,y)]]==-col[ID[p]])
				test_dead(ID[make_pair(x,y)]);
		}
	}
	test_dead(ID[p]);
}

void solve(){
ID.clear();
	scanf("%d",&n);
	cntW=cntB=0;
	tot=0;
	for(int i=1;i<=n*5;i++){
		fa[i]=i;col[i]=0;
		set<int>().swap(S[i]);
		set<int>().swap(Q[i]);
	}
	for(int i=1;i<=n;i++){
		if(i%2==1){
			cntB++;
		}else{
			cntW++;
		}
		P p;
		scanf("%d%d",&p.X,&p.Y);
		if(!ID[p]){
			ID[p]=++tot;
			pos[tot]=p;
			fa[ID[p]]=ID[p];
		}
		col[ID[p]]=i%2?1:-1;
		put(p);
	}
	printf("%d %d\n",cntB,cntW);
}

int main(){
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}

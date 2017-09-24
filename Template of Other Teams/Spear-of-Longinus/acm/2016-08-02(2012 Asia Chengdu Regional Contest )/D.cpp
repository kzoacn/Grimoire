#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#define out(x) cerr<< #x <<"="<< x <<endl;
using namespace std;
const int maxn=1e5+5;
int MAGIC=444;
typedef long long LL;
struct edge{
	int u,v;
	LL w;
	edge(){}
	edge(int u,int v,LL w):u(u),v(v),w(w){}
};
int B[maxn],Bsiz;
edge edges[maxn];
int Esiz;

struct node  {
	int start[maxn], tot;
	int u[maxn * 2], v[maxn * 2];
	LL w[maxn * 2];
	int next[maxn * 2];
	void clear(int n) {
		for(int i = 0; i <= n; i++) {
			start[i] = 0;
		}
		tot = 0;
	}
	void add(int x, int y, LL key) {
		tot++;
		u[tot] = x;
		v[tot] = y;
		w[tot] = key;
		next[tot] = start[x];
		start[x] = tot;
	}
}G, G2;

int n,m,q;
int col[maxn],deg[maxn];
int type[maxn];
LL ansAA00;
LL ansAA01;
LL ansAA11;
LL ansBB00;
LL ansBB01;
LL ansBB11;
LL ansAB1[maxn];
LL ansAB0[maxn];
int rid[maxn];
inline void CA(int x){
	for(int i = G.start[x]; i; i = G.next[i]) {
		int v=G.v[i];
		LL w=G.w[i];
		//cerr<<x<<" "<<v<<" "<<w<<endl;
		if(col[x]==0&&col[v]==0){
			if(type[v]==1)
				ansAA00-=w;
			else
				ansAB0[rid[v]]-=w;
		}else
		if(col[x]==0&&col[v]==1){
			if(type[v]==1)
				ansAA01-=w;
			else
				ansAB0[rid[v]]-=w;
		}else
		if(col[x]==1&&col[v]==0){
			if(type[v]==1)
				ansAA01-=w;
			else
				ansAB1[rid[v]]-=w;
		}else
		if(col[x]==1&&col[v]==1){
			if(type[v]==1)
				ansAA11-=w;
			else
				ansAB1[rid[v]]-=w;
		}
		
		col[x]^=1;
		
		
		if(col[x]==0&&col[v]==0){
			if(type[v]==1)
				ansAA00+=w;
			else
				ansAB0[rid[v]]+=w;
		}else
		if(col[x]==0&&col[v]==1){
			if(type[v]==1)
				ansAA01+=w;
			else
				ansAB0[rid[v]]+=w;
		}else
		if(col[x]==1&&col[v]==0){
			if(type[v]==1)
				ansAA01+=w;
			else
				ansAB1[rid[v]]+=w;
		}else
		if(col[x]==1&&col[v]==1){
			if(type[v]==1)
				ansAA11+=w;
			else
				ansAB1[rid[v]]+=w;
		}
		col[x]^=1;
	}

	col[x]^=1;

}
inline void CB(int x){

	for(int i = G2.start[rid[x]]; i; i = G2.next[i]) {
		int v=G2.v[i];
		LL w=G2.w[i];
		
		if(col[x]==0&&col[B[v]]==0)
			ansBB00-=w;else
		if(col[x]==0&&col[B[v]]==1)
			ansBB01-=w;else
		if(col[x]==1&&col[B[v]]==0)
			ansBB01-=w;else
		if(col[x]==1&&col[B[v]]==1)
			ansBB11-=w;
		
		col[x]^=1;	
		
		
		if(col[x]==0&&col[B[v]]==0)
			ansBB00+=w;else
		if(col[x]==0&&col[B[v]]==1)
			ansBB01+=w;else
		if(col[x]==1&&col[B[v]]==0)
			ansBB01+=w;else
		if(col[x]==1&&col[B[v]]==1)
			ansBB11+=w;
		
		col[x]^=1;	
	}
	col[x]^=1;	
}

inline LL Q(int c1,int c2){

	LL ans=0;

	if(c1!=c2){
		ans+=ansAA01+ansBB01;
		
		for(int i=0;i<Bsiz;i++){
			if(col[B[i]]==0){
				ans+=ansAB1[i];
			}else{
				ans+=ansAB0[i];
			}
		}
		
	}else
	if(c1==0&&c2==0){
		ans+=ansAA00+ansBB00;
		for(int i=0;i<Bsiz;i++){
			if(col[B[i]]==0)
				ans+=ansAB0[i];
		}
		
	}else
	if(c1==1&&c2==1){
		ans+=ansAA11+ansBB11;
		for(int i=0;i<Bsiz;i++){
			if(col[B[i]]==1)
				ans+=ansAB1[i];
		}
	}
	
	return ans;
}
inline int getn(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}

map<pair<int,int>,LL>M;

int main(){


	


	while(scanf("%d%d",&n,&m)==2){
		
	//	MAGIC=int(sqrt(2*m))+2;
	
		static int t=0;
		printf("Case %d:\n",++t);		
		//Clean

		ansAA00=0;
		ansAA01=0;
		ansAA11=0;
		ansBB00=0;
		ansBB01=0;
		ansBB11=0;
		Esiz=0;
		Bsiz=0;
		for(int i=1;i<=n;i++){
			deg[i]=0;type[i]=0;
		}
		for(int i=0;i<=n;i++){
			ansAB1[i]=ansAB0[i]=0;
			B[i]=0;rid[i]=0;
		}
		G.clear(n);
		G2.clear(n);
		for(int i=1;i<=n;i++)col[i]=getn();
		M.clear();
		for(int i=1;i<=m;i++){
			int u=getn(),v=getn();
			LL w=getn();
			if(u>v)swap(u,v);
			if(!M.count(make_pair(u,v))){
				deg[u]++;deg[v]++;
				edges[Esiz++]=edge(u,v,w);
				M[make_pair(u,v)]+=w;
			}else{
				M[make_pair(u,v)]+=w;
			}
		}
		
		for(int i=0;i<Esiz;i++){
			edges[i].w=M[make_pair(edges[i].u,edges[i].v)];
			//cerr<<edges[i].u<<" "<<edges[i].v<<" "<<edges[i].w<<endl;
				G.add(edges[i].u, edges[i].v, edges[i].w);
				G.add(edges[i].v, edges[i].u, edges[i].w);
		}
		
		
		for(int i=1;i<=n;i++)
			if(deg[i]>MAGIC){
				rid[i]=Bsiz;
				B[Bsiz++]=i;
				type[i]=2;
			}else
				type[i]=1;
		
		for(int i=0;i<Esiz;i++){
			int u=edges[i].u,v=edges[i].v;
			LL w=edges[i].w;
			if(type[u]==2&&type[v]==2){
				G2.add(rid[u], rid[v], w);
				G2.add(rid[v], rid[u], w);
			}
		}
		
		for(int i=0;i<Esiz;i++){
			int u=edges[i].u,v=edges[i].v;
			LL w=edges[i].w;
			if(type[u]==1&&type[v]==1){
				if(col[u]==0&&col[v]==0)
					ansAA00+=w;else
				if(col[u]==1&&col[v]==0)
					ansAA01+=w;else
				if(col[u]==0&&col[v]==1)
					ansAA01+=w;	else			
				if(col[u]==1&&col[v]==1)
					ansAA11+=w;
			}
			if(type[u]==2&&type[v]==2){
				if(col[u]==0&&col[v]==0)
					ansBB00+=w;else
				if(col[u]==1&&col[v]==0)
					ansBB01+=w;else
				if(col[u]==0&&col[v]==1)
					ansBB01+=w;	else			
				if(col[u]==1&&col[v]==1)
					ansBB11+=w;
			}
			
			if(type[u]==1&&type[v]==2){
				if(col[u]==0)
					ansAB0[rid[v]]+=w;
				if(col[u]==1)
					ansAB1[rid[v]]+=w;	
			}
			if(type[u]==2&&type[v]==1){
				if(col[v]==0)
					ansAB0[rid[u]]+=w;
				if(col[v]==1)
					ansAB1[rid[u]]+=w;	
			}
			
			
			
		}
		
	/*	out(ansAA00);
		out(ansAA01);
		out(ansAA11);
		out(ansBB00);
		out(ansBB01);
		out(ansBB11);
	*/
		//for(int i=1;i<=n;i++)
		//	printf("%d%c",type[i]," \n"[i==n]);
		
		
		//cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
		
		scanf("%d",&q);
		while(q--){
			static char cmd[20];
			scanf("%s",cmd);
			if(cmd[0]=='A'){
				int x=getn(),y=getn();
				printf("%lld\n",Q(x,y));
			}else{
				int x=getn();
				if(type[x]==1)
					CA(x);
				else CB(x);
			}
		}
		
		
		//cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	}
	return 0;
}

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=20010;
int stamp,comps,top;
int low[maxn],dfn[maxn],comp[maxn],stack[maxn];
int a[maxn],b[maxn],c[maxn];
vector<int>edge[maxn];
void add(int x,int a,int y,int b){
	edge[x<<1|a].push_back(y<<1|b);
}
void tarjan(int x){
	dfn[x]=low[x]=++stamp;
	stack[top++]=x;
	for(int i=0;i<edge[x].size();i++){
		int y=edge[x][i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(!comp[y])
			low[x]=min(low[x],dfn[y]);		
	}
	if(low[x]==dfn[x]){
		comps++;
		do{
			int y=stack[--top];
			comp[y]=comps;
		}while(stack[top]!=x);
	}

}
int n,m;
int OneMoreTimeOneMoreChance=0;
int in[maxn];
bool solve(){
	int counter=n+n+1;
	stamp=top=comps=0;
	fill(dfn,dfn+counter,0);
	fill(low,low+counter,0);
	fill(stack,stack+counter,0);
	fill(comp,comp+counter,0);
	for(int i=0;i<counter;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=0;i<n;i++){
		if(in[i]==OneMoreTimeOneMoreChance&&comp[i<<1]==comp[i<<1|1])
			return 0;
	}
	return 1;
}
bool check(int mid){
		
	OneMoreTimeOneMoreChance++;
		
	
	for(int i=0;i<mid;i++){
		edge[a[i]<<1].clear();
		edge[a[i]<<1|1].clear();
		edge[b[i]<<1].clear();
		edge[b[i]<<1|1].clear();
		in[a[i]]=OneMoreTimeOneMoreChance;
		in[b[i]]=OneMoreTimeOneMoreChance;
	}
	for(int i=0;i<mid;i++){
		if(c[i]==0){
			add(a[i],0,b[i],1);
			add(b[i],0,a[i],1);
		}
		if(c[i]==1){
			add(a[i],0,b[i],0);
			add(a[i],1,b[i],1);
			
			add(b[i],0,a[i],0);
			add(b[i],1,a[i],1);
		}
		if(c[i]==2){
			add(a[i],1,b[i],0);
			add(b[i],1,a[i],0);
		}
	}
	return solve();
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		
		for(int i=0;i<maxn;i++)edge[i].clear();
	
		scanf("%d%d",&n,&m);
		for(int i=0;i<m;i++)
			scanf("%d%d%d",&a[i],&b[i],&c[i]);
		
		
		
		int l=2,r=m+1;
		while(l<r){
			int mid=(l+r)>>1;
//			cerr<<mid<<endl;
//			cerr<<check(mid)<<endl;
			if(check(mid))
				l=mid+1;
			else
				r=mid;
		}
		printf("%d\n",l-1);
	}
	return 0;
}

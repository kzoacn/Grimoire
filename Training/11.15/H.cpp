#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;
vector<int>G[maxn];
int fa[maxn];
int match[maxn];
int n;
int rt[maxn],root;
vector<int>L[maxn];
void dfs(int u){
	for(auto v:G[u]){
		if(v==fa[u])continue;
		dfs(v);
	}
	if(fa[u]&&!match[u]&&!match[fa[u]]){
		match[u]=1;
		match[fa[u]]=1;
	}
	
	if(!match[u])
		L[root].push_back(u);
}

bool cmp(int x,int y){
	if(match[x] != match[y])	
		return match[x]>match[y];
	return L[x].size()>L[y].size();
}

int main(){

freopen("hidden.in","r",stdin);
freopen("hidden.out","w",stdout);

	scanf("%d",&n);
	for(int i=1;i<=n;i++)rt[i]=1;
	for(int i=2;i<=n;i++){
		scanf("%d",&fa[i]);
		G[fa[i]].push_back(i);
		if(fa[i])rt[i]=0;
	}
	
	for(int i=1;i<=n;i++)if(rt[i]){
		root=i;
		dfs(i);
	}
	static int id[maxn];
	for(int i=1;i<=n;i++){
		id[i]=i;
	}
	sort(id+2,id+1+n,cmp);
	/*
	for(int i=1;i<=n;i++){
		cerr<<"list "<<i<<endl;
		for(auto x:L[i])
			cerr<<x<<" ";
		cerr<<endl;
		
	}*/
	
	for(int i=2;i<=n;i++)if(rt[id[i]]){
	
		int u=id[i];
		
		
		
		while(L[1].size()){
			if(match[L[1].back()]){
				L[1].pop_back();
			}else break;
		}
		
		if(match[u]){
			fa[u]=1;
		}else{
			if(L[1].size()){
				fa[u]=L[1].back();
				match[L[1].back()]=match[u]=1;
				L[1].pop_back();
			}else{
				fa[u]=1;
			}
		}
		
		for(auto x:L[u])
			L[1].push_back(x);
	}
	
	
	cout<<accumulate(match+1,match+1+n,0)/2<<endl;
	for(int i=2;i<=n;i++)
		printf("%d%c",fa[i]," \n"[i==n]);
	
	
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
int n,m;
int cnt[1<<20];
int adj[20];
int inv[1<<20];
int con[1<<20];
int e[401],vis[1<<20];
int tot=0;
bool check(int S){
	if(vis[S])return con[S];
	vis[S]=1;
	
	int tS=S;
	int ok=0;
	while(tS){
		int x=inv[tS&-tS];	
		if(check(S^(1<<x))){
			ok=(adj[x]&(S^(1<<x)))>0;
			if(ok)break;			
		}
		tS-=tS&-tS;
	}
	return con[S]=ok;
}
void dfs(int i,int S1,int S2){
	if(i==n){
	
		/*puts("S1:");
		for(int i=0;i<n;i++)if(S1>>i&1){
			cerr<<i<<" ";
		}puts("");
		cerr<<check(S1)<<endl;
	
	
		puts("S2:");
		for(int i=0;i<n;i++)if(S2>>i&1){
			cerr<<i<<" ";
		}puts("");
		cerr<<check(S2)<<endl;
	*/
		if(S1&&S2&&check(S1)&&check(S2)){
			tot++;
			cnt[S1]++;
			cnt[S2]++;
		}
		return ;
	}
	dfs(i+1,S1|(1<<i),S2);
	dfs(i+1,S1,S2|(1<<i));
}
int main(){
	for(int i=0;i<20;i++)inv[1<<i]=i;
	int T;scanf("%d",&T);
	for(int t=1;t<=T;t++){
		scanf("%d%d",&n,&m);
		
		tot=0;
		
		for(int i=0;i<n;i++){
			adj[i]=0;
		}
		for(int i=0;i<(1<<n);i++){
			cnt[i]=0;
			con[i]=0;
			vis[i]=0;
		}
		for(int i=0;i<n;i++){
			con[1<<i]=1;
			vis[1<<i]=1;
		}
		for(int i=0;i<m;i++){
			int u,v;scanf("%d%d",&u,&v);
			e[i]=(1<<u)|(1<<v);
			adj[u]|=1<<v;
			adj[v]|=1<<u;
		}
		
		
		dfs(1,1,0);
		
		
		for(int i=0;i<n;i++){
			for(int j=0;j<(1<<n);j++){
				if(j&(1<<i))
					cnt[j^(1<<i)]+=cnt[j];
			}
		}
		printf("Case #%d:",t);
		for(int i=0;i<m;i++)printf(" %d",tot-cnt[e[i]]);
		puts("");
	}
	return 0;
}

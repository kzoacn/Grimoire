#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<cmath>
using namespace std;
int n,m;
vector<int>G[233];
int main(){
	while(scanf("%d%d",&n,&m)==2){
		if(!n)break;
		for(int i=1;i<=n;i++)G[i].clear();
		for(int i=1;i<=n;i++)		
		for(int j=1;j<=n;j++){
			int x,y;scanf("%d%d",&x,&y);
			G[x].push_back(y);
		}
		for(int i=1;i<=n;i++)sort(G[i].begin(),G[i].end());
		int ans=1e9;
		for(int i=1;i<=m-n+1;i++){
			int res=0;
			for(int j=1;j<=n;j++){
				int now=i;
				for(int k=0;k<G[j].size();k++){
					int y=G[j][k];
					res+=abs(now-y);
					now++;
				}
			}
			ans=min(ans,res);
		}printf("%d\n",ans);
	}
	return 0;
}

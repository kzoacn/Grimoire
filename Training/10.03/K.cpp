#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int mp[44][44],a[44][44];
int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)==2&&n){
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(i!=j)
			a[i][j]=inf;
		while(m--){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			a[u][v]=min(a[u][v],w);
			a[v][u]=min(a[v][u],w);
		}
		int ans=0;
		for(int u=2;u<n;u++){
			for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				mp[i][j]=a[i][j];
				if(i==u||j==u)mp[i][j]=inf;
			}
			
			for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
			
				
				
			ans=max(ans,mp[1][n]);
		}
		if(ans==inf)puts("Inf");
		else printf("%d\n",ans);
	}
	return 0;
}

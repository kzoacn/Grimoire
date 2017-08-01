#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m;
pair<LL,int>mp[333][333];
const LL inf=1LL<<61;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)mp[i][j]=make_pair(0LL,0);
			else mp[i][j]=make_pair(inf,0);
		}
	}
	for(int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		mp[u][v]=mp[v][u]=min(mp[u][v],make_pair(w*1ll,1));
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if(mp[i][k].first!=inf&&mp[k][j].first!=inf)
			mp[i][j]=min(mp[i][j],make_pair(mp[i][k].first+mp[k][j].first,mp[i][k].second+mp[k][j].second));
	}
	double tot=0,cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			cnt+=mp[i][j].second;
			tot++;
		}
	}
	printf("%.10f\n",cnt/tot);
	return 0;
}

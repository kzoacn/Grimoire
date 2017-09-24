#include<bits/stdc++.h>
using namespace std;
const int maxn=111;
int n,m;
vector<int>G[maxn];
long long a[maxn];
int s,t;
int main(){
	cin>>n>>m>>s>>t;
	s++;
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		u++;v++;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	a[s]=1;
	while(t--){
		static long long na[maxn];
		memset(na,0,sizeof na);
		for(int i=1;i<=n;i++){
			for(int j=0;j<G[i].size();j++){
				int v=G[i][j];
				na[v]+=a[i];
			}
		}
		for(int i=1;i<=n;i++)
			a[i]=na[i];
	}
	cout<<accumulate(a+1,a+1+n,0LL)<<endl;
	return 0;
}

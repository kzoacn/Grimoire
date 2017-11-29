#include<bits/stdc++.h>
using namespace std;
const int maxn=101;

string name[maxn];
double x[maxn],y[maxn],z[maxn];
double mp[maxn][maxn];
map<string,int>M;

int main(){
	int T;cin>>T;
	while(T--){
		M.clear();
		int n,m;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>name[i];
			M[name[i]]=i;
			scanf("%lf%lf%lf",&x[i],&y[i],&z[i]);
		}
		
		auto sqr=[](double x){return x*x;};
		
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mp[i][j]=sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])+sqr(z[i]-z[j]));
		cin>>m;
		for(int i=1;i<=m;i++){
			string a,b;
			cin>>a>>b;
			int u=M[a],v=M[b];
			mp[u][v]=0;
		}
		for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
		int q;cin>>q;
		static int t=0;
		printf("Case %d:\n",++t);
		while(q--){
			string a,b;
			cin>>a>>b;
			int u=M[a],v=M[b];
			printf("The distance from %s to %s is %.0f parsecs.\n",a.c_str(),b.c_str(),mp[u][v]);
		}
	}
	return 0;
}

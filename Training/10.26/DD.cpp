#include <bits/stdc++.h>

using namespace std;

int n, m;

bool del[505], edge[505][505];

bool g[505][505];

namespace MC{
	int main(){
		int T=5;
		static int id[505];
		for(int i=1;i<=min(n,30);i++)id[i]=i;
		static int now[505];
		int cur=0,ans=0;
		while(T--){
			cur=0;
			for(int j=1;j<=min(n,30);j++){
				int ok=1;
				int x=id[j];
				for(int i=1;i<=cur;i++)if(!g[now[i]][x]){
					ok=0;
					break;
				}
				
				if(ok){
					now[++cur]=x;
				}
			}
			for(int i=31;i<=n;i++){
				int ok=1;
				int x=i;
				for(int i=1;i<=cur;i++)if(!g[now[i]][x]){
					ok=0;
					break;
				}
				
				if(ok){
					now[++cur]=x;
				}
			}
			random_shuffle(id+1,id+1+min(n,30));
			ans=max(ans,cur);
		}
		return ans;
	}
}

int main() {
srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while (cin >> n >> m) {
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(i!=j)
			g[i][j]=1;
		
		for (int i = 1; i <= m; ++i) {
			static int u, v;
			
			cin >> u >> v;
			
			g[u][v]=g[v][u]=0;
			
		}
		
		cout << n - MC::main() << endl;
	}
	
	return 0;
}

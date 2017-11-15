#include <bits/stdc++.h>

using namespace std;

int n, m;

bool del[505], edge[505][505];

bool g[505][505];

namespace MC {
	int len[505], mc[505], list[505][505];
	
	int ans;
	
	bool found;
	
	void DFS(int size) {
		int i,j,k;
		if (len[size] == 0) {
			if (size > ans) {
				ans = size; found = true;
			}
			return;
		}
		for (k = 0; k < len[size] && !found; ++k) {
			if (size + len[size] - k <= ans) break;
			i = list[size][k];
			if (size + mc[i] <= ans) break;
			len[size + 1] = 0;
			for (j = k + 1; j < len[size]; ++j)
				if (g[i][list[size][j]]) list[size + 1][len[size + 1]++] = list[size][j];
			DFS(size + 1);
		}
	}
	
	int main() {
	
		if(n<=30){
			ans = 0;
			mc[n] = ans = 1;
		
			for (int i = n - 1; i; --i) {
				found = 0;
				len[1] = 0;
				for (int j = i + 1; j <= n; ++j)
					if (g[i][j]) list[1][len[1]++] = j;
				DFSs(1);
				mc[i] = ans;
				//cerr<<i<<" "<<mc[i]<<endl;
			}
			return ans;
		}else{
			ans = 0;
			for (int i = 31; i <= n; ++i) {
				mc[i] = n - i + 1;
			}
			ans = n - 30;
//			n = 31;
			for (int i = 30; i; --i) {
				found = 0;
				len[1] = 0;
				for (int j = i + 1; j <= n; ++j)
					if (g[i][j]) list[1][len[1]++] = j;
				DFS(1);
				mc[i] = ans;
				//cerr<<i<<" "<<mc[i]<<endl;
			}
			return ans;
		
		}
	}
}

int main() {
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

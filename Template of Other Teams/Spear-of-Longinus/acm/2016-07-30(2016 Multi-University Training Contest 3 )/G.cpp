#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 200005;
const int INF = 999999999;

int Case, n, Root;
int deg[N], fa[N], cnt[N];
int f[N][3][2];

vector<int> G[N];

void Prep(int x){
	cnt[x] = 0;
	
	int child = 0;
	
	for (int i = 0; i < G[x].size(); i++){
		int y = G[x][i];
		if (y == fa[x]) continue;
		
		fa[y] = x;
		Prep(y);
		child++;
		cnt[x] += cnt[y];
	}
	if (child == 0) cnt[x] = 1;
}

int dp(int x, int times, int use){
	
	if (f[x][times][use] != -1) return f[x][times][use];
	
	int Ans0 = 0;
	//printf("%d %d\n", x, Ans0);
	for (int i = 0; i < G[x].size(); i++){
		int y = G[x][i];
		if (y == fa[x]) continue;
		
		if (cnt[y] & 1) Ans0 += dp(y, 1, 0) + 1;
		else Ans0 += dp(y, 2, 0) + 2;
	}
	
	if (use){
		int Ans1 = INF;
		for (int i = 0; i < G[x].size(); i++){
			int y = G[x][i];
			if (y == fa[x]) continue;
			
			if (cnt[y] & 1){ // 1 to 2
				if (cnt[y] == 1) Ans1 = min(Ans1, Ans0); else
				Ans1 = min(Ans1, Ans0 + dp(y, 2, 1) + 2 - (dp(y, 1, 0) + 1));
			}else // 2 to 1
				Ans1 = min(Ans1, Ans0 + dp(y, 1, 1) + 1 - (dp(y, 2, 0) + 2));
		}
		Ans0 = Ans1;
	}
	
	f[x][times][use] = Ans0;
	return Ans0;
}

int main(){
	
	int Case;
	scanf("%d", &Case);
	
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d", &n);
		
		for (int i = 1; i <= n; i++){
			G[i].clear();
			deg[i] = 0;
			fa[i] = 0;
		}
		
		for (int i = 1; i <= n - 1; i++){
			int u , v;
			scanf("%d%d", &u, &v);
			G[u].push_back(v); deg[v]++;
			G[v].push_back(u); deg[u]++;
		}
		
		if (n == 2){
			printf("1\n");
			continue;
		}
		
		if (n == 1){
			printf("0\n");
			continue;
		}
		
		Root = -1;
		for (int i = 1; i <= n; i++)
			if (deg[i] != 1) {
				Root = i;
				break;
			}
		
		
		Prep(Root);
		
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= 2; j++)
				for (int k = 0; k <= 1; k++)
					f[i][j][k] = -1;
		
		printf("%d\n", dp(Root, 0, cnt[Root] & 1));
	}
	
	return 0;
}

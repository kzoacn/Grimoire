#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 55;
const int dx[2] = {0, 1};
const int dy[2] = {1, 0};

char map[N][N];

vector<pair<int, int> > G[N][N];

int f[N][N][N][N][2][2];
int Vis[N][N];
int Time;


int n, m;


void Solve(int x, int y, int sx, int sy){

	
	if (Vis[x][y] == Time) return;
	Vis[x][y] = Time;

	if (map[x][y] >= 'A' && map[x][y] <= 'Z' && map[x][y] - 'A' == map[sx][sy] - 'a'){
		G[sx][sy].push_back(make_pair(x, y));
	}
	
	if (x == n && y == m) return;
	for (int i = 0; i <= 1; i++){
		int xx = x + dx[i];
		int yy = y + dy[i];
		if (xx > n || yy > m) continue;
		if (map[xx][yy] == '#') continue;
		
		Solve(xx, yy, sx, sy);
	}
}

void Dfs(int x, int y){
	
	if (Vis[x][y] == Time) return;
	Vis[x][y] = Time;

	for (int i = 0; i <= 1; i++){
		int xx = x + dx[i];
		int yy = y + dy[i];
		if (xx > n || yy > m) continue;
		if (map[xx][yy] == '#') continue;
		
		Dfs(xx, yy);
	}
}

int Work(int x0, int y0, int x1, int y1, int use, int use1){
	if (f[x0][y0][x1][y1][use][use1] != -2)
		return f[x0][y0][x1][y1][use][use1];
	
	if (x0 == x1 && y0 == y1) return 0;
	
	
	f[x0][y0][x1][y1][use][use1] = -1;
	
	for (int i = 0; i <= 1; i++){
		int xx = x0 + dx[i];
		int yy = y0 + dy[i];
		if (xx > x1 || yy > y1) continue;
		if (map[xx][yy] == '#') continue;
			
		int Ret = Work(xx, yy, x1, y1, 0, use1);
		if (Ret > f[x0][y0][x1][y1][use][use1]) {
			f[x0][y0][x1][y1][use][use1] = Ret;
		}
	}
		
	for (int i = 0; i < G[x0][y0].size(); i++){
		int xx = G[x0][y0][i].first;
		int yy = G[x0][y0][i].second;
			
		if (xx == x1 && yy == y1 && use1 == 1) continue;
		if (xx > x1 || yy > y1) continue;
		if (use == 1) continue;
		
		int Ret = Work(x0, y0, xx, yy, 1, 1);
		int Tmp = Work(xx, yy, x1, y1, 0, use1);
		
			
			if (Tmp + Ret + 1 > f[x0][y0][x1][y1][use][use1]){
				f[x0][y0][x1][y1][use][use1] = Tmp + Ret + 1;
			}
			
	}
	
	return f[x0][y0][x1][y1][use][use1];
}

int main(){
	
	Time = 0;
	memset(Vis, 0, sizeof(Vis));
	
	while (scanf("%d%d", &n, &m) == 2){
		if (n == 0 && m == 0) break;
		
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				G[i][j].clear();
		
		for (int i = 1; i <= n; i++){
			scanf("%s", map[i] + 1);
		}
		
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if (map[i][j] >= 'a' && map[i][j] <= 'z'){
					++Time;
					Solve(i, j, i, j);
				}
			}
		}
		
		++Time;
		if (map[1][1] != '#'){
			Dfs(1, 1);
		}
		
		if (Vis[n][m] != Time){
			puts("-1");
			continue;
		}
		
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				for (int k = 1; k <= n; k++)
					for (int l = 1; l <= m; l++)
						for (int t = 0; t <= 1; t++)
							for (int p = 0; p <= 1; p++)
								f[i][j][k][l][t][p] = -2;
		
		int Ans = Work(1, 1, n, m, 0, 0);
		printf("%d\n", Ans);
	}
	
	return 0;
}

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int N = 200005;

vector<int> G[N], E[N];

int n, m, tot, dfc, Root, cnt, block, Q;
int g[N], adj[N * 2], nxt[N * 2];
int dfn[N], belong[N], low[N], Real_dep[N], stack[N], dep[N];
int fa[N][16];
bool Vis[N], iscut[N];

void Ins(int x, int y){
	adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot;
	adj[++tot] = x; nxt[tot] = g[y]; g[y] = tot;
}

void Dfs(int x, int lst){
	dfn[x] = ++dfc;
	low[x] = dfn[x];
	stack[++cnt] = x;
	int son = 0;
	for (int i = g[x]; i; i = nxt[i]){
		if (!dfn[adj[i]]){
			++son;
			Dfs(adj[i], i);
			low[x] = min(low[x], low[adj[i]]);
			if (low[adj[i]] >= dfn[x]){
				int Tmp;
				iscut[x] = 1;
				++block;
				E[x].push_back(block + n + m);
				do{
					Tmp = stack[cnt--];
					belong[Tmp] = block;
					E[Tmp].push_back(block + n + m);
				}while (Tmp != adj[i]);
				belong[x] = block;
			}
		}
		else
		if (((i) ^ (lst)) != 1) low[x] = min(low[x], dfn[adj[i]]);
	}
	if (x == Root && son == 1) iscut[x] = 0;
}

void Prepare(int x, int Fa){
	Vis[x] = 1;
	Real_dep[x] = Real_dep[Fa] + 1;
	dep[x] = dep[Fa] + (x <= n);
	for (int i = 0; i < (int)G[x].size(); i++){
		int y = G[x][i];
		if (y == Fa) continue;
		fa[y][0] = x;
		for (int j = 1; j <= 15; j++)
			fa[y][j] = fa[fa[y][j - 1]][j - 1];
		Prepare(y, x);
	}
}

int lca(int x, int y){
	if (Real_dep[x] < Real_dep[y]) swap(x, y);
	for (int i = 15; i >= 0; i --)
		if (Real_dep[fa[x][i]] >= Real_dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 15; i >= 0; i --)
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

int Get(int x){
	for (int i = 15; i >= 0; i --)
		if (Real_dep[fa[x][i]]) x = fa[x][i];
	return x;
}

int main(){
	
	while (1){
		scanf("%d%d", &n, &m);
		if (!n && !m) break;
		
		tot = 1;
		cnt = 0;
		block = 0;
		for (int i = 1; i <= n + n + m; i++) g[i] = dfn[i] = iscut[i] = 0;
		for (int i = 1; i <= n + n + m; i++){
			G[i].clear();
			E[i].clear();
			belong[i] = 0;
			low[i] = dfn[i] = 0;
		}
		
		for (int i = 1; i <= m; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			Ins(x, i + n);
			Ins(i + n, y);
		}
		
		dfc = 0;
		for (int i = 1; i <= n; i++)
			if ( dfn[i] == 0 ){
				Root = i;
				Dfs(i, 0);
			} 
		
		for (int i = 1; i <= n + m; i++)
			if (iscut[i]){
				for (int j = 0; j < E[i].size(); j++){
						G[i].push_back(E[i][j]);
						G[E[i][j]].push_back(i);
					}
			}
		
		for (int i = 1; i <= n + m + block; i++) Vis[i] = 0;
		
		Real_dep[0] = dep[0] = 0;
		
		for (int i = 1; i <= n + m + block; i++){
			if (belong[i] && !iscut[i]) continue;
			if (Vis[i]) continue;
			for (int j = 0; j <= 15; j++)
				fa[i][j] = 0;
			Prepare(i,0);
		}
		
		scanf("%d", &Q);
		for (int ii = 1; ii <= Q; ii++){
			int x, y;
			scanf("%d%d", &x, &y);
			int xx = iscut[x + n] ? x + n : belong[x + n] + n + m;
			int yy = iscut[y + n] ? y + n : belong[y + n] + n + m;
			if (Get(xx) != Get(yy)) printf("0\n");
			else {
				int Lca = lca(xx,yy);
				printf("%d\n", dep[xx] + dep[yy] - 2 * dep[Lca]+ (Lca <= n));
			}
		}
		
	}
	
	return 0;
}



#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 300005;
const int S = N * 8;
const int T = S * 2;

int Case, n, m, dfc, Rev, tot;
int fa[N][20];
int dfn[N], ri[N], dep[N], same[N];

vector<int> G[N];

struct node{
	int pos, l, r, w;
}Q[T];

struct node1{
	int Max, add;
}tree[N * 4];

void Prep(int x, int Fa){
	++dfc;
	dfn[x] = dfc;
	dep[x] = dep[Fa] + 1;
	
	fa[x][0] = Fa;
	for (int i = 1; i <= 19; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	
	for (int i = 0; i < G[x].size(); i++){
		int y = G[x][i];
		if (y == Fa) continue;
		
		Prep(y, x);
	}
	ri[x] = dfc;
}

void Add(int x1, int x2, int y1, int y2, int w){
	if (x1 > x2 || y1 > y2) return;
	//printf("%d %d %d %d %d\n", x1, x2, y1, y2, w);
	//if (!y1 && !y2) printf("%d\n", tot);
	
	// Add
	++tot;
	Q[tot].pos = x1;
	Q[tot].l = y1;
	Q[tot].r = y2;
	Q[tot].w = w;
	
	// Delete
	++tot;
	Q[tot].pos = x2 + 1;
	Q[tot].l = y1;
	Q[tot].r = y2;
	Q[tot].w = - w;
	
}

bool cmp(node a, node b){
	return a.pos < b.pos;
}

int Get(int x, int y){
	if (dep[y] > dep[x]) swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	
	if (x == y) return x;
	for (int i = 19; i >= 0; i--)
		if (fa[x][i] != fa[y][i]){
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}

int Jump(int x, int step){
	for (int i = 19; i >= 0; i--)
		if (step >= (1 << i)){
			step -= (1 << i);
			x = fa[x][i];
		}
	return x;
}

void Build(int s, int x, int y){
	tree[s].Max = tree[s].add = 0;
	if (x == y) return;
	int mid = (x + y) >> 1;
	int t = s + s;
	
	Build(t, x, mid);
	Build(t + 1, mid + 1, y);
}

void push(int s){
	if (tree[s].add == 0) return;
	int t = s + s;
	tree[t].Max += tree[s].add;
	tree[t].add += tree[s].add;
	
	tree[t + 1].Max += tree[s].add;
	tree[t + 1].add += tree[s].add;
	
	tree[s].add = 0;
}

void Change(int s, int x, int y, int l, int r, int w){
	if (x == l && y == r){
		tree[s].Max += w;
		tree[s].add += w;
		return;
	}
	
	if (x != y) push(s);
	int mid = (x + y) >> 1;
	int t = s + s;
	
	if (r <= mid) Change(t, x, mid, l, r, w);
	else
	if (l > mid) Change(t + 1, mid + 1, y, l, r, w);
	else {
		Change(t, x, mid, l, mid, w);
		Change(t + 1, mid + 1, y, mid + 1, r, w);
	}
	
	tree[s].Max = max(tree[t].Max, tree[t + 1].Max);
}

int main(){
	freopen("G.in", "r", stdin);
	scanf("%d", &Case);
	
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d%d", &n, &m);
		
		for (int i = 1; i <= n; i++) G[i].clear();
		
		for (int i = 1; i <= n - 1; i++){
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		dfc = 0;
		dep[0] = 0;
		Prep(1, 0);
		tot = 0;
		
		
		//for (int i = 1; i <= n; i++)
		//	printf("%d %d\n", i, dfn[i]);
		
		for (int i = 1; i <= n; i++) same[i] = 0;
		
		Rev = 0;
		for (int i = 1; i <= m; i++){
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if (u == v){
				same[u] += w;
				Rev += w;
			} else {
				int Lca = Get(u, v);
				if (Lca != u && Lca != v){
					Add(dfn[u], ri[u], dfn[v], ri[v], w);
					continue;
				}
				if (Lca == u){
					int d = Jump(v, dep[v] - dep[Lca] - 1);
					//if (i == 7) printf("%d\n", tot);
					//printf("%d %d %d\n",i, dfn[d], ri[v]);
					
					//if (i == 7){
					//	printf("%d %d %d %d\n", 1, dfn[d] - 1, dfn[v], ri[v]);
					//	printf("%d %d %d %d\n", dfn[d] + 1, n, dfn[v], ri[v]);
					//	printf("%d\n", tot);
					//}
					
					Add(1, dfn[d] - 1, dfn[v], ri[v], w);
					Add(ri[d] + 1, n, dfn[v], ri[v], w); 
					//if (i == 7) printf("%d\n", tot);
					
					continue;
				}
				if (Lca == v){
					int d = Jump(u, dep[u] - dep[Lca] - 1);
					
					//if (i == 2) puts("ok");
					//if (i == 2){
					//	printf("%d %d %d\n", d, dfn[d], ri[d]);
					//}
					
					Add(dfn[u], ri[u], 1, dfn[d] - 1, w);
					Add(dfn[u], ri[u], ri[d] + 1, n, w);
					continue;
				}
			}
		}
		
		for (int i = 1; i <= n; i++){
			if (same[i] == 0) continue;
			
			for (int p = 0; p < G[i].size(); p++){
				int To = G[i][p];
				
				if (To == fa[i][0]) continue;
				
				Add(dfn[To], ri[To], dfn[To], ri[To], -same[i]);
				
			}
			
			Add(1, dfn[i] - 1, 1, dfn[i] - 1, - same[i]);
			Add(1, dfn[i] - 1, ri[i] + 1, n, - same[i]);
			Add(ri[i] + 1, n, 1, dfn[i] - 1, - same[i]);
			Add(ri[i] + 1, n, ri[i] + 1, n, - same[i]);
			
		}
		
		Build(1, 1, n);
		
		sort(Q + 1, Q + 1 + tot, cmp);
		int Ans = -999999999;
		
		//puts("OK!");
		//for (int i = 1; i <= tot; i++)
		//	printf("%d %d\n", i, Q[i].l, Q[i].r);
		//printf("%d\n", tot);
		for (int i = 1, j = i; i <= tot; i = j){
			while (j <= tot && Q[j].pos == Q[i].pos){
				//printf("%d %d %d %d\n", i, j, Q[j].l, Q[j].r);
				Change(1, 1, n, Q[j].l, Q[j].r, Q[j].w);
				j++;
			}
			//printf("%d %d\n", i, j - 1);
			//printf("%d %d %d %d\n", i, j, Q[i].pos, tree[1].Max);
			if (Q[i].pos <= n)
			Ans = max(Ans, Rev + tree[1].Max);
		}
		
		if (n == 1) Ans = same[1];
		
		printf("Case #%d: %d\n", ii, Ans);
		
	}
	
	return 0;
}

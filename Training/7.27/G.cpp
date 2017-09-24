#include <bits/stdc++.h>

using namespace std;


int n;
bool edge[105][105];
int cnt = 0;
int col[1111], can[1111][11], deg[1111], adj[111], id[1111], ans[111];

struct Edge {
	int v, nxt;
} e[111111];

std::string LINE;
std::stringstream ss;

inline void addedge(int u, int v) {
//cout << u << " -------- " << v << endl;
	e[++cnt].v = v;
	e[cnt].nxt = adj[u];
	adj[u] = cnt;
}

inline bool cmp_deg(int p, int q) {
	return deg[p] > deg[q];
}

inline bool dfs(int dep) {
	if (dep > n) {
		return true;
	}
	/*if (dep == 1) {
		col[1] = 1;
		return dfs(dep + 1);
	}*/
	for (int i = 1; i <= 4; ++i) {
		if (can[dep][i]) {
			continue;
		}
		col[dep] = i;
		for (int p = adj[dep]; p; p = e[p].nxt) {
		//if (dep == 6) cout << e[p].v << endl;
			can[e[p].v][i]++;
		}
		if (dfs(dep + 1)) {
			return true;
		}
		for (int p = adj[dep]; p; p = e[p].nxt) {
			can[e[p].v][i]--;
		}
	}
	return false;
}

int main() {
	int cs = 0;
	while (~scanf("%d", &n)) {
		if (cs++ > 0) {
			puts("");
		}
		getchar();
		memset(edge, 0, sizeof edge);
		
		int u, v;
		while (1) {
			std::getline(std::cin, LINE);
			if (LINE.length() == 0) break;
			ss = std::stringstream(LINE);
			ss >> u >> v; v = -v;
			edge[u][v] = edge[v][u] = 1;
			//cout << u << " " << v << endl;
		}
		
		for (int i = 1; i <= n; ++i) {
			adj[i] = 0;
			deg[i] = 0;
			for (int j = 1; j <= 4; ++j) {
				can[i][j] = 0;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i != j && edge[i][j]) {
					//addedge(i, j);
					++deg[i];
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			id[i] = i;
		}
		sort(id + 1, id + n + 1, cmp_deg);
//for (int i = 1; i <= n; ++i) cout << deg[i] << " "; cout << endl;
//for (int i = 1; i <= n; ++i) cout << id[i] << " "; cout << endl;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1 + i; j <= n; ++j) {
				if (edge[id[i]][id[j]]) {
				//	if (id[i] == 6 && id[j] == 7) cout << i << " -------- " << j << endl;
					addedge(i, j);
				}
			}
		}
		if (dfs(1)) {
			for (int i = 1; i <= n; ++i) {
				ans[id[i]] = col[i];
			}
			/*for (int i = 1; i <= n; ++i) {
				for (int j = 1 + i; j <= n; ++j) {
				if (edge[i][j]) cout << i << " " << j << endl;
					assert(!edge[i][j] || ans[i] != ans[j]);
				}
			}*/
			for (int i = 1; i <= n; ++i) {
				printf("%d %d\n", i, ans[i]);
			}
		} else {
			while (1) {
				puts("fuck");
			}
		}
	}
	
	return 0;
}

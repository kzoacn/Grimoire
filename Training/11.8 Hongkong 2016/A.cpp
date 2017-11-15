#include <bits/stdc++.h>

const int MAXN = 100 + 5;

int n, m, k;
std::vector<int> G[MAXN];
int depth[MAXN], fa[MAXN];

int col[MAXN], aimCol[MAXN];
std::set<int> S, T;
int cnts[MAXN], cntt[MAXN];

int CNT = 0;

void print() {
	static std::vector<int> Last(MAXN, -1);
	
	for (int i = 1; i <= n; ++i) {
		if (col[i] != Last[i]) goto YESPRINT;
	}
	
	return;
	
	YESPRINT:
	
	assert(++CNT <= 20000);
	
#ifdef LOCAL
	for (int i = 1; i <= n; ++i) {
		if (Last[i] == -1 || col[i] == Last[i]) continue;
		bool flag = 0;
		for (int to: G[i])
			if (col[i] == Last[to]) {
				flag = 1; break;
			}
		if (flag) continue;
		std::cerr << "Invalid Move!!" << std::endl;
		assert(0);
	}
#endif
	
	for (int i = 1; i <= n; ++i)
		printf("%d%c", Last[i] = col[i], " \n"[i == n]);
}

void DFS(int now) {
	for (int to: G[now]) {
		if (to == fa[now]) continue;
		fa[to] = now;
		depth[to] = depth[now] + 1;
		DFS(to);
	}
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) std::swap(u, v);
	while (depth[u] != depth[v]) u = fa[u];
	while (u != v)
		u = fa[u], v = fa[v];
	return u;
}

void MoveTo(int u, int v) {
	int lca = LCA(u, v);
	while (u != lca) {
		std::swap(col[u], col[fa[u]]);
		print();
		u = fa[u];
	}
	static std::vector<int> List;
	List.clear();
	while (v != lca) {
		List.push_back(v);
		v = fa[v];
	}
	for (auto it = List.rbegin(); it != List.rend(); ++it) {
		std::swap(col[u], col[*it]);
		print();
		u = *it;
	}
}

void CopyTo(int u, int v) {
	int lca = LCA(u, v);
	if (lca == v) {
		int uu = u;
		while (fa[uu] != v) uu = fa[uu];
		MoveTo(u, uu);
		u = uu;
	}
	else {
		MoveTo(u, fa[v]);
		u = fa[v];
	}
	
	col[v] = col[u];
	print();
}

bool vis[MAXN];

void DFS2(int now) {
	for (int to: G[now]) {
		if (to == fa[now]) continue;
		DFS2(to);
	}
	vis[now] = 1;
	if (col[now] == aimCol[now]) return;
//	std::cerr << "Need moving: " << now << std::endl;
	for (int i = 1; i <= n; ++i) if (!vis[i] && col[i] == aimCol[now]) {
		MoveTo(i, now);
//		std::cerr << "MoveTo: " << i << " " << now << std::endl;
		break;
	}
}

int Fa(int x) {
	return fa[x] == x ? x : fa[x] = Fa(fa[x]);
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", col + i);
		S.insert(col[i]);
		++cnts[col[i]];
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", aimCol + i);
		T.insert(aimCol[i]);
		++cntt[aimCol[i]];
	}
	
	for (int i: T) if (!S.count(i))
		return puts("Impossible"), 0;
	
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		static int u, v;
		
		scanf("%d%d", &u, &v);
		if (Fa(u) != Fa(v)) {
			fa[fa[u]] = fa[v];
			G[u].push_back(v);
			G[v].push_back(u);
		}
	}
	
	memset(fa, 0, sizeof fa);
	DFS(1);
	print();
	
	/*for (auto it_s = S.begin(), it_t = T.begin(); it_s != S.end(); ++it_s, ++it_t) {
		if (*it_s != *it_t) {
			for (int i = 1; i <= n; ++i) if (col[i] == *it_s) {
				for (int j = 1; j <= n; ++j) if (col[j] == *it_t) {
//					std::cerr << "CopyTo: " << j << " " << i << std::endl;
					CopyTo(j, i);
//					std::cerr << "End of CopyTo()" << std::endl;
					break;
				}
				break;
			}
		}
	}*/
	
	for (int i = 0; i < k; ++i)
		for (int j = 0; cntt[i] > cnts[i] && j < k; ++j) while (cntt[i] > cnts[i] && cnts[j] > cntt[j]) {
			for (int x = 1; x <= n; ++x) if (col[x] == i) {
				for (int y = 1; y <= n; ++y) if (col[y] == j) {
					CopyTo(x, y);
					++cnts[i];
					--cnts[j];
					break;
				}
				break;
			}
//			std::cerr << cntt[i] << " " << cnts[i] << std::endl;
		}
	
	DFS2(1);
	
	for (int i = 1; i <= n; ++i)
		if (col[i] != aimCol[i])
			while (1) puts("cnbb");
	
	return 0;
}

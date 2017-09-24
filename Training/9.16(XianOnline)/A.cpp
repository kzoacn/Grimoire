#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef unsigned long long ull;
const int Mod = 19260817;

int pw19[65], pw26[65];

int n, m;

struct Matrix {
//	bool mat[65][65];
	ull mat[64];
	
	__advance void clear() {
		memset(mat, 0, sizeof mat);
	}
	
	Matrix() {
		clear();
	}
	
	__advance Matrix rotate() const {
		Matrix res;
		for (int i = 0; i < 64; ++i)
			for (int j = 0; j < 64; ++j) {
				res.mat[j] |= ((ull)((bool)(mat[i] & (1ull << j))) << i);
			}
		return res;
	}
	
	__advance Matrix operator * (const Matrix &rhs) const {
		Matrix res, tmp = rhs.rotate();
		for (int i = 0; i < 64; ++i)
			for (int j = 0; j < 64; ++j) {
				ull t = mat[i] & tmp.mat[j];
				res.mat[i] |= ((ull)(__builtin_popcountll(t) & 1) << j);
			}
		return res;
	}
	
	__advance void unit() {
		clear();
		for (int i = 0; i < 64; ++i)
			mat[i] |= (1ull << i);
	}
	
	__advance int calc() {
		int ans = 0;
		for (int i = 1; i <= 64; ++i)
			for (int j = 1; j <= 64; ++j)
				ans = (ans + 1ll * (bool)(mat[i - 1] & (1ull << (j - 1))) * pw19[i] * pw26[j]) % Mod;
		return ans;
	}
} mt[3005];

std::vector<int> G[3005];

int anc[3005][12], depth[3005];
Matrix up[3005][12], down[3005][12];

__advance void DFS(int now) {
	up[now][0] = down[now][0] = mt[now];
	for (int i = 1; i < 12; ++i) {
		anc[now][i] = anc[anc[now][i - 1]][i - 1];
		up[now][i] = up[now][i - 1] * up[anc[now][i - 1]][i - 1];
		down[now][i] = down[anc[now][i - 1]][i - 1] * down[now][i - 1];
	}
	for (int to: G[now]) {
		if (to == anc[now][0]) continue;
		depth[to] = depth[now] + 1;
		anc[to][0] = now;
		DFS(to);
	}
}

__advance int LCA(int u, int v) {
	if (depth[u] < depth[v]) std::swap(u, v);
	int tmp = depth[u] - depth[v];
	for (int i = 0; i < 12; ++i)
		if ((1 << i) & tmp) u = anc[u][i];
	for (int i = 11; i >= 0; --i) {
		int x = anc[u][i], y = anc[v][i];
		if (x == y) continue;
		u = x, v = y;
	}
	return u == v ? u : anc[u][0];
}

__advance int main() {
	pw19[0] = pw26[0] = 1;
	for (int i = 1; i <= 64; ++i) {
		pw19[i] = pw19[i - 1] * 19 % Mod;
		pw26[i] = pw26[i - 1] * 26 % Mod;
	}
	
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; ++i) std::vector<int>().swap(G[i]);
		
		for (int u, v, i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		ull seed;
		std::cin >> seed;
		
		for (int i = 1; i <= n; ++i) {
			mt[i].clear();
			for (int p = 1; p <= 64; ++p) {
				seed ^= seed * seed + 15;
				for (int q = 1; q <= 64; ++q)
					mt[i].mat[p - 1] |= ((ull)(seed >> (q - 1)) & 1) << (q - 1);
			}
		}
		
		DFS(1);
		
		for (int u, v; m--; ) {
			scanf("%d%d", &u, &v);
			int lca = LCA(u, v);
			
			Matrix t1, t2; t1.unit(); t2.unit();
			
			int tmp = depth[u] - depth[lca] + 1;
			for (int i = 0; i < 12; ++i)
				if ((1 << i) & tmp) {
					t1 = t1 * up[u][i];
					u = anc[u][i];
				}
			tmp = depth[v] - depth[lca];
			for (int i = 0; i < 12; ++i)
				if ((1 << i) & tmp) {
					t2 = down[v][i] * t2;
					v = anc[v][i];
				}
			
			printf("%d\n", (t1 * t2).calc());
		}
	}
	
	return 0;
}

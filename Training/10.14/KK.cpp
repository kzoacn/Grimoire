#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

int n, m;

int deg[200005];

int fa[200005];

int Fa(int x) {
	return fa[x] == x ? x : fa[x] = Fa(fa[x]);
}

struct Edge {
	int u, v;
	
	__advance __inline void scan() {
		scanf("%d%d", &u, &v);
		++deg[u];
		++deg[v];
	}
} edge[500005];

__advance __inline bool check(int x) {
	for (int i = 1; i <= n; ++i) fa[i] = i;
	
	for (int i = 1; i <= m; ++i) {
		if (edge[i].u != x && edge[i].v != x) {
			int u = edge[i].u, v = edge[i].v;
			if (Fa(u) == Fa(v)) return 0;
			fa[fa[u]] = fa[v];
		}
	}
	return 1;
}

std::vector<int> ans;

__advance int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
		edge[i].scan();
	
	int maxdeg = 0;
	
	for (int i = 1; i <= n; ++i) {
		if (deg[i] & 1) {
			puts("0");
			return 0;
		}
		maxdeg = std::max(maxdeg, deg[i]);
	}
	
	if (n == m) {
		printf("%d\n", n);
		for (int i = 1; i <= n; ++i)
			printf("%d%c", i, " \n"[i == n]);
	}
	else {
		for (int i = 1; i <= n; ++i) if (deg[i] == maxdeg) {
			if (check(i)) ans.push_back(i);
		}
		
		printf("%d\n", (int)ans.size());
		for (int i = 0; i < (int)ans.size(); ++i)
			printf("%d%c", ans[i], " \n"[i == (int)ans.size() - 1]);
	}
	
	return 0;
}

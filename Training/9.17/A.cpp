#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int testcase, n, m, s, t, cnt;
int adj[MAXN];

inline void addedge(int u, int v, int w) {
	e[++cnt].v = v;
	e[cnt].
}

int main() {
	cin >> testcase;
	for (; testcase; --testcase) {
		scanf("%d%d", &n, &m);
		scanf("%d%d", &s, &t);
		memset(adj, cnt = -1, sizeof(*adj) * (n + 1));
		for (int i = 1; i <= m; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
		}
	}
}

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;

const int MAXN = 111111;
int deg[MAXN], adj[MAXN];
LL dist[MAXN], k[MAXN], b[MAXN];
int n, m, cnt;

struct Edge {
	int v, nxt;
} e[MAXN];

struct E {
	int u, v;
} edge[MAXN];

inline int upper(int a, int b) {
	if (a >= 0) {
		return (a + b - 1) / b;
	}
	return -((-a) / b);
}

inline void addedge(int u, int v) {
	e[++cnt].v = v;
	e[cnt].nxt = adj[u];
	adj[u] = cnt;
	deg[v]++;
}

inline LL calc(LL mid) {
	for (int i = 1; i <= n; ++i) {
		deg[i] = adj[i] = 0;
		dist[i] = 0;
	}
	cnt = 0;
	for (int i = 1; i <= m; ++i) {
		addedge(edge[i].v, edge[i].u);
	}
	
	static queue<int> Q;
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 0) {
			Q.push(i);
			dist[i] = k[i] * mid + b[i];
		}
	}
	while (Q.size()) {
		int u = Q.front();
		Q.pop();
		for (int p = adj[u]; p; p = e[p].nxt) {
			int v = e[p].v;
//cout << u << " " << v << " " << dist[u] << " " << dist[u] + k[v] * mid + b[v] << endl;
			dist[v] = max(dist[v], dist[u] + k[v] * mid + b[v]);
			if (--deg[v] == 0) {
				Q.push(v);
			}
		}
	}
	LL ret = 0;
	for (int i = 1; i <= n; ++i) {
		ret = max(ret, dist[i]);
	}
	return ret;
}

int main() {
	/*ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);*/
	
	int testcase;
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		cin >> n >> m;
		LL left = -1e5, right = 1e5;  //?
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", &b[i], &k[i]);
			if (k[i] > 0) {
				right = min(right, 1LL * (50000 - b[i]) / k[i]);
				left = max(left, 1LL * upper(1 - b[i], k[i]));
			}
			if (k[i] < 0) {
				left = max(left, 1LL * -((50000 - b[i]) / (-k[i])));
				right = min(right, 1LL * (b[i] - 1) / (-k[i]));
			}
		}
		
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &edge[i].u, &edge[i].v);
		}
				
				
		//cout << calc(-1) << endl; return 0;
		while (left + 3 < right) {
		//cout << left << " " << right << endl;
			LL m1 = left + (right - left) / 3;
			LL m2 = right - (right - left) / 3;
			if (calc(m1) > calc(m2)) {
				left = m1;
			} else {
				right = m2;
			}
		}
		LL ans = 1e18;
		for (int i = left; i <= right; ++i) {
			ans = min(ans, calc(i));
		}
		cout << "Case #" << cs << ": " << ans << endl;
	}
}

#include <bits/stdc++.h>

typedef long long ll;

const ll LNF = 0x3f3f3f3f3f3f3f3fll;

int n, m, x[100005], y[100005], kd[100005];

int head[100005], nxt[100005], to[100005], w[100005], ed;

void AddEdge(int u, int v, int d) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v; w[ed] = d;
}

ll dist[100005]; bool inq[100005];

ll SPFA() {
	static std::queue<int> que;
	static int now;
	
	for (int i = 1; i <= m; ++i) {
		if (kd[i] == 0) {
			que.push(i); inq[i] = 1; dist[i] = 0;
		}
		else dist[i] = LNF;
	}
	
	while (!que.empty()) {
		now = que.front(); que.pop(); inq[now] = 0;
		for (int i = head[now]; i; i = nxt[i]) {
			if (dist[to[i]] <= dist[now] + w[i]) continue;
			dist[to[i]] = dist[now] + w[i];
			if (!inq[to[i]]) {
				que.push(to[i]); inq[to[i]] = 1;
			}
		}
	}
	
	ll res = 0;
	for (int i = 1; i <= m; ++i) if (kd[i] == 2) {
		if (dist[i] == LNF) return -1;
		res += dist[i];
	}
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, 0, sizeof head); ed = 0;
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d", x + i);
		for (int i = 1; i <= n; ++i) scanf("%d", y + i);
		for (int c, i = 1; i <= n; ++i) {
			scanf("%d", &c);
			AddEdge(y[i], x[i], c);
		}
		for (int i = 1; i <= m; ++i) scanf("%d", kd + i);
		
		printf("Case #%d: %lld\n", kase, SPFA());
	}
	
	return 0;
}

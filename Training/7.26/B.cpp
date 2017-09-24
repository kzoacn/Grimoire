#include <bits/stdc++.h>

typedef long long ll;

int v[10005], deg[10005];

int head[10005], nxt[100005 << 1], to[100005 << 1], ed = 0;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

int n, m;
bool del[10005];

std::queue<int> que;

ll BFS(int st) {
	static std::queue<int> qq;
	static int now;
	
	int cnt = 0; ll res = 0;
	
	qq.push(st); del[st] = 1;
	while (!qq.empty()) {
		now = qq.front(); qq.pop();
		++cnt; res += v[now];
		for (int i = head[now]; i; i = nxt[i]) if (!del[to[i]]) {
			qq.push(to[i]);
			del[to[i]] = 1;
		}
	}
	if (cnt & 1) return res;
	return 0;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", v + i);
		}
		memset(deg, 0, sizeof deg);
		memset(head, 0, sizeof head); ed = 0;
		for (int u, v, i = 1; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			AddEdge(u, v);
			AddEdge(v, u);
			++deg[u]; ++deg[v];
		}
		
		memset(del, 0, sizeof del);
		for (int i = 1; i <= n; ++i) {
			if (deg[i] <= 1) {
				que.push(i);
				del[i] = 1;
			}
		}
		
		int now;
		while (!que.empty()) {
			now = que.front(); que.pop();
			for (int i = head[now]; i; i = nxt[i]) if (!del[to[i]]) {
				--deg[to[i]];
				if (deg[to[i]] <= 1) {
					que.push(to[i]);
					del[to[i]] = 1;
				}
			}
		}
		
		ll ans = 0;
		for (int i = 1; i <= n; ++i) if (!del[i])
			ans += BFS(i);
		
		printf("%lld\n", ans);
	}
	
	return 0;
}

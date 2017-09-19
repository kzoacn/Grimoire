#include <bits/stdc++.h>

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3fll;

int head[505], nxt[1000005], ed, st, sd;

struct Edge {
	int u, v; ll cap;
	
	Edge() {}
	Edge(int u, int v, ll cap): u(u), v(v), cap(cap) {}
} e[1000005];

void AddEdge(int u, int v, ll cap, ll icap = 0) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, icap);
}

int dist[505], cur[505];

bool BFS() {
	static std::queue<int> que;
	
	memset(dist, -1, sizeof dist);
	dist[st] = 0; que.push(st);
	
	while (!que.empty()) {
		int now = que.front(); que.pop();
		for (int i = head[now]; ~i; i = nxt[i]) {
			if (!e[i].cap || dist[e[i].v] != -1) continue;
			dist[e[i].v] = dist[now] + 1;
			que.push(e[i].v);
		}
	}
	
	return dist[sd] != -1;
}

ll DFS(int now, ll maxflow) {
	if (now == sd || !maxflow) return maxflow;
	ll res = 0, tmp;
	for (int &i = cur[now]; ~i; i = nxt[i]) {
		if (!e[i].cap || dist[e[i].v] != dist[now] + 1) continue;
		tmp = DFS(e[i].v, std::min(maxflow, e[i].cap));
		e[i].cap -= tmp; e[i ^ 1].cap += tmp;
		res += tmp; maxflow -= tmp;
		if (!maxflow) break;
	}
	if (!res) dist[now] = -1;
	return res;
}

ll Dinic() {
	ll res = 0;
	while (BFS()) {
		memcpy(cur, head, sizeof head);
		res += DFS(st, INF);
	}
	return res;
}

int n, w, p, q; ll D[505], r[505][505], qindian[505];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, -1, sizeof head); ed = 0;
		
		scanf("%d%d%d%d", &n, &w, &p, &q); st = 0, sd = n + 1;
		for (int i = 1; i <= n; ++i) D[i] = 1;
		memset(r, 0, sizeof r);
		memset(qindian, 0, sizeof qindian);
		
		for (int x, y, z, a, b, c, d, e, f; p--; ) {
			scanf("%d%d%d%d%d%d%d%d%d", &x, &y, &z, &a, &b, &c, &d, &e, &f);
			D[x] += d - f;
			D[y] += e - d;
			D[z] += f - e;
			r[x][y] = r[y][x] += 2ll * a * w;
			r[y][z] = r[z][y] += 2ll * b * w;
			r[z][x] = r[x][z] += 2ll * c * w;
		}
		
		for (int x, y, z; q--; ) {
			scanf("%d%d%d", &x, &y, &z);
			if (z == 0) r[y][x] = INF;
			else if (z == 1) r[x][y] = r[y][x] = INF;
			else {
				qindian[x] = -1;
				qindian[y] = 1;
			}
		}
		
		ll ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (qindian[i] == -1)
				AddEdge(st, i, INF);
			else if (qindian[i] == 1)
				AddEdge(i, sd, INF);
			
			if (D[i] > 0) {
				ans -= D[i] * w;
				AddEdge(st, i, 2ll * D[i] * w);
			}
			else if (D[i] < 0) {
				ans += D[i] * w;
				AddEdge(i, sd, -2ll * D[i] * w);
			}
			for (int j = i + 1; j <= n; ++j) if (r[i][j] || r[j][i])
				AddEdge(i, j, r[i][j], r[j][i]);
		}
		
		ans += Dinic();
		
		printf("%lld\n", ans);
	}
	
	return 0;
}

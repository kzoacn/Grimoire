#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int n;
int head[205], nxt[200005], ed, st, sd;

struct Edge {
	int u, v, cap, w;
	
	Edge() {}
	Edge(int u, int v, int cap, int w): u(u), v(v), cap(cap), w(w) {}
} e[200005];

void AddEdge(int u, int v, int cap, int w) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap, w);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0, -w);
}

int dist[205], from[205];
bool inq[205];

bool SPFA() {
	static std::queue<int> que;
	static int now;
	
	memset(dist, 0x3f, sizeof dist);
	dist[st] = 0; que.push(st); inq[st] = 1;
	while (!que.empty()) {
		now = que.front(); que.pop(); inq[now] = 0;
		for (int i = head[now]; ~i; i = nxt[i]) {
			if (!e[i].cap || dist[e[i].v] <= dist[now] + e[i].w) continue;
			dist[e[i].v] = dist[now] + e[i].w;
			from[e[i].v] = i;
			if (!inq[e[i].v]) {
				que.push(e[i].v); inq[e[i].v] = 1;
			}
		}
	}
	return dist[sd] != INF;
}

int MCF() {
	int res = 0;
	while (SPFA()) {
		int minflow = INF;
		for (int i = sd; i != st; i = e[from[i]].u)
			minflow = std::min(minflow, e[from[i]].cap);
		for (int i = sd; i != st; i = e[from[i]].u) {
			e[from[i]].cap -= minflow; e[from[i] ^ 1].cap += minflow;
			res += minflow * e[from[i]].w;
		}
	}
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, -1, sizeof head); ed = 0;
		
		scanf("%d", &n);
		st = 0, sd = n * 2 + 1;
		
		for (int w, i = 1; i < n; ++i)
			for (int j = i + 1; j <= n; ++j) {
				scanf("%d", &w);
				AddEdge(i + n, j, INF, w);
				AddEdge(j + n, i, INF, w);
			}
		
		for (int i = 1; i <= n; ++i) {
			AddEdge(i, i + n, INF, 0);
			AddEdge(st, i + n, 1, 0);
			AddEdge(i, sd, 1, 0);
		}
		
		printf("Case %d: %d\n", kase, MCF());
	}
	
	return 0;
}

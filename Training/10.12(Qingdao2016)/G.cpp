#include <bits/stdc++.h>

typedef long double ldb;

const int INF = 0x3f3f3f3f;
const ldb eps = 1e-10;

int n, m;
int head[205], nxt[1000005], ed, st, sd;
struct Edge {
	int u, v, cap; ldb w;
	
	Edge() {}
	Edge(int u, int v, int cap, ldb w): u(u), v(v), cap(cap), w(w) {}
} e[1000005];

void AddEdge(int u, int v, int cap, ldb w) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap, w);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0, -w);
}

ldb dist[205];
int from[205];
bool inq[205];

bool BellmanFord() {
	static std::queue<int> que;
	
	for (int i = st; i <= sd; ++i) dist[i] = 1e60;
	dist[st] = 0; que.push(st); inq[st] = 1;
	
	while (!que.empty()) {
		int now = que.front(); que.pop(); inq[now] = 0;
		for (int i = head[now]; ~i; i = nxt[i]) {
			if (!e[i].cap || dist[e[i].v] < dist[now] + e[i].w + eps) continue; // eps ?
			dist[e[i].v] = dist[now] + e[i].w;
			from[e[i].v] = i;
			if (!inq[e[i].v]) {
				que.push(e[i].v); inq[e[i].v] = 1;
			}
		}
	}
	
	return dist[sd] < 1e20;
}

ldb MCMF() {
	ldb cost = 0;
	int minc;
	
	while (BellmanFord()) {
		minc = INF;
		for (int i = sd; i != st; i = e[from[i]].u)
			minc = std::min(minc, e[from[i]].cap);
		for (int i = sd; i != st; i = e[from[i]].u) {
			e[from[i]].cap -= minc; e[from[i] ^ 1].cap += minc;
		}
		cost += minc * (-dist[sd]);
	}
	
	return cost;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, -1, sizeof head); ed = 0;
		
		scanf("%d%d", &n, &m); st = 0, sd = n + 1;
		for (int i = 1; i <= n; ++i) {
			static int s, b;
		
			scanf("%d%d", &s, &b);
			if (s > b)
				AddEdge(st, i, s - b, 0);
			else if (s < b)
				AddEdge(i, sd, b - s, 0);
		}
		for (int i = 1; i <= m; ++i) {
			static int u, v, c;
			static double p;
		
			scanf("%d%d%d%lf", &u, &v, &c, &p);
			p = std::log(1 - p);
		
			AddEdge(u, v, 1, 0);
			if (c > 1)
				AddEdge(u, v, c - 1, -p);
		}
		
		ldb ans = 1 - std::exp(MCMF());
	
		printf("%.2f\n", (double)ans);
	}
	
	return 0;
}

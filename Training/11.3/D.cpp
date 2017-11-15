#include <bits/stdc++.h>

const int MAXN = 305, MAXM = 200005;
const int INF = 0x3f3f3f3f;

int n, m;
int head[MAXN], nxt[MAXM], ed, st, sd;
struct Edge {
	int u, v, cap, w, id;
	
	Edge() {}
	Edge(int u, int v, int cap, int w, int id): u(u), v(v), cap(cap), w(w), id(id) {}
} e[MAXM];

void AddEdge(int u, int v, int cap, int w, int id) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap, w, id);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0, -w, 0);
}

bool inq[MAXN];
int dist[MAXN], from[MAXN];

bool modlabel() {
	static std::queue<int> que;
	
	memset(dist, 0x3f3f3f3f, sizeof dist);
	dist[st] = 0; que.push(st); inq[st] = 1;
	
	while (!que.empty()) {
		int now = que.front(); que.pop(); inq[now] = 0;
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
	int flow = 0, cost = 0;
	while (modlabel()) {
		int minc = INF;
		for (int i = sd; i != st; i = e[from[i]].u)
			minc = std::min(minc, e[from[i]].cap);
		for (int i = sd; i != st; i = e[from[i]].u) {
			e[from[i]].cap -= minc;
			e[from[i] ^ 1].cap += minc;
		}
		flow += minc;
		cost += minc * dist[sd];
	}
	return cost;
}

int ans[MAXM];

int main() {
	memset(head, -1, sizeof head);
	scanf("%d%d", &n, &m);
	st = 0, sd = n + 1;
	for (int i = 1; i <= m; ++i) {
		static int u, v, w;
		
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(st, v, w, 0, i);
		AddEdge(u, sd, w, 0, 0);
		AddEdge(u, v, INF, 1, i);
	}
	
	MCF();
	int maxFlow = 0;
	for (int i = 0; i < ed; i += 2) if (e[i].id) {
		ans[e[i].id] += e[i ^ 1].cap;
		maxFlow += e[i ^ 1].cap;
	}
	printf("%d\n", maxFlow);
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	
	return 0;
}

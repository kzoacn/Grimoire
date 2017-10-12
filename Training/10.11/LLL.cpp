#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LNF = 0x3f3f3f3f3f3f3f3fll;

int n, m, id[55][55];

int head[5105], nxt[1000005], ed, st, sd;
struct Edge {
	int u, v, cap; ll w;
	
	Edge() {}
	Edge(int u, int v, int cap, ll w): u(u), v(v), cap(cap), w(w) {}
} e[1000005];

__advance __inline void AddEdge(int u, int v, int cap, ll w) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap, w);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0, -w);
}

ll dist[5105];
//int from[5105];
int cur[5105];
bool inq[5105], instk[5105];

__advance __inline bool BellmanFord() {
	static int que[65536];
	static unsigned short hd, tl;
	
	hd = 0; tl = 0;
	
	memset(dist, 0x3f, sizeof dist);
	dist[st] = 0; que[tl++] = st; inq[st] = 1;
	
	while (hd != tl) {
		int now = que[hd++]; inq[now] = 0;
		for (int i = head[now]; ~i; i = nxt[i]) {
			if (!e[i].cap || dist[e[i].v] <= dist[now] + e[i].w) continue;
			dist[e[i].v] = dist[now] + e[i].w;
//			from[e[i].v] = i;
			if (!inq[e[i].v]) {
				que[tl++] = e[i].v; inq[e[i].v] = 1;
			}
		}
	}
	
	return dist[sd] != LNF;
}

__advance int DFS(int now, int maxflow) {
	if (now == sd || !maxflow) return maxflow;
	int res = 0, tmp;
	instk[now] = 1;
	for (int i = head[now]; ~i; i = nxt[i]) {
		if (!e[i].cap || dist[e[i].v] != dist[now] + e[i].w || instk[e[i].v]) continue;
		tmp = DFS(e[i].v, std::min(e[i].cap, maxflow));
		e[i].cap -= tmp; e[i ^ 1].cap += tmp;
		res += tmp; maxflow -= tmp;
		if (!maxflow) break;
	}
	instk[now] = 0;
	if (!res) dist[now] = LNF;
	return res;
}

__advance ll MCF(int oddeven) {
	int flow = 0, minc;
	ll cost = 0;
	while (BellmanFord()) {
//		memcpy(cur, head, sizeof head);
		minc = DFS(st, INF);
		flow += minc;
		cost += minc * dist[sd];
	}
	if (flow != n * m + oddeven) return -1;
	return cost;
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, -1, sizeof head); ed = 0;
		
		scanf("%d%d", &n, &m);
		st = 0, sd = 1; int S = 2, T = 3, tot = 4;
		int odd = 0, even = 0;
		for (int i = 1, x; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				id[i][j] = tot; tot += 2;
				
				AddEdge(st, id[i][j] + 1, 1, 0);
				AddEdge(id[i][j], sd, 1, 0);
				
				scanf("%d", &x);
				
				if (x) {
					if (x & 1) {
						AddEdge(S, id[i][j], 1, 0);
						++odd;
					}
					else {
						AddEdge(id[i][j] + 1, T, 1, 0);
						++even;
					}
				}
			}
		for (int i = 1, x; i < n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &x);
				
				AddEdge(id[i][j] + 1, id[i + 1][j], 1, x);
				AddEdge(id[i + 1][j] + 1, id[i][j], 1, x);
			}
		for (int i = 1, x; i <= n; ++i)
			for (int j = 1; j < m; ++j) {
				scanf("%d", &x);
				
				AddEdge(id[i][j] + 1, id[i][j + 1], 1, x);
				AddEdge(id[i][j + 1] + 1, id[i][j], 1, x);
			}
		if (odd != even) {
			printf("Case #%d: -1\n", kase);
			continue;
		}
		AddEdge(T, S, INF, 0);
		AddEdge(st, S, odd, 0);
		AddEdge(T, sd, odd, 0);
		
		printf("Case #%d: %lld\n", kase, MCF(odd));
	}
	
	return 0;
}

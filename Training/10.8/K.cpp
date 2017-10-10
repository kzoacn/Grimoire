#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int MAXN = 1005, MAXM = 1000005;

int n, m, k;
int head[MAXN], nxt[MAXM], ed, S, T, st, sd;

struct Edge {
	int u, v, cap, w;
	
	Edge() {}
	Edge(int u, int v, int cap, int w): u(u), v(v), cap(cap), w(w) {}
} e[MAXM];

void AddEdge(int u, int v, int cap, int w) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap, w);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0, -w);
}

int dist[MAXN], from[MAXN];
bool inq[MAXN];

bool SPFA() {
	static std::queue<int> que;
	
	memset(dist, 0x3f, sizeof dist);
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
	int flow = 0, cost = 0, mincap;
	while (SPFA()) {
		mincap = INF;
		for (int i = sd; i != st; i = e[from[i]].u)
			mincap = std::min(mincap, e[from[i]].cap);
		for (int i = sd; i != st; i = e[from[i]].u) {
			e[from[i]].cap -= mincap;
			e[from[i] ^ 1].cap += mincap;
		}
		flow += mincap;
		cost += mincap * dist[sd];
	}
	
//	std::cerr << flow << " " << cost << std::endl;
	
	if (flow < n) return -1;
	return cost;
}

int s[105], t[105], C[105][105], D[105][105], E[105][105], F[105][105];

int id_mac[105], id_mis[105][2];

int main() {
	while (~scanf("%d%d%d", &n, &m, &k) && (n || m || k)) {
		memset(head, -1, sizeof head); ed = 0;
		for (int i = 1; i <= n; ++i) scanf("%d%d", s + i, t + i);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) scanf("%d", C[i] + j);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) scanf("%d", D[i] + j);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) scanf("%d", E[i] + j);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) scanf("%d", F[i] + j);
		
		st = 0, sd = 1, S = 2, T = 3; int tot = 3;
		for (int i = 1; i <= m; ++i)
			id_mac[i] = ++tot;
		for (int i = 1; i <= n; ++i) {
			id_mis[i][0] = ++tot;
			id_mis[i][1] = ++tot;
		}
		
		for (int i = 1; i <= m; ++i) {
			AddEdge(S, id_mac[i], 1, 0);
			for (int j = 1; j <= n; ++j) if (C[j][i] < t[j])
				AddEdge(id_mac[i], id_mis[j][0], 1, D[j][i] + k * std::max(C[j][i] - s[j], 0));
		}
		
		for (int i = 1; i <= n; ++i) {
			AddEdge(st, id_mis[i][1], 1, 0);
			AddEdge(id_mis[i][0], sd, 1, 0);
			AddEdge(id_mis[i][1], T, 1, 0);
			for (int j = 1; j <= n; ++j) if (i != j) {
				if (t[i] + E[i][j] >= t[j]) continue;
				AddEdge(id_mis[i][1], id_mis[j][0], 1, F[i][j] + k * std::max(t[i] + E[i][j] - s[j], 0));
			}
		}
		AddEdge(T, S, INF, 0);
		
		printf("%d\n", MCF());
	}
	
	return 0;
}

#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int head[210], nxt[200005], ed, ss, tt, st, sd;
int ideg[210];

struct Edge {
	int u, v, cap;
	
	Edge() {}
	Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} e[200005];

void AddEdge(int u, int v, int cap, int icap = 0) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, icap);
}

int dist[210], cur[210];

bool BFS() {
	static std::queue<int> que;
	static int now;
	
	memset(dist, -1, sizeof dist);
	dist[st] = 0; que.push(st);
	
	while (!que.empty()) {
		now = que.front(); que.pop();
		for (int i = head[now]; ~i; i = nxt[i]) {
			if (!e[i].cap || dist[e[i].v] != -1) continue;
			dist[e[i].v] = dist[now] + 1;
			que.push(e[i].v);
		}
	}
	return dist[sd] != -1;
}

int DFS(int now, int maxflow) {
	if (now == sd || !maxflow) return maxflow;
	int res = 0, tmp;
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

int Dinic() {
	int res = 0;
	while (BFS()) {
		memcpy(cur, head, sizeof head);
		res += DFS(st, INF);
	}
	return res;
}

int n, m, a[105], b[105], s[105];
int cl[105][105];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, -1, sizeof head);
		ed = 0;
		
		scanf("%d%d", &n, &m);
		st = 0, ss = n * 2 + 1, tt = n * 2 + 2, sd = n * 2 + 3;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", a + i, b + i, s + i);
			s[i] = (s[i] + m - 1) / m;
		}
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", cl[i] + j);
		
		memset(ideg, 0, sizeof ideg);
		for (int i = 1; i <= n; ++i) {
			AddEdge(ss, i, INF);
			AddEdge(i + n, tt, INF);
			ideg[i + n] += s[i];
			ideg[i] -= s[i];
			for (int j = 1; j <= n; ++j)
				if (i != j && a[j] - b[i] > cl[i][j]) AddEdge(i + n, j, INF);
		}
		for (int i = 1; i <= n * 2; ++i) {
			if (ideg[i] > 0) AddEdge(st, i, ideg[i]);
			else if (ideg[i] < 0) AddEdge(i, sd, -ideg[i]);
		}
		
		Dinic();
		AddEdge(tt, ss, INF);
		printf("Case %d: %d\n", kase, Dinic());
	}
	
	return 0;
}

#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int n, m, p[1005], col[1005];

std::vector<int> G[1005];
bool vis[1005];

int head[2005], nxt[1000005], ed, st, sd;
struct Edge {
	int u, v, cap;
	
	Edge() {}
	Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} e[1000005];

void AddEdge(int u, int v, int cap) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0);
}

int dist[2005], cur[2005];

bool modlabel() {
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

int aug(int now, int maxflow) {
	if (now == sd || !maxflow) return maxflow;
	int res = 0, tmp;
	for (int &i = cur[now]; ~i; i = nxt[i]) {
		if (!e[i].cap || dist[e[i].v] != dist[now] + 1) continue;
		tmp = aug(e[i].v, std::min(maxflow, e[i].cap));
		e[i].cap -= tmp; e[i ^ 1].cap += tmp;
		res += tmp; maxflow -= tmp;
		if (!maxflow) break;
	}
	if (!res) dist[now] = -1;
	return res;
}

int Dinic() {
	int res = 0;
	while (modlabel()) {
		memcpy(cur, head, sizeof head);
		res += aug(st, INF);
	}
	return res;
}

void DFS(int now, int c) {
	col[now] = c;
	vis[now] = 1;
	for (int to: G[now]) if (!vis[to])
		DFS(to, c ^ 1);
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		memset(head, -1, sizeof head); ed = 0;
		
		st = 0, sd = n * 2 + 1;
		for (int i = 1; i <= n; ++i) {
			static int w;
			
			scanf("%d", &w);
			AddEdge(i * 2 - 1, i * 2, w);
		}
		for (int i = 1; i <= n; ++i)
			scanf("%d", p + i);
		
		for (int i = 1; i <= n; ++i) {
			col[i] = vis[i] = 0;
			G[i].clear();
		}
		
		for (int i = 1; i <= m; ++i) {
			static int u, v;
			
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
			
			AddEdge(u * 2, v * 2 - 1, INF);
			AddEdge(v * 2, u * 2 - 1, INF);
		}
		
		for (int i = 1; i <= n; ++i) if (!vis[i])
			DFS(i, 0);
		
		for (int i = 1; i <= n; ++i) {
			if (p[i] == 1) {
				if (col[i] == 0) AddEdge(st, i * 2 - 1, INF);
				else AddEdge(i * 2, sd, INF);
			}
			else if (p[i] == 2) {
				if (col[i] == 0) AddEdge(i * 2, sd, INF);
				else AddEdge(st, i * 2 - 1, INF);
			}
		}
		
		printf("%d\n", Dinic());
	}
	
	return 0;
}

#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int n, m;
int head[1005], nxt[10005 << 1], ed, st, sd;
struct Edge {
	int u, v, cap;
	
	Edge() {}
	Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} e[10005 << 1];

void AddEdge(int u, int v, int cap) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0);
}

int dist[1005], cur[1005];

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

int DFS(int now, int maxflow) {
	if (now == sd || !maxflow) return maxflow;
	int res = 0, tmp;
	for (int &i = cur[now]; ~i; i = nxt[i]) {
		if (!e[i].cap || dist[e[i].v] != dist[now] + 1) continue;
		tmp = DFS(e[i].v, std::min(e[i].cap, maxflow));
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

bool st_set[1005], sd_set[1005];

void DFS2(int now) {
	if (st_set[now]) return;
	st_set[now] = 1;
	for (int i = head[now]; ~i; i = nxt[i]) {
		if (!e[i].cap) continue;
		DFS2(e[i].v);
	}
}

void DFS3(int now) {
	if (sd_set[now]) return;
	sd_set[now] = 1;
	for (int i = head[now]; ~i; i = nxt[i]) {
		if (e[i].cap) continue;
		DFS3(e[i].v);
	}
}

int main() {
	while (~scanf("%d%d%d%d", &n, &m, &st, &sd) && (n || m || st || sd)) {
		memset(head, -1, sizeof head); ed = 0;
		for (int i = 1; i <= m; ++i) {
			static int u, v;
			
			scanf("%d%d", &u, &v);
			AddEdge(u, v, 1);
		}
		
		int maxflow = Dinic();
		memset(st_set, 0, sizeof st_set);
		memset(sd_set, 0, sizeof sd_set);
		DFS2(st);
		DFS3(sd);
		int cnt = 0;
		for (int i = 0; i < ed; i += 2) {
			if (st_set[e[i].v] && sd_set[e[i].u]) {
//				std::cerr << e[i].u << "->" << e[i].v << std::endl;
				++cnt;
			}
		}
		
		if (cnt) ++maxflow;
		printf("%d %d\n", maxflow, cnt);
	}
	
	return 0;
}

#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int head[3005], nxt[2000005], ed = 0, st, sd;

struct Edge {
	int u, v, cap;
	
	Edge() {}
	Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} e[2000005];

void AddEdge(int u, int v, int cap, int icap = 0) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, icap);
}

int dist[3005], cur[3005];

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

int S, R, F, T;

std::map<std::string, int> loca; int tot = 0;
std::vector<int> vec;

int main() {
	memset(head, -1, sizeof head);
	
	std::cin >> S >> R >> F >> T;
	st = 0, sd = S + T * 2 + 1;
	
	std::string tmp;
	for (int i = 1; i <= R; ++i) {
		std::cin >> tmp;
		if (!loca.count(tmp)) loca[tmp] = ++tot;
		AddEdge(st, loca[tmp], 1);
	}
	for (int i = 1; i <= F; ++i) {
		std::cin >> tmp;
		if (!loca.count(tmp)) loca[tmp] = ++tot;
		AddEdge(loca[tmp], sd, 1);
	}
	for (int cnt, i = 1; i <= T; ++i) {
		vec.clear();
		std::cin >> cnt;
		for (int j = 1; j <= cnt; ++j) {
			std::cin >> tmp;
			if (!loca.count(tmp)) loca[tmp] = ++tot;
			vec.push_back(loca[tmp]);
		}
		AddEdge(S + i, S + T + i, 1);
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
			AddEdge(*it, S + i, 1);
			AddEdge(S + T + i, *it, 1);
		}
	}
	
	printf("%d\n", Dinic());
	
	return 0;
}

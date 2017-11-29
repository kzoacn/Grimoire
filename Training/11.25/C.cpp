#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

const int drct[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

int id[10][10][10], cnt[10][10][10];
bool key[10][10][10];

int head[1005], nxt[1000005], ed, st, sd;
struct Edge {
	int u, v, cap;
	
	Edge() {}
	Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} e[1000005];

void AddEdge(int u, int v, int cap, int icap = 0) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, icap);
}

int dist[1005], cur[1005];

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

int augment(int now, int maxflow) {
	if (now == sd || !maxflow) return maxflow;
	int res = 0, tmp;
	for (int &i = cur[now]; ~i; i = nxt[i]) {
		if (!e[i].cap || dist[e[i].v] != dist[now] + 1) continue;
		tmp = augment(e[i].v, std::min(maxflow, e[i].cap));
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
		res += augment(st, INF);
	}
	return res;
}

inline int kabe(int x) {
	return x == 0 || x == 9;
}

void pretreatment() {
	int tot = 0;
	
	for (int i = 0; i <= 9; ++i)
		for (int j = 0; j <= 9; ++j)
			for (int k = 0; k <= 9; ++k) {
				id[i][j][k] = ++tot;
				cnt[i][j][k] = kabe(i) + kabe(j) + kabe(k);
			}
	st = 0, sd = tot + 1;
}

inline bool valid(int x) {
	return x >= 0 && x <= 9;
}

void build() {
	memset(head, -1, sizeof head); ed = 0;
	
	for (int i = 0; i <= 9; ++i)
		for (int j = 0; j <= 9; ++j)
			for (int k = 0; k <= 9; ++k) {
				if (cnt[i][j][k]) AddEdge(st, id[i][j][k], cnt[i][j][k]);
				if (key[i][j][k]) AddEdge(id[i][j][k], sd, INF);
				for (int t = 0; t < 3; ++t) {
					int x = i + drct[t][0], y = j + drct[t][1], z = k + drct[t][2];
					if (valid(x) && valid(y) && valid(z))
						AddEdge(id[i][j][k], id[x][y][z], 1, 1);
				}
			}
}

int main() {
	pretreatment();
	
	int caseCnt; scanf("%d", &caseCnt);
	while (caseCnt--) {
		memset(key, 0, sizeof key);
		
		int n; scanf("%d", &n);
		while (n--) {
			static int x, y, z;
			
			scanf("%d%d%d", &x, &y, &z);
			key[x][y][z] = 1;
		}
		
		build();
		printf("%d\n", Dinic());
	}
	
	return 0;
}

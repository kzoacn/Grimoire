#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int head[2005], nxt[200005], ed, st, sd, tot;
struct Edge {
	int u, v, cap;
	
	Edge() {}
	Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} e[200005];

void AddEdge(int u, int v, int cap, int icap = 0) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, icap);
}

int dist[2005], cur[2005];

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
	long long res = 0;
	while (BFS()) {
		memcpy(cur, head, sizeof(cur));
		res += DFS(st, INF);
	}
	return res >= INF ? -1 : res;
}

int rev(int x) {
	int res = 0;
	for (int i = 1; i <= 8; ++i) {
		res = (res << 1) | (x & 1);
		x >>= 1;
	}
	return res;
}

bool num[256];

namespace Trie {
	int root[2], to[2005][2], w[2005];
	
	void build(int &k, int l, int r, int rv) {
		k = ++tot;
		w[k] = INF;
		if (l == r) {
			to[k][0] = to[k][1] = 0;
			
			int x = rv ? rev(l) : l;
			if (num[x]) {
				if (rv == 0) AddEdge(k, x, INF);
				else AddEdge(x, k, INF);
			}
			return;
		}
		int mid = (l + r) >> 1;
		build(to[k][0], l, mid, rv);
		build(to[k][1], mid + 1, r, rv);
	}
	
	void init() {
		build(root[0], 0, 255, 0);
		build(root[1], 0, 255, 1);
	}
	
	void insert(int k, char *s, int val) {
		if (!*s) {
			w[k] = std::min(w[k], val);
			return;
		}
		insert(to[k][*s - '0'], s + 1, val);
	}
	
	void DFS(int last, int k, int rv) {
		if (!k) return;
		if (rv == 0) AddEdge(last, k, w[k]);
		else AddEdge(k, last, w[k]);
		for (int i = 0; i < 2; ++i)
			DFS(k, to[k][i], rv);
	}
	
	void edge_build() {
		DFS(st, root[0], 0);
		DFS(sd, root[1], 1);
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int n, m;
		
		memset(num, 0, sizeof num);
		memset(head, -1, sizeof head); ed = 0;
		st = 256, sd = 257, tot = 257;
		
		scanf("%d%d", &n, &m);
		for (int x, i = 1; i <= n; ++i) {
			scanf("%d", &x); num[x] = 1;
		}
		
		Trie::init();
		
		char opt[2], s[10]; int w;
		while (m--) {
			scanf("%s%s%d", opt, s, &w);
			int t = (*opt == 'P' ? 0 : 1);
			if (t == 1) std::reverse(s, s + strlen(s));
			Trie::insert(Trie::root[t], s, w);
		}
		
		Trie::edge_build();
		
		printf("Case #%d: %d\n", kase, Dinic());
	}
	
	return 0;
}

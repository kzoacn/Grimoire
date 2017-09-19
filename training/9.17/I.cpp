#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF = 1e15;
const int MAXN = 1111;
const int MAXM = 111111;
int testcase, n, m, S, T, cnt;
int adj[MAXN], mark[MAXN], seq[MAXN], cur[MAXN];
LL maxflow = 0;

struct Edge {
	int v, nxt;
	LL lim;
} e[MAXM];

inline void addedge(int u, int v, int w) {
	e[++cnt].v = v;
	e[cnt].lim = w;
	e[cnt].nxt = adj[u];
	adj[u] = cnt;
	
	e[++cnt].v = u;
	e[cnt].lim = 0;
	e[cnt].nxt = adj[v];
	adj[v] = cnt;
}

inline bool bfs() {
	memset(mark, 0, sizeof(*mark) * (n + 1));
	int head = 1, tail = 1;
	seq[1] = S;
	mark[S] = 1;
	for (; head <= tail; ++head) {
		int u = seq[head];
		cur[u] = adj[u];
		for (int p = adj[u]; ~p; p = e[p].nxt) {
			int v = e[p].v;
			if (e[p].lim && !mark[v]) {
				mark[v] = mark[u] + 1;
				seq[++tail] = v;
			}
		}
	}
	return mark[T] > 0;
}

inline void dinic(int u, LL sum) {
	if (u == T) {
		maxflow += sum;
		return;
	}
	if (mark[u] == mark[T]) {
		return;
	}
	for (int &p = cur[u]; ~p && sum; p = e[p].nxt) {
		int v = e[p].v;
		if (e[p].lim && mark[v] == mark[u] + 1) {
			LL flow = maxflow;
			dinic(v, min(sum, e[p].lim));
			flow = maxflow - flow;
			e[p].lim -= flow;
			e[p ^ 1].lim += flow;
			sum -= flow;
		}
	}
}

int main() {
	cin >> testcase;
	for (; testcase; --testcase) {
		scanf("%d%d", &n, &m);
		scanf("%d%d", &S, &T);
		memset(adj, cnt = -1, sizeof(*adj) * (n + 1));
		for (int i = 1; i <= m; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w * 10000 + 1);
		}
		
		maxflow = 0;
		while (bfs()) {
			dinic(S, INF);
		}
		printf("%d\n", (int)(maxflow % 10000));
	}
}

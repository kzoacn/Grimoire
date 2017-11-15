#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int INF = 1e9;
int n, m, S, T, cnt, maxflow, mincost;
int adj[MAXN], ans[MAXN], dist[MAXN], from[MAXN];
bool inq[MAXN];

struct Edge {
	int v, lim, c, nxt, id;
} e[MAXN];

inline void addedge(int u, int v, int lim, int cost, int id) {
	e[++cnt].v = v;
	e[cnt].lim = lim;
	e[cnt].c = cost;
	e[cnt].id = id;
	e[cnt].nxt = adj[u];
	adj[u] = cnt;
	
	e[++cnt].v = u;
	e[cnt].lim = 0;
	e[cnt].c = -cost;
	e[cnt].id = id;
	e[cnt].nxt = adj[v];
	adj[v] = cnt;
}

inline bool spfa() {
	for (int i = 1; i <= T; ++i) {
		dist[i] = INF;
		inq[i] = false;
	}
	inq[S] = true;
	dist[S] = 0;
	static queue<int> Q;
	while (Q.size()) {
		Q.pop();
	}
	Q.push(S);
	while (Q.size()) {
		int u = Q.front();
		Q.pop();
		inq[u] = false;
		for (int p = adj[u]; ~p; p = e[p].nxt) {
			int v = e[p].v;
			if (e[p].lim && e[p].c + dist[u] < dist[v]) {
				dist[v] = dist[u] + e[p].c;
				from[v] = p;
				if (!inq[v]) {
					inq[v] = true;
					Q.push(v);
				}
			}
		}
	}
	return dist[T] != INF;
}

inline void modify() {
	int u = T, flow = INF;
	while (u != S) {
		flow = min(flow, e[from[u]].lim);
		u = e[from[u] ^ 1].v;
	}
	maxflow += flow;
	u = T;
	while (u != S) {
		int p = from[u];
		mincost += flow * e[p].c;
		e[p].lim -= flow;
		e[p ^ 1].lim += flow;
		u = e[p ^ 1].v;
	}
}

int main() {
	cin >> n >> m;
	S = n + 1;
	T = n + 2;
	memset(adj, cnt = -1, sizeof(adj));
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addedge(S, v, w, 1, i);
		addedge(u, v, INF, 1, i);
		addedge(u, T, w, 0, i);
	}
	
	maxflow = 0;
	mincost = 0;
	while (spfa()) {
		modify();
	}
	for (int i = 0; i <= cnt; ++i) {
		if (e[i].c != 1) {
			continue;
		}
		if (e[i ^ 1].v == S) {
			if (e[i].lim) {
				puts("-1");
				return 0;
			}
			ans[e[i].id] += e[i ^ 1].lim;
		} else {
			ans[e[i].id] += e[i ^ 1].lim;
		}
	}
	cout << mincost << endl;
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", ans[i]);
	}
}

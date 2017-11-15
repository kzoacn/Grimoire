#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 1e4 + 5, MAXM = 5e3 + 5;

const LL INF = 0x3f3f3f3f3f3f3f3fLL;

map<pair<int, int>, int> ID;

int m;

int head[MAXN], nxt[MAXM << 1], to[MAXM << 1], d[MAXM << 1], ed, tot;

void AddEdge(int u, int v, int w) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v; d[ed] = w;
}

//int from[MAXN];
LL dist[MAXN];
bool inq[MAXN];

LL ans;

LL SPFA(int u, int v, int e) {
	static queue<int> que;
	
	for (int i = 1; i <= tot; ++i)
		dist[i] = INF;
//	memset(dist, 0x3f, sizeof dist);
//	memset(from, 0, sizeof from);
	dist[u] = 0; que.push(u); inq[u] = 1;
	
	while (!que.empty()) {
		int now = que.front(); que.pop(); inq[now] = 0;
		for (int i = head[now]; i; i = nxt[i]) {
			if (i == e || i == (e ^ 1)) continue;
			if (dist[now] + d[i] + d[e] >= ans) continue;
			if (dist[to[i]] <= dist[now] + d[i]) continue;
			dist[to[i]] = dist[now] + d[i];
//			from[to[i]] = now;
			if (!inq[to[i]]) {
				que.push(to[i]); inq[to[i]] = 1;
			}
		}
	}
	
	return dist[v] + d[e];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int caseCnt; cin >> caseCnt;
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, tot = 0, sizeof head);
		ed = 1;
		ID.clear();
		
		cin >> m;
		for (int i = 1; i <= m; ++i) {
			static int x, y, u, v, w;
			
			cin >> x >> y;
			if (ID.count(make_pair(x, y)))
				u = ID[make_pair(x, y)];
			else
				ID[make_pair(x, y)] = u = ++tot;
			
			cin >> x >> y;
			if (ID.count(make_pair(x, y)))
				v = ID[make_pair(x, y)];
			else
				ID[make_pair(x, y)] = v = ++tot;
			
			cin >> w;
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
		
		ans = INF;
		for (int i = 2; i <= ed; i += 2)
			ans = min(ans, SPFA(to[i], to[i ^ 1], i));
		
		cout << "Case #" << kase << ": " << (ans == INF ? 0LL : ans) << endl;
	}
	
	return 0;
}

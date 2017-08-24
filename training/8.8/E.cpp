#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, m, id[15][15], tot;
bool app[10], adj[10][10], adj2[10][15][15];
char mp[15][15];

int head[105], nxt[200005], ed, st, sd;

struct Edge {
	int u, v, cap;
	
	Edge() {}
	Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} e[200005];

void AddEdge(int u, int v, int cap, int icap = 0) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, icap);
}

int dist[105], cur[105];

bool BFS() {
	static std::queue<int> que;
	static int now;
	
	memset(dist, -1, sizeof(int) * (sd + 1));
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
		memcpy(cur, head, sizeof(int) * (sd + 1));
		res += DFS(st, INF);
	}
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(app, 0, sizeof app); tot = 0;
		memset(id, 0, sizeof id);
		memset(adj, 0, sizeof adj);
		memset(adj2, 0, sizeof adj2);
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			scanf("%s", mp[i] + 1);
			
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (mp[i][j] != '.') {
					app[mp[i][j] - '0'] = 1;
					for (int t = 0; t < 4; ++t) {
						int x = i + drct[t][0], y = j + drct[t][1];
						if (x < 1 || x > n || y < 1 || y > m || mp[x][y] == '.') continue;
						adj[mp[x][y] - '0'][mp[i][j] - '0'] = adj[mp[i][j] - '0'][mp[x][y] - '0'] = 1;
					}
				}
				else {
					id[i][j] = ++tot;
					for (int t = 0; t < 4; ++t) {
						int x = i + drct[t][0], y = j + drct[t][1];
						if (x < 1 || x > n || y < 1 || y > m || mp[x][y] == '.') continue;
						adj2[mp[x][y] - '0'][i][j] = 1;
					}
				}
			}
		}
		
		st = 0, sd = tot + 1;
		
		int fullSet = 0;
		for (int i = 0; i <= 9; ++i) if (app[i]) fullSet |= (1 << i);
		
		int ans = 0;
		
		for (int S = fullSet; ; S = (S - 1) & fullSet) {
			int digitCnt = 0, tmp_tot = 0;
			bool flag = 0;
			for (int i = 0; i <= 9; ++i) if (S & (1 << i)) {
				++digitCnt;
				for (int j = i + 1; j <= 9; ++j) if (S & (1 << j))
					if (adj[i][j]) { flag = 1; break; }
			}
			
			if (flag) {
				if (S == 0) break;
				continue;
			}
			
			memset(head, -1, sizeof head); ed = 0;
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= m; ++j) if (mp[i][j] == '.') {
					flag = 0;
					for (int k = 0; k <= 9; ++k) if ((S & (1 << k)) && adj2[k][i][j]) {
						flag = 1; break;
					}
					if (flag) continue;
					
					++tmp_tot;
					
					if ((i + j) & 1) AddEdge(st, id[i][j], 1);
					else {
						AddEdge(id[i][j], sd, 1); continue;
					}
					
					for (int t = 0; t < 4; ++t) {
						int x = i + drct[t][0], y = j + drct[t][1];
						if (x < 1 || x > n || y < 1 || y > m || mp[x][y] != '.') continue;
						flag = 0;
						for (int k = 0; k <= 9; ++k) if ((S & (1 << k)) && adj2[k][x][y]) {
							flag = 1; break;
						}
						if (flag) continue;
						AddEdge(id[i][j], id[x][y], INF);
					}
				}
			
			ans = std::max(ans, digitCnt + tmp_tot - Dinic());
			
			if (S == 0) break;
		}
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}

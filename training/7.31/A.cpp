#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

struct Tri {
	int x, y, z;
	
	Tri(int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}
	
	Tri operator + (const Tri &rhs) const {
		return Tri(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	
	Tri operator - (const Tri &rhs) const {
		return Tri(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	
	Tri operator * (int t) const {
		return Tri(x * t, y * t, z * t);
	}
	
	bool operator < (const Tri &rhs) const {
		return x == rhs.x ? (y == rhs.y ? z < rhs.z : y < rhs.y) : x < rhs.x;
	}
	
	bool operator <= (const Tri &rhs) const {
		return !(rhs < *this);
	}
	
	bool operator == (const Tri &rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}
	
	bool operator != (const Tri &rhs) const {
		return !(*this == rhs);
	}
	
	Tri opp() const {
		return Tri(-x, -y, -z);
	}
} inf(INF, INF, INF);

int head[405], nxt[200005], ed = 0, st, sd;

struct Edge {
	int u, v, cap;
	Tri w;
	
	Edge() {}
	Edge(int u, int v, int cap, Tri w): u(u), v(v), cap(cap), w(w) {}
} e[200005];

void AddEdge(int u, int v, int cap, Tri w) {
	nxt[ed] = head[u]; head[u] = ed; e[ed++] = Edge(u, v, cap, w);
	nxt[ed] = head[v]; head[v] = ed; e[ed++] = Edge(v, u, 0, w.opp());
}

Tri dist[405]; bool inq[405]; int from[405];

bool SPFA() {
	static std::queue<int> que;
	static int now;
	
	for (int i = st; i <= sd; ++i)
		dist[i] = inf;
	dist[st] = Tri(); que.push(st); inq[st] = 1;
	
	while (!que.empty()) {
		now = que.front(); que.pop(); inq[now] = 0;
		for (int i = head[now]; ~i; i = nxt[i]) {
			if (!e[i].cap || dist[e[i].v] <= dist[now] + e[i].w) continue;
			dist[e[i].v] = dist[now] + e[i].w;
			from[e[i].v] = i;
			if (!inq[e[i].v]) {
				que.push(e[i].v); inq[e[i].v] = 1;
			}
		}
	}
	
	return dist[sd] != inf;
}

Tri MCMF() {
	Tri res = Tri();
	while (SPFA()) {
		int mincap = INF;
		for (int i = sd; i != st; i = e[from[i]].u)
			mincap = std::min(mincap, e[from[i]].cap);
		for (int i = sd; i != st; i = e[from[i]].u) {
			res = res + e[from[i]].w * mincap;
			e[from[i]].cap -= mincap; e[from[i] ^ 1].cap += mincap;
		}
	}
	return res;
}

int m, n, k, s;
int tp[25][25]; // 0: field, 1: peasant's house, 2: swamp
int id[25][25];

int px[205], py[205], invp[405];

int Manhattan(int x1, int y1, int x2, int y2) {
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool vis[405];
int mat[405], imat[405]; Tri mn[405];
int edge_id[405][405];

std::vector<int> edge[405];
int deg[405];

std::queue<int> que;

int main() {
	memset(head, -1, sizeof head);
	
	scanf("%d%d%d%d", &m, &n, &k, &s);
	for (int x, y, i = 1; i <= k; ++i) {
		scanf("%d%d", &x, &y);
		tp[x][y] = 1;
		px[i] = x;
		py[i] = y;
	}
	for (int x, y, i = 1; i <= s; ++i) {
		scanf("%d%d", &x, &y);
		tp[x][y] = 2;
	}
	
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j) if (tp[i][j] != 2)
			id[i][j] = ++**id;
	st = 0, sd = **id + 1;
	
	for (int i = 1; i <= k; ++i)
		invp[id[px[i]][py[i]]] = i;
	
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j) {
			if (tp[i][j] == 1) {
				AddEdge(st, id[i][j], 1, Tri());
				for (int x = 1; x <= m; ++x)
					for (int y = 1; y <= n; ++y) if (tp[x][y] == 0) {
						edge_id[id[i][j]][id[x][y]] = ed;
						AddEdge(id[i][j], id[x][y], 1, Tri(Manhattan(i, j, x, y), x, y));
					}
			}
			else if (tp[i][j] == 0)
				AddEdge(id[i][j], sd, 1, Tri());
		}
	
	MCMF();
	
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j) if (tp[i][j] == 1)
			for (int x = 1; x <= m; ++x)
				for (int y = 1; y <= n; ++y) if (tp[x][y] == 0) {
					if (e[edge_id[id[i][j]][id[x][y]]].cap == 0) {
						mat[id[i][j]] = id[x][y];
						imat[id[x][y]] = id[i][j];
						mn[id[i][j]] = Tri(Manhattan(i, j, x, y), x, y);
					}
				}
	
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j) if (tp[i][j] == 1)
			for (int x = 1; x <= m; ++x)
				for (int y = 1; y <= n; ++y) if (tp[x][y] == 0) {
					if (Tri(Manhattan(i, j, x, y), x, y) < mn[id[i][j]]) {
						++deg[invp[id[i][j]]];
						edge[invp[imat[id[x][y]]]].push_back(invp[id[i][j]]);
					}
				}
	
	for (int i = 1; i <= k; ++i) if (!deg[i]) que.push(i);
	
	while (!que.empty()) {
		int now = que.front(); que.pop();
		printf("%d ", now);
		for (int i = 0; i < (int)edge[now].size(); ++i)
			if (!--deg[edge[now][i]]) {
				que.push(edge[now][i]);
			}
	}
	putchar('\n');
	
	return 0;
}

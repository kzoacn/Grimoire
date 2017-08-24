#include <bits/stdc++.h>

const double eps = 1e-8;

int sgn(double x) { return x < -eps ? -1 : x > eps; }

int n, m;
int h[205], x[205], y[205];

double edge[205][205];

double sqr(double x) {
	return x * x;
}

double Euclid(int u, int v) {
	return std::sqrt(sqr((h[u] - h[v]) * 5) + sqr(x[u] - x[v]) + sqr(y[u] - y[v]));
}

bool vis[205]; double dist[205];
int from[205];

void Dijkstra(int st) {
	memset(vis, 0, sizeof vis);
	memset(from, -1, sizeof from);
	
	for (int i = 0; i < n; ++i)
		dist[i] = 1e20;
	dist[st] = 0;
	for (int i = 1; i < n; ++i) {
		int now = -1; double nowdis = 1e20;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && sgn(dist[j] - nowdis) < 0) {
				nowdis = dist[j]; now = j;
			}
		}
		vis[now] = 1;
		for (int j = 0; j < n; ++j) if (j != now && sgn(dist[j] - (dist[now] + edge[now][j])) > 0) {
			dist[j] = dist[now] + edge[now][j];
			from[j] = now;
		}
	}
}

void print(int now, char endChar) {
	if (from[now] != -1) print(from[now], ' ');
	printf("%d%c", now, endChar);
}

int main() {
	bool firstCase = 1;
	while (~scanf("%d%d", &n, &m)) {
		if (firstCase) firstCase = 0;
		else putchar('\n');
		
		for (int i = 0; i < n; ++i)
			scanf("%d%d%d", h + i, x + i, y + i);
		
		for (int i = 0; i < n; ++i) {
			edge[i][i] = 0;
			for (int j = i + 1; j < n; ++j)
				edge[i][j] = edge[j][i] = 1e20;
		}
		
		char drct[20];
		for (int u, v, i = 1; i <= m; ++i) {
			scanf("%d%d%s", &u, &v, drct);
			switch (*drct) {
				case 'w':
				case 's':
					edge[u][v] = edge[v][u] = Euclid(u, v);
					break;
				case 'l':
					edge[u][v] = edge[v][u] = 1;
					break;
				case 'e':
					edge[u][v] = 1;
					edge[v][u] = Euclid(u, v) * 3;
					break;
			}
		}
		
		int q; scanf("%d", &q);
		int u, v;
		while (q--) {
			scanf("%d%d", &u, &v);
			Dijkstra(u);
			print(v, '\n');
		}
	}
	
	return 0;
}

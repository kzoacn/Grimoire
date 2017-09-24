#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef std::map<std::string, int> mp_si;

mp_si ID; int tot;
std::string col[305];

int R;

struct Edge {
	int u, v, to;
	
	Edge() {}
	Edge(int u, int v, int to): u(u), v(v), to(to) {}
} edge[105], e[105 << 1];

int head[305], nxt[105 << 1], ed;

void AddEdge(int u, int v, int to) {
	nxt[++ed] = head[u]; head[u] = ed; e[ed] = Edge(u, v, to);
	nxt[++ed] = head[v]; head[v] = ed; e[ed] = Edge(v, u, to);
}

std::string s[3];

double dp[505][505][305];
int vis[505][505], TAT;

void DP(int l, int r) {
	if (l >= r || vis[l][r] == TAT) return;
	vis[l][r] = TAT;
	for (int mid = l; mid < r; ++mid) {
		DP(l, mid); DP(mid + 1, r);
		for (int i = 1; i <= R; ++i) {
			dp[l][r][edge[i].to] = std::max(dp[l][r][edge[i].to], 
											std::max(dp[l][mid][edge[i].u] * dp[mid + 1][r][edge[i].v], dp[l][mid][edge[i].v] * dp[mid + 1][r][edge[i].u]));
		}
	}
}

int main() {
	bool fir = 1;
	while (~scanf("%d", &R)) {
		if (fir) fir = 0;
		else putchar('\n');
		
		ID.clear(); tot = ed = 0;
		//memset(head, 0, sizeof head);
		
		for (int i = 1; i <= R; ++i) {
			for (int j = 0; j < 3; ++j) {
				std::cin >> s[j];
				if (!ID.count(s[j])) {
					ID[s[j]] = ++tot;
					col[tot] = s[j];
				}
			}
			edge[i] = Edge(ID[s[0]], ID[s[1]], ID[s[2]]);
			//AddEdge(ID[s[0]], ID[s[1]], ID[s[2]]);
		}
		
		int T; scanf("%d", &T);
		int n;
		while (T--) {
			scanf("%d", &n);
			for (int i = 1; i <= n; ++i)
				for (int j = i; j <= n; ++j)
					for (int k = 1; k <= tot; ++k)
						dp[i][j][k] = 0;
			
			for (int i = 1; i <= n; ++i) {
				double p;
				while (1) {
					std::cin >> s[0];
					if (s[0] == "END") break;
					scanf("%lf", &p);
					dp[i][i][ID[s[0]]] = p;
				}
			}
			
			++TAT;
			DP(1, n);
			int mx = 1;
			for (int i = 2; i <= tot; ++i) if (dp[1][n][i] > dp[1][n][mx]) mx = i;
			puts(dp[1][n][mx] == 0 ? "GAMEOVER" : col[mx].c_str());
		}
	}
	
	return 0;
}

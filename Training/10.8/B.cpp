#include <bits/stdc++.h>

const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

char mp[105][105];

int n, m, k;

typedef std::pair<int, int> pii;
#define mkpair std::make_pair

pii pp[5];

int Dist[5][5];

int dist[105][105];

void BFS(pii st) {
	static std::queue<pii> que;
	static pii now;
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			dist[i][j] = -1;
	dist[st.first][st.second] = 0; que.push(st);
	
	while (!que.empty()) {
		now = que.front(); que.pop();
		int x = now.first, y = now.second;
		
		for (int t = 0; t < 4; ++t) {
			int xx = x + drct[t][0], yy = y + drct[t][1];
			if (xx < 1 || xx > n || yy < 1 || yy > m || dist[xx][yy] != -1 || mp[xx][yy] == '#') continue;
			dist[xx][yy] = dist[x][y] + 1;
			que.push(mkpair(xx, yy));
		}
	}
}

int permu[5];

int main() {
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", mp[i] + 1);
			for (int j = 1; j <= m; ++j)
				if (mp[i][j] == '@')
					pp[0] = mkpair(i, j);
		}
		scanf("%d", &k);
		for (int i = 1; i <= k; ++i)
			scanf("%d%d", &pp[i].first, &pp[i].second);
		
		for (int i = 0; i <= k; ++i) {
			BFS(pp[i]);
			for (int j = 0; j <= k; ++j)
				Dist[i][j] = dist[pp[j].first][pp[j].second];
		}
		
		for (int i = 0; i <= k; ++i) permu[i] = i;
		
		int ans = 0x3f3f3f3f, tmp;
		do {
			tmp = 0;
			for (int i = 1; i <= k; ++i) {
				if (tmp == -1) continue;
				if (Dist[permu[i - 1]][permu[i]] == -1) {
					tmp = -1;
					continue;
				}
				tmp += Dist[permu[i - 1]][permu[i]];
			}
			if (tmp != -1) ans = std::min(ans, tmp);
		} while (std::next_permutation(permu + 1, permu + k + 1));
		
		if (ans == 0x3f3f3f3f) puts("-1");
		else printf("%d\n", ans);
	}
	
	return 0;
}

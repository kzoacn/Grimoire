#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef std::pair<int, int> pii;
#define mp std::make_pair

const int INF = 0x3f3f3f3f;

struct State {
	bool ac;
	int to[26];
	std::vector<int> ito[26];
	
	State() {}
	
	__advance void clear(int n) {
		ac = 0;
		for (int i = 0; i < 26; ++i) {
			to[i] = n;
			std::vector<int>().swap(ito[i]);
		}
	}
};

struct DFA {
	int n; // death node = n
	
	State st[1005];
	
	DFA() {}
	
	__advance void scan() {
		static int m, k;
		static char ch;
		
		scanf("%d%d%d", &n, &m, &k);
		
		for (int i = 0; i <= n; ++i) st[i].clear(n);
		
		for (int x, i = 1; i <= k; ++i) {
			scanf("%d", &x);
			st[x].ac = 1;
		}
		
		for (int u, v, i = 1; i <= m; ++i) {
			scanf("%d%d %c", &u, &v, &ch);
			st[u].to[ch - 'a'] = v;
			st[v].ito[ch - 'a'].push_back(u);
		}
		
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < 26; ++j)
				if (st[i].to[j] == n) st[n].ito[j].push_back(i);
	}
} A, B;

int from[1005][1005];
pii dp[1005][1005]; // pair(length -> DP value, hash -> rank)
bool vis[1005][1005];

__advance bool cmp(pii a, pii b) {
	return dp[a.first][a.second] < dp[b.first][b.second];
}

__advance std::string Solve() {
	static pii vec[2][100005];
	static int tot[2];
	
	tot[0] = tot[1] = 0;
	
	for (int i = 0; i <= A.n; ++i)
		for (int j = 0; j <= B.n; ++j) {
			vis[i][j] = 0;
			
			if (A.st[i].ac ^ B.st[j].ac) {
				vis[i][j] = 1;
				dp[i][j] = mp(0, 0);
				vec[0][++tot[0]] = mp(i, j);
			}
		}
	
	std::sort(vec[0] + 1, vec[0] + tot[0] + 1, cmp);
	
	int cur = 1;
	while (tot[cur ^ 1]) {
		tot[cur] = 0;
		
		int rk_tot = 0;
		for (int ch = 0; ch < 26; ++ch) {
			for (int i = 1; i <= tot[cur ^ 1]; ++i) {
				int x = vec[cur ^ 1][i].first, y = vec[cur ^ 1][i].second;
				
				for (auto p: A.st[x].ito[ch])
					for (auto q: B.st[y].ito[ch]) if (!vis[p][q]) {
						vis[p][q] = 1;
						dp[p][q] = mp(dp[x][y].first + 1, ++rk_tot);
						from[p][q] = ch;
						vec[cur][++tot[cur]] = mp(p, q);
					}
			}
		}
		
		cur ^= 1;
	}
	
	if (!vis[0][0]) return std::string("0");
	
	std::string ans;
	int x = 0, y = 0;
	while (dp[x][y].first) {
		int ch = from[x][y];
		ans += (char)(ch + 'a');
		x = A.st[x].to[ch];
		y = B.st[y].to[ch];
	}
	return ans;
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		A.scan(); B.scan();
		
		printf("Case #%d: %s\n", kase, Solve().c_str());
	}
	
	return 0;
}

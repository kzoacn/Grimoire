#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

struct DFA {
	int n; // death node = n
	
	int to[1005][26];
	bool ac[1005];
	
	DFA() {}
	
	__advance void scan() {
		static int m, k;
		static char ch;
		
		scanf("%d%d%d", &n, &m, &k);
		
		for (int i = 0; i <= n; ++i) {
			ac[i] = 0;
			for (int j = 0; j < 26; ++j)
				to[i][j] = n;
		}
		
		for (int x, i = 1; i <= k; ++i) {
			scanf("%d", &x);
			ac[x] = 1;
		}
		
		for (int u, v, i = 1; i <= m; ++i) {
			scanf("%d%d %c", &u, &v, &ch);
			to[u][ch - 'a'] = v;
		}
	}
} A, B;

int fr_x[1005][1005], fr_y[1005][1005], from[1005][1005];
int dp[1005][1005]; // pair(length -> DP value, hash -> rank)
bool vis[1005][1005];

__advance std::string Solve() {
	static int qx[1005 * 1005], qy[1005 * 1005];
	static int head, tail;
	
	head = 1, tail = 0;
	
	memset(vis, 0, sizeof vis);
	dp[0][0] = 0; vis[0][0] = 1;
	++tail;
	qx[tail] = 0, qy[tail] = 0;
	
	while (head <= tail) {
		int x = qx[head], y = qy[head]; ++head;
		
		if (A.ac[x] ^ B.ac[y]) {
			std::string ans;
			while (x || y) {
				ans += (char)(from[x][y] + 'a');
				int p = fr_x[x][y], q = fr_y[x][y];
				x = p, y = q;
			}
			for (int l = 0, r = (int)ans.length() - 1; l < r; ++l, --r)
				std::swap(ans[l], ans[r]);
			return ans;
		}
		
		for (int ch = 0; ch < 26; ++ch) {
			int p = A.to[x][ch], q = B.to[y][ch];
			if (vis[p][q]) continue;
			
			vis[p][q] = 1;
			dp[p][q] = dp[x][y] + 1;
			fr_x[p][q] = x, fr_y[p][q] = y;
			from[p][q] = ch;
			++tail;
			qx[tail] = p; qy[tail] = q;
		}
	}
	
	return std::string("0");
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		A.scan(); B.scan();
		
		printf("Case #%d: %s\n", kase, Solve().c_str());
	}
	
	return 0;
}

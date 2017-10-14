#include <bits/stdc++.h>

const int Mod = 1000003;

namespace ACAM {
	int to[1005][26], fail[1005];
	bool ends[1005];
	int root, tot;
	
	int newnode() {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		fail[tot] = 0;
		ends[tot] = 0;
		return tot;
	}
	
	void init() {
		tot = 0;
		root = newnode();
	}
	
	void insert(int &k, char *s) {
		if (!k) k = newnode();
		if (!*s) {
			ends[k] = 1;
			return;
		}
		insert(to[k][*s - 'a'], s + 1);
	}
	
	void build() {
		static std::queue<int> que;
		
		fail[root] = root;
		for (int i = 0; i < 26; ++i) {
			if (to[root][i]) {
				fail[to[root][i]] = root;
				que.push(to[root][i]);
			}
			else to[root][i] = root;
		}
		
		while (!que.empty()) {
			int now = que.front(); que.pop();
			ends[now] |= ends[fail[now]];
			for (int i = 0; i < 26; ++i) {
				if (to[now][i]) {
					fail[to[now][i]] = to[fail[now]][i];
					que.push(to[now][i]);
				}
				else to[now][i] = to[fail[now]][i];
			}
		}
	}
}

int n, L, R;

char s[50];

int dp[25][1005][8]; // 1: lower 2: upper 4: number

const char trans[] = "oi\0e\0s\0t\0\0\0";

int main() {
	ACAM::init();
	
	scanf("%d%d%d", &L, &R, &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s);
		ACAM::insert(ACAM::root, s);
	}
	
	ACAM::build();
	
	int ans = 0;
	
	dp[0][ACAM::root][0] = 1;
	for (int len = 1; len <= R; ++len) {
		for (int now = 1; now <= ACAM::tot; ++now) if (!ACAM::ends[now]) {
			for (int S = 0; S < 8; ++S) {
				for (int i = 0; i < 26; ++i) { // lowercase
					if (!ACAM::ends[ACAM::to[now][i]])
						dp[len][ACAM::to[now][i]][S | 1] = (dp[len][ACAM::to[now][i]][S | 1] + dp[len - 1][now][S]) % Mod;
				}
				for (int i = 0; i < 26; ++i) { // uppercase
					if (!ACAM::ends[ACAM::to[now][i]])
						dp[len][ACAM::to[now][i]][S | 2] = (dp[len][ACAM::to[now][i]][S | 2] + dp[len - 1][now][S]) % Mod;
				}
				for (int i = 0; i < 10; ++i) { // number
					if (trans[i] && !ACAM::ends[ACAM::to[now][trans[i] - 'a']])
						dp[len][ACAM::to[now][trans[i] - 'a']][S | 4] = (dp[len][ACAM::to[now][trans[i] - 'a']][S | 4] + dp[len - 1][now][S]) % Mod;
					else if (!trans[i])
						dp[len][ACAM::root][S | 4] = (dp[len][ACAM::root][S | 4] + dp[len - 1][now][S]) % Mod;
				}
			}
		}
		if (L <= len && len <= R) {
			for (int now = 1; now <= ACAM::tot; ++now)
				if (!ACAM::ends[now])
					ans = (ans + dp[len][now][7]) % Mod;
		}
	}
	
	printf("%d\n", ans);
	
	return 0;
}

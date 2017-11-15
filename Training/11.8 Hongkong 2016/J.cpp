#include <bits/stdc++.h>

const int MAXN = 1.5e4 + 5, MAXNODE = 2e5 + 5;

namespace ACAM {
	int to[MAXNODE][2], fail[MAXNODE], tot;
	int root;
	bool isend[MAXNODE];
	
	int newnode() {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		fail[tot] = 0;
		isend[tot] = 0;
		return tot;
	}
	
	void init() {
		tot = 0;
		root = newnode();
	}
	
	void insert(int &k, char *s) {
		if (!k) k = newnode();
		if (!*s) {
			isend[k] = 1;
			return;
		}
		insert(to[k][*s - '0'], s + 1);
	}
	
	void build() {
		static std::queue<int> que;
		
		for (int i = 0; i < 2; ++i) {
			if (to[root][i]) {
				fail[to[root][i]] = root;
				que.push(to[root][i]);
			}
			else to[root][i] = root;
		}
		
		while (!que.empty()) {
			int now = que.front(); que.pop();
			isend[now] |= isend[fail[now]];
			for (int i = 0; i < 2; ++i) {
				if (to[now][i]) {
					fail[to[now][i]] = to[fail[now]][i];
					que.push(to[now][i]);
				}
				else to[now][i] = to[fail[now]][i];
			}
		}
	}
	
	int label[MAXNODE];
	
	bool FindCircle(int now) {
		if (isend[now]) return 0;
		if (label[now] == 1) return 1;
		if (label[now] == 2) return 0;
		label[now] = 1;
		for (int i = 0; i < 2; ++i) {
			if (FindCircle(to[now][i])) return 1;
		}
		label[now] = 2;
		return 0;
	}
	
	int dp[MAXNODE], nxt[MAXNODE];
	
	int DP(int now) {
		if (isend[now]) return -1;
		if (label[now]) return dp[now];
		label[now] = 1;
		dp[now] = 0;
		for (int i = 0; i < 2; ++i) {
			int tmp = DP(to[now][i]) + 1;
			if (tmp > dp[now]) {
				dp[now] = tmp;
				nxt[now] = i;
			}
		}
		return dp[now];
	}
	
	std::string DP() {
		std::string res;
		
		memset(nxt, -1, sizeof nxt);
		memset(label, 0, sizeof label);
		DP(root);
		
		for (int now = root; nxt[now] != -1; now = to[now][nxt[now]])
			res.push_back(nxt[now] + '0');
		return res;
	}
}

int n;

int main() {
	ACAM::init();
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		static char s[MAXNODE];
		
		scanf("%s", s);
		ACAM::insert(ACAM::root, s);
	}
	
	ACAM::build();
	if (ACAM::FindCircle(ACAM::root))
		return puts("-1"), 0;
	
	printf("%s\n", ACAM::DP().c_str());
	
	return 0;
}

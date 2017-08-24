#include <bits/stdc++.h>

const int Mod = 998244353;
const int lim = 20;

namespace Trie {
	int root, to[5005][2], msk[5005], tot;
	
	void init() {
		tot = 0;
		root = 0;
	}
	
	int newnode() {
		++tot;
		to[tot][0] = to[tot][1] = msk[tot] = 0;
		return tot;
	}
	
	void insert(int &k, int *s, int mask) {
		if (!k) k = newnode();
		if (*s == -1) {
			msk[k] |= mask; return;
		}
		insert(to[k][*s], s + 1, mask);
	}
}

namespace ACAM {
	int root, to[305][2], msk[305], fail[305], tot;
	
	void init() {
		tot = 0;
		root = 0;
	}
	
	int newnode() {
		++tot;
		to[tot][0] = to[tot][1] = msk[tot] = fail[tot] = 0;
		return tot;
	}
	
	void insert(int &k, int *s, int mask) {
		if (!k) k = newnode();
		if (*s == -1) {
			msk[k] |= mask; return;
		}
		insert(to[k][*s], s + 1, mask);
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
			for (int i = 0; i < 2; ++i) {
				if (to[now][i]) {
					fail[to[now][i]] = to[fail[now]][i];
					msk[to[now][i]] |= msk[fail[to[now][i]]];
					que.push(to[now][i]);
				}
				else to[now][i] = to[fail[now]][i];
			}
		}
	}
}

int n, L, ss[25];
char s[25]; int len;

bool check(int mid) {
	for (int i = mid - 1, j = mid; i >= 0 && j < len; --i, ++j)
		if (ss[i] == ss[j]) return 0;
	return 1;
}

void Insert(int id) {
	ACAM::insert(ACAM::root, ss, 1 << id);
	for (int i = 0; i <= (len >> 1); ++i) if (check(i)) {
//		fprintf(stderr, "Insert: %d->%d\n", id, i);
		Trie::insert(Trie::root, ss + i, 1 << id);
	}
}

int dp[2][505][1 << 6];

//char tmp[25];

void DFS(int dep, int u1, int u2, int mask) {
	mask |= Trie::msk[u1] | ACAM::msk[u2];
	
/*	tmp[dep] = '\0';
	fprintf(stderr, "%s: mask = %d\n", tmp, mask);*/
	
	if (dep == L || dep == lim) {
//		fprintf(stderr, "%s: mask = %d\n", tmp, mask);
		++dp[0][u2][mask];
		return;
	}
	for (int i = 0; i < 2; ++i) {
//		tmp[dep] = i + '0';
		DFS(dep + 1, Trie::to[u1][i], ACAM::to[u2][i], mask);
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(dp, 0, sizeof(dp));
		Trie::init();
		ACAM::init();
		
		scanf("%d%d", &n, &L);
		for (int i = 0; i < n; ++i) {
			scanf("%s", s); len = strlen(s);
			ss[len] = -1;
			for (int j = 0; j < len; ++j) ss[j] = s[j] - '0';
			Insert(i);
			for (int j = 0; j < len; ++j) ss[j] = (s[len - j - 1] - '0') ^ 1;
			Insert(i);
		}
		
		ACAM::build();
		
		DFS(0, Trie::root, ACAM::root, 0);
		
//		fprintf(stderr, "%d %d\n", Trie::tot, ACAM::tot);
		
		int cur = 1;
		for (int i = lim + 1; i <= L; ++i, cur ^= 1) {
			memset(dp[cur], 0, sizeof(dp[cur]));
			for (int msk = 0; msk < (1 << n); ++msk) {
				for (int u = 1; u <= ACAM::tot; ++u) {
					for (int j = 0; j < 2; ++j) {
//						fprintf(stderr, "DEBUG: %d %d %d %d\n", i, msk, u, j);
						dp[cur][ACAM::to[u][j]][msk | ACAM::msk[ACAM::to[u][j]]] = 
								(dp[cur][ACAM::to[u][j]][msk | ACAM::msk[ACAM::to[u][j]]] + dp[cur ^ 1][u][msk]) % Mod;
					}
				}
			}
		}
		
		int ans = 0;
		for (int u = 1; u <= ACAM::tot; ++u)
			ans = (ans + dp[cur ^ 1][u][(1 << n) - 1]) % Mod;
		printf("%d\n", ans);
	}
	
	return 0;
}

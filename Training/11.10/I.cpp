#include <bits/stdc++.h>

typedef std::pair<int, int> PII;
#define mkpair std::make_pair

const int MAXN = 200 + 5, MAXM = 1e4 + 5;

const int INF = 0x3f3f3f3f;

int m, n, k; // Mana, Kind, EquationCount

int lastc[MAXN], c[MAXN], p[MAXN];

struct Rule {
	int v;
	int infCnt, pri;
	
	Rule() {
		v = 0;
		infCnt = pri = 0;
	}
} rules[MAXN];

std::vector<PII> nxtRule[MAXN];

bool inq[MAXN];

void SPFA() {
	static std::queue<int> que;
	
	for (int i = 1; i <= n; ++i) {
		lastc[i] = INF;
		if (c[i] != INF && c[i] <= m) {
			que.push(i); inq[i] = 1;
		}
	}
	
	while (!que.empty()) {
		int now = que.front(); que.pop(); inq[now] = 0;
		for (auto e: nxtRule[now]) {
			int i = e.first, x = e.second;
			
			if (lastc[now] == INF) {
				--rules[i].infCnt;
				rules[i].pri += c[now] * x;
			}
			else {
				rules[i].pri += (c[now] - lastc[now]) * x;
			}
			if (!rules[i].infCnt && rules[i].pri <= m && c[rules[i].v] > rules[i].pri) {
//				lastc[rules[i].v] = c[rules[i].v];
				c[rules[i].v] = rules[i].pri;
				if (!inq[rules[i].v]) {
					que.push(rules[i].v); inq[rules[i].v] = 1;
				}
			}
		}
		lastc[now] = c[now];
	}
}

int dp[MAXM];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d", &m, &n, &k);
		
		for (int i = 1; i <= n; ++i) {
			nxtRule[i].clear();
			c[i] = INF;
		}
		for (int i = 1; i <= k; ++i)
			rules[i] = Rule();
		
		for (int i = 1; i <= n; ++i) {
			static int x;
			
			scanf("%d", &x);
			if (x) scanf("%d", c + i);
			scanf("%d", p + i);
		}
		for (int i = 1; i <= k; ++i) {
			static int x;
			
			scanf("%d%d", &rules[i].v, &x);
			while (x--) {
				static int u, v;
				
				scanf("%d%d", &u, &v);
				nxtRule[u].push_back(mkpair(i, v));
				++rules[i].infCnt;
			}
		}
		
		SPFA();
		
//		for (int i = 1; i <= n; ++i)
//			fprintf(stderr, "c[%d] = %d\n", i, c[i]);
		
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= n; ++i) if (c[i] <= m)
			for (int j = c[i]; j <= m; ++j)
				dp[j] = std::max(dp[j], dp[j - c[i]] + p[i]);
		
		int ans = 0;
		for (int i = 0; i <= m; ++i)
			ans = std::max(ans, dp[i]);
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}

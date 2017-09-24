//#include <bits/stdc++.h>

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

#define __advance __attribute__((optimize("O3")))

const int Mod = 998244353;
int lim;
const int MAXN = 3333;
typedef long long LL;

#define fix(x) if (x >= Mod) x -= Mod

int n, m, a[MAXN], b[MAXN];

struct BIT {
	int c[MAXN];
	
	__advance __inline void init() {
		memset(c, 0, sizeof(int) * (lim + 1));
	}
	
#define lowbit(x) ((x) & -(x))
	
	__advance __inline void add(int a, int x) {
		for (register int i = a; i <= lim; i += lowbit(i)){
			c[i] += x; fix(c[i]);
		}
	}
	
	__advance __inline int query(int a) {
		register LL res = 0;
		for (register int i = a; i > 0; i -= lowbit(i)){
			res += c[i];// fix(res);
		}
		return res % Mod;
	}
	__advance __inline int query(int a,int b) {
		return query(b)-query(a);
	}
} bit[3][MAXN];

int dp[3][MAXN];

int head[MAXN], nxt[MAXN], last[MAXN];

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, 0, sizeof head);
		memset(last, 0, sizeof last);
		
		scanf("%d%d", &n, &m);
		lim = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i); lim = std::max(lim, a[i]);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", b + i); lim = std::max(lim, b[i]);
			if (!head[b[i]]) head[b[i]] = i;
			nxt[last[b[i]]] = i;
			last[b[i]] = i;
		}
		for (int i = 1; i <= lim; ++i)
			nxt[last[i]] = m + 1;
		
		for (int k = 0; k < 2; ++k)
			for (int i = 1; i <= m; ++i) bit[k][i].init();
		
		int ans = 0;
		register int i,j,k,tmp;
		for (i = 1; i <= n; ++i) {
			for (k = 0; k < 2; ++k) {
				tmp = (k == 0);
				for (j = 1; j <= m; ++j) {
					BIT &T=bit[k ^ 1][j];
					if (a[i] == b[j]) {
						dp[k][j] = tmp;
						ans += dp[k][j]; fix(ans);
					}
					if (k == 0) tmp = (1ll * tmp + T.query(a[i],lim) + Mod) % Mod;
					else {
						tmp += T.query(a[i] - 1); fix(tmp);
					}
				}
			}
			for (k = 0; k < 2; ++k)
				for (j = head[a[i]]; j <= m; j = nxt[j])
					bit[k][j].add(a[i], dp[k][j]);
		}
		printf("%d\n", ans);
	}
	
	return 0;
}

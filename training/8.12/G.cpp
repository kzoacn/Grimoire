#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 111111;
LL c[MAXN], ans[MAXN];
int a[MAXN], d[MAXN], mu[MAXN], number[MAXN], p[MAXN], pos[MAXN], testcase, n, m;
vector<int> factor[MAXN], factor_mu[MAXN], multiple[MAXN];
vector<pair<int, int> > qry[MAXN];

inline int lowbit(int k) {
	return k & -k;
}

inline void modify(int k, LL x) {
	for (; k <= n; k += lowbit(k)) {
		c[k] += x;
	}
}

inline LL query(int k) {
	LL ret = 0;
	for (; k; k -= lowbit(k)) {
		ret += c[k];
	}
	return ret;
}

int main() {
	mu[1] = 1;
	for (int i = 1; i < MAXN; ++i) {
		for (int j = i + i; j < MAXN; j += i) {
			mu[j] -= mu[i];
		}
	}
	for (int i = 1; i < MAXN; ++i) {
		factor[i].clear();
		factor_mu[i].clear();
		multiple[i].clear();
	}
	for (int i = 1; i < MAXN; ++i) {
		for (int j = i; j < MAXN; j += i) {
			factor[j].push_back(i);
			if (mu[i]) {
				factor_mu[j].push_back(i);
			}
			multiple[i].push_back(j);
		}
	}
	scanf("%d", &testcase);
	for (; testcase; --testcase) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			pos[a[i]] = i;
			qry[i].clear();
		}
		for (int i = 1; i <= m; ++i) {
			int l, r;
			scanf("%d%d", &l, &r);
			qry[r].push_back(make_pair(l, i));
		}
		memset(c, 0, sizeof(*c) * (n + 10));
		memset(number, 0, sizeof(*number) * (n + 10));
		for (int i = 1; i <= n; ++i) {
			int cnt = p[0] = 0;
			for (auto u : multiple[a[i]]) {
				if (u <= n && pos[u] < i) {
					p[++cnt] = pos[u];
				}
			}
			sort(p + 1, p + cnt + 1);
			for (int j = cnt; j; --j) {
				LL now = 0;
				for (auto g: factor_mu[a[p[j]] / a[i]]) {
					now += mu[g] * number[g];
				}
				now *= a[i];
				modify(1, now);
				modify(p[j] + 1, -now);
				for (auto g: factor[a[p[j]] / a[i]]) {
					number[g]++;
				}
			}
			for (int j = cnt; j; --j) {
				for (auto g: factor[a[p[j]] / a[i]]) {
					number[g]--;
				}
			}
			for (auto u: qry[i]) {
				ans[u.second] = query(u.first);
			}
		}
		
		for (int i = 1; i <= m; ++i) {
			printf("%lld\n", ans[i]);
		}
	}
}

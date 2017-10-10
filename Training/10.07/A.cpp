#include <bits/stdc++.h>

typedef long long ll;

int n, m;

struct Opt {
	int tp, p; ll x; // 0: query, 1: change
	
	Opt() {}
	Opt(int tp, int p, ll x = 0): tp(tp), p(p), x(x) {}
} opt[100005];

char s[10];

ll calc(int x) {
	ll res = 0;
	while (x <= n) {
		res += x;
		x = x << 1 | 1;
	}
	return res;
}

std::map<int, ll> n_link;

int node[100005 * 30], tot;
ll val[100005 * 30], sum[100005 * 30];

int hsh(int x) {
	return std::lower_bound(node + 1, node + tot + 1, x) - node;
}	

ll Calc(int x) {
	if (x > n) return 0;
	static int t;
	ll res;
	if (node[t = hsh(x)] == x) res = sum[t];
	else res = calc(x);
	if (n_link.count(x)) res = std::max(res, n_link[x]);
	return res;
}

ll Val(int x) {
	if (x > n) return 0;
	static int t;
	if (node[t = hsh(x)] == x) return val[t];
	return x;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		tot = 0;
		for (int i = 1; i <= m; ++i) {
			static int p;
			static ll x;
			
			scanf("%s", s);
			if (s[0] == 'q') {
				scanf("%d", &p);
				opt[i] = Opt(0, p);
				
				if ((p << 1) <= n) node[++tot] = p << 1;
				if ((p << 1 | 1) <= n) node[++tot] = p << 1 | 1;
				int which = p & 1;
				p >>= 1;
				while (p) {
					if ((p << 1 | (which ^ 1)) <= n) node[++tot] = p << 1 | (which ^ 1);
					which = p & 1;
					p >>= 1;
				}
			}
			else {
				scanf("%d%lld", &p, &x);
				opt[i] = Opt(1, p, x);
				while (p) {
					node[++tot] = p;
					p >>= 1;
				}
			}
		}
		
		std::sort(node + 1, node + tot + 1);
		tot = std::unique(node + 1, node + tot + 1) - node - 1;
		
		for (int i = 1; i <= tot; ++i) {
			sum[i] = calc(node[i]);
			val[i] = node[i];
		}
		
		n_link.clear();
		ll sum = 0;
		for (int i = n; i; i >>= 1) {
			sum += i;
			n_link.insert(std::make_pair(i, sum));
		}
		
		for (int i = 1; i <= m; ++i) {
			if (opt[i].tp == 0) {
				int k = opt[i].p, which = k & 1;
				ll ans = Val(k) + Calc(k << 1) + Calc(k << 1 | 1), Sum = Calc(k);
				k >>= 1;
				while (k) {
					Sum += Val(k);
					ans = std::max(ans, Sum + Calc(k << 1 | (which ^ 1)));
					which = k & 1;
					k >>= 1;
				}
				printf("%lld\n", ans);
			}
			else {
				int k = opt[i].p;
				ll x = opt[i].x - Val(k);
				if (n_link.count(k)) {
					for (std::map<int, ll>::iterator it = n_link.begin(); it != n_link.end(); ++it) {
						it->second += x;
						if (it->first == k) break;
					}
				}
				val[hsh(k)] += x;
				while (k) {
					::sum[hsh(k)] = std::max(Calc(k << 1), Calc(k << 1 | 1)) + Val(k);
					k >>= 1;
				}
			}
		}
	}
	
	return 0;
}

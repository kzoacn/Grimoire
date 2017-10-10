#include <bits/stdc++.h>

typedef long long ll;

const double eps = 1e-6;

int n;
ll a[45];

std::multiset<ll> st, st2;

ll Int(double x) {
	return x - std::floor(x) < std::ceil(x) - x ? std::floor(x) : std::ceil(x);
}

bool isInt(double x) {
	return std::abs(x - Int(x)) < eps;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		st.clear();
		st2.clear();
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			st.insert(a[i]);
		}
		
		std::sort(a + 1, a + n + 1);
		
		int ans = n - 1;
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j) {
				st.erase(st.find(a[i]));
				st.erase(st.find(a[j]));
				for (int posdel = 1; posdel < n; ++posdel) {
					double del = 1. * (a[j] - a[i]) / posdel;
					
					int tmp = 2;
					double L = a[j], R = a[j] + del;
					for (int t = 1; t < posdel; ++t) {
						L -= del;
						if (isInt(L) && st.count(Int(L))) {
							st.erase(st.find(Int(L)));
							st2.insert(Int(L));
							++tmp;
						}
					}
					
					L = a[i];
					
					for (int t = posdel + 1; t < n; ++t) {
						L -= del;
						if (isInt(L) && st.count(Int(L))) {
							st.erase(st.find(Int(L)));
							st2.insert(Int(L));
							++tmp;
						}
					}
					
					ans = std::min(ans, n - tmp);
					
					for (int t = 1; t < n - posdel; ++t) {
						if (isInt(L) && st2.count(Int(L))) {
							st2.erase(st2.find(Int(L)));
							st.insert(Int(L));
							--tmp;
						}
						if (isInt(R) && st.count(Int(R))) {
							st.erase(st.find(Int(R)));
							st2.insert(Int(R));
							++tmp;
						}
						L += del;
						R += del;
						
						ans = std::min(ans, n - tmp);
					}
					
					while (!st2.empty()) {
						st.insert(*st2.begin());
						st2.erase(st2.begin());
					}
				}
				st.insert(a[i]);
				st.insert(a[j]);
			}
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}

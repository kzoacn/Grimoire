#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int testcase, n, m;
int a[111111], b[111111];
__int128 ans = 0;

inline int lcm(int a, int b) {
	return a / __gcd(a, b) * b;
}

inline void dfs(int dep, int now, int t) {
	if (dep > n) {
		ans += (__int128)(m / now) * (m / now + 1) / 2 * t * now;
		//cout << dep << " " << now << " " << (m / now) * (m / now + 1) / 2 * t * now << endl;
		return;
	}
	if (now == m) {
		return;
	}
	dfs(dep + 1, now, t);
	dfs(dep + 1, lcm(now, b[dep]), -t);
} 

int main() {
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			a[i] = __gcd(a[i], m);
		}
		
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			bool flag = true;
			for (int j = 1; j <= n; ++j) {
				if (i != j && a[i] % a[j] == 0) {
					flag = false;
				}
			}
			if (flag) {
				b[++cnt] = a[i];
				//cout << b[cnt] << endl;
			}
		}
		n = cnt;
		
		ans = 0;
		dfs(1, 1, 1);
		ans = 1LL * m * (m + 1) / 2 - m - ans;
		printf("Case #%d: %lld\n", cs, (LL)ans);
	}
}

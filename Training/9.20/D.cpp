#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 233333;
int a[MAXN], c[MAXN], n;
LL s[MAXN], b[MAXN], table[MAXN], tot[111];

inline int lowbit(int k) {
	return k & -k;
}

inline int query(int k) {
	int ret = 0;
	for (; k <= n; k += lowbit(k)) {
		ret += c[k];
	}
	return ret;
}

inline void add(int k) {
	for (; k; k -= lowbit(k)) {
		c[k]++;
	}
}

inline LL get_floor(LL a, LL b) {
	LL r = (a % b + b) % b;
	return (a - r) / b;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		LL sum = 0;
		bool flag = true;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
			if (a[i]) {
				flag = false;
			}
		}
		
		if (sum < 0 || (sum == 0 && flag == false)) {
			puts("Endless");
			continue;
		}
		if (flag) {
			puts("0");
			continue;
		}
		s[0] = 0;
		for (int i = 1; i <= n; ++i) {
			s[i] = s[i - 1] + a[i];
		}
		for (int i = 1; i <= n; ++i) {
			b[i] = s[i] + sum;
		}
		
		LL ans = 0;
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			table[i] = s[i];
		}
		sort(table + 1, table + n + 1);
		cnt = unique(table + 1, table + n + 1) - table - 1;
		for (int i = 1; i <= n; ++i) {
			a[i] = lower_bound(table + 1, table + cnt + 1, s[i]) - table;
		}
		memset(c, 0, sizeof(*c) * (n + 1));
		for (int i = 1; i <= n; ++i) {
			ans += query(a[i] + 1);
			add(a[i]);
		}
		//for (int i = 1; i <= n; ++i) cout << s[i] << " ";cout << endl; cout << ans << endl;
		
		for (int i = 0; i < sum; ++i) {
			c[i] = 0;
			tot[i] = 0;
		}
		sort(s + 1, s + n + 1);
		sort(b + 1, b + n + 1);
		//for (int i = 1; i <= n; ++i) cout << s[i] << " "; cout << endl;
		//for (int i = 1; i <= n; ++i) cout << b[i] << " "; cout << endl;
		for (int i = 1, j = 1; i <= n; ++i) {
			while (j <= n && b[j] < s[i]) {
				LL r = (b[j] % sum + sum) % sum;
				LL p = 1LL * (b[j] - r) / sum;
				//cout << j << " " << b[j] << " " << r << " " << p << endl;
				c[r]++;
				tot[r] += p;
				++j;
			}
			LL r1 = (s[i] % sum + sum) % sum;
			LL p = 1LL * (s[i] - r1) / sum;
			//if (i == 3) cout << s[i] << " " <<  p << " " << r1 << endl;
			for (int r2 = 0; r2 < sum; ++r2) {
				ans += 1LL * c[r2] * (1 + p + get_floor(r1 - r2 - 1, sum));
				//if (i == 3 && r2 == 1) cout << c[r2] << " " << p << endl;
				ans -= tot[r2];
			}
			//cout << ans << endl;
		}
		printf("%lld\n", ans);
	}
}

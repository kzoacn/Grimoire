#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

template <class T>
__advance void scan(T &x) {
	register char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

int n, k, aa[60005];
int b, l[60005], r[60005], tag[60005], tot;

struct Num {
	int val, pos;
	
	Num() {}
	Num(int val, int pos): val(val), pos(pos) {}
	
	__advance bool operator < (const Num &rhs) const {
		return val < rhs.val;
	}
} a[60005];

int ans;

__advance bool check(int t) {
	int res = 0;
	for (int i = 1; i <= tot; ++i)
		res += std::upper_bound(a + l[i], a + r[i] + 1, Num(t - tag[i], 0)) - a - l[i];
	return res < ((n + 1) >> 1);
}

__advance int main() {
	freopen("F.in", "r", stdin);
	
	while (~scanf("%d%d", &n, &k) && (n || k)) {
		b = std::floor(std::sqrt(n));
		tot = 0;
		for (int i = 1; i <= n; i += b) {
			++tot;
			l[tot] = i;
			r[tot] = std::min(i + b - 1, n);
			tag[tot] = 0;
		}
		
		for (int i = 1; i <= n; ++i) {
			scan(aa[i]); a[i] = Num(aa[i], i);
		}
		std::sort(aa + 1, aa + n + 1);
		ans = aa[(n + 1) >> 1];
		
//		printf("check: %d\n", check(ans));
		
		for (int i = 1; i <= tot; ++i)
			std::sort(a + l[i], a + r[i] + 1);
		
		int x, y;
		while (k--) {
			scan(x); scan(y);
			int lb = (x + b - 1) / b, rb = (y + b - 1) / b;
			
			for (int i = lb + 1; i <= rb - 1; ++i)
				++tag[i];
			
			for (int i = l[lb]; i <= r[lb]; ++i) if (x <= a[i].pos && a[i].pos <= y) ++a[i].val;
			std::sort(a + l[lb], a + r[lb] + 1);
			
			if (lb != rb) {
				for (int i = l[rb]; i <= r[rb]; ++i) if (x <= a[i].pos && a[i].pos <= y) ++a[i].val;
				std::sort(a + l[rb], a + r[rb] + 1);
			}
			
			if (check(ans)) ++ans;
			
			printf("%d\n", ans);
		}
	}
	
	return 0;
}

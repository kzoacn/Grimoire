#include <bits/stdc++.h>

const char dig[] = "0123456789ABCDEF";

int n, m;

long long BITSUM(int x, int bs) {
	long long res = 0;
	while (x > 0) {
		res += (x % bs) * (x % bs);
		x /= bs;
	}
	return res;
}

char s[100000];
int len;

void print(long long x, int bs) {
	if (x == 0) {
		puts("0"); return;
	}
	
	len = 0;
	while (x > 0) {
		s[++len] = dig[x % bs];
		x /= bs;
	}
	for (int i = len; i; --i)
		putchar(s[i]);
	putchar('\n');
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		long long ans = 0;
		
		int t = std::sqrt(n);
		for (int i = 1; i <= t; ++i) if (n % i == 0) {
			ans += BITSUM(i, m);
			if (i != n / i) ans += BITSUM(n / i, m);
		}
		
		print(ans, m);
	}
	
	return 0;
}

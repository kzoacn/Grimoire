#include <bits/stdc++.h>

template <class T>
void scan(T &x) {
	register char ch; register bool minus;
	x = minus = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar()) minus |= (ch == '-');
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	if (minus) x = -x;
}

int n, s[105];

int main() {
	int caseCnt; scan(caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scan(n);
		for (int i = 1; i <= n; ++i) scan(s[i]);
		
		std::sort(s + 1, s + n + 1);
		if (n < 10 || n > 13) {
			puts("No"); continue;
		}
		if (s[1] != 1 || s[2] != 1) {
			puts("No"); continue;
		}
		bool flag = 0;
		for (int i = 3; i < n; ++i)
			if (s[i] - s[i - 1] > 2) {
				flag = 1; puts("No"); break;
			}
		
		if (!flag) puts("Yes");
	}
	
	return 0;
}

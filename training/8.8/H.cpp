#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
char s[MAXN];
int n, m, k, testcase;

typedef long long LL;

set<LL> S;

bool f = 0;

inline int get_p(char s[], int n) {
	S.clear();
	for (int l = 1; l <= n; ++l) {
		for (int i = 0; i + l - 1 < n; ++i) {
			int j = i + l - 1;
			bool flag = true;
			for (int k = 1; k <= l; ++k) {
				if (s[i + k - 1] != s[j - k + 1]) {
					flag = false;
				}
			}
			if (flag) {
				LL mask = 0;
				for (int k = i; k <= j; ++k) {
					mask *= 3LL;
					if (s[k] == 'A') {
						mask += 1;
					} else {
						mask += 2;
					}
				}
				S.insert(mask);
			}
		}
	}
	return S.size();
}

inline void solve(int n, int m) {
	for (int mask = 0; mask < 1 << n; ++mask) {
		for (int i = 0; i < n; ++i) {
			if (mask & (1 << i)) {
				s[i] = 'A';
			} else {
				s[i] = 'B';
			}
		}
		s[n] = 0;
		if (get_p(s, n) == m) {
//f = 1;
//cout << get_p(s, n) << endl;
			puts(s);
			return;
		}
	}
	puts("Impossible");
}

int main() {
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d%d%d", &n, &m, &k);
		printf("Case #%d:\n", cs);
		if (k == 1) {
			if (n == m) {
				for (int i = 0; i < n; ++i) {
					putchar('A');
				}
				puts("");
			} else {
				puts("Impossible");
			}
			continue;
		}
		if (k > 2) {
			if (m == 1) {
				if (n == 1) {
					puts("A");
				} else {
					puts("Impossible");
				}
				continue;
			}
			if (m == 2) {
				if (n == 2) {
					puts("AB");
				} else {
					puts("Impossible");
				}
			} else {
				if (m > n) {
					puts("Impossible");
				} else {
					s[n] = 0;
					for (int i = n - m, c = 2; i >= 0; --i, c = (c - 1 + 3) % 3) {
						s[i] = 'A' + c;
					}
					for (int c = 0, i = n - m + 1; i < n; ++i, c = (c + 1) % 2) {
						s[i] = 'A' + c;
					}
					puts(s);
				}
			}
			continue;
		}
		if (n == m) {
			for (int i = 0; i < n; ++i) putchar('A');
			puts("");
			continue;
		}
		if (n <= 8) {
			solve(n, m);//checker
		} else {
			if (m > n || m < 8) {
				puts("Impossible");
			} else {
				s[0] = 'B';
				s[1] = 'B';
				s[2] = 'A';
				s[3] = 'A';
				s[4] = 'B';
				s[5] = 'A';
				for (int i = 0; i < m - 8; ++i) {
					putchar('B');
				}
				for (int i = 0, j = 0; i < n - m + 8; ++i, j = (j + 1 + 6) % 6) {
					putchar(s[j]);
				}
				puts("");
			}
			/*if (m > n || m < (n - 4 + 1) / 2) {
				puts("Impossible");
			} else {
				int p = m - 5, q = n - p - 4;
				for (int i = 0; i < p; ++i) {
					s[i] = 'A';
				}
				s[p] = 'B';
				s[p + 1] = 'A';
				s[p + 2] = 'B';
				s[p + 3] = 'B';
				for (int i = 0; i < q; ++i) {
					s[p + 4 + i] = 'A';
				}
				s[n] = 0;
				puts(s);
			}*/
		}
	}
}

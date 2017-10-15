#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5;

bitset<MAXN> t[MAXN], a[MAXN], b[MAXN];

int n, m, q, who[MAXN], f[MAXN], ans[MAXN];

char s[MAXN];

int main() {
	while (scanf("%d%d%d", &n, &m, &q), n || m || q) {
		for (int i = 1; i <= q; ++i) {
			a[i].reset();
			b[i].reset();
			scanf(" %s", s + 1);
			for (int j = 1; j <= n; ++j) {
				a[i][j] = s[j] - '0';
			}
			t[i] = a[i];
			scanf(" %s", s + 1);
			for (int j = 1; j <= m; ++j) {
				b[i][j] = s[j] - '0';
			}
			
			if (i > 1) {
				a[i] ^= t[i - 1];
			}
		}
		
		for (int i = 1; i <= m; ++i) {
			ans[i] = -1;
		}
		
		for (int i = 1; i <= n; ++i) {
			a[q + 1][i] = 1;
		}
		for (int i = 1; i <= m; ++i) {
			b[q + 1][i] = 1;
		}
		++q;
		memset(f, 0, sizeof(f));
		int now = 0;
		for (int i = 1; i <= n; ++i) {
			int id = -1;
			for (int j = now + 1; j <= q; ++j) {
				if (a[j][i] == 1) {
					id = j; 
					break;
				}
			}
			if (id == -1) {
				f[i] = 1;
				continue;
			}
			++now;
			who[now] = i;
			swap(a[now], a[id]);
			swap(b[now], b[id]);
			for (int j = 1; j <= q; ++j) {
				if (j == now || a[j][i] == 1) {
					continue;
				}
				a[j] ^= a[now];
				b[j] ^= b[now];
			}
		}
		
		for (int i = now; i; --i) {
			int id = -1;
			for (int j = who[i] + 1; j <= n; ++j) {
				if (a[i][j] == 1) {
					id = j;
					break;
				}
			}
			if (id != -1) {
				for (int j = 1; j <= n; ++j) {
					if (a[i][j] == 1) {
						f[j] = 1;
					}
				}
				continue;
			}
			for (int j = 1; j <= m; ++j) {
				if (b[i][j] == 1) {
					ans[j] = who[i];
				}
			}
		}
		
		for (int i = 1; i <= m; ++i) {
			if (ans[i] == -1) {
				putchar('?');
				continue;
			}
			if (ans[i] < 11) {
				putchar(ans[i] + '0' - 1);
			}
			if (ans[i] > 10) {
				putchar(ans[i] - 11 + 'A');
			}
		}
		puts("");
	}
}

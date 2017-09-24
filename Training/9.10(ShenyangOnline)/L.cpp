#include <bits/stdc++.h>

template <class T>
void scan(T &x) {
	register char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

int n;
int a[1000005 << 1], b[1000005 << 1];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scan(a[i]); a[n + i] = a[i];
		}
		for (int i = 1; i <= n; ++i) {
			scan(b[i]); b[n + i] = b[i];
		}
		
		int sum = 0, suma = 0, ans = 0, res = 0;
		
		for (int l = 1, r = 1; l <= n; ++l) {
			while (r - l < n && sum >= 0) {
				sum += a[r] - b[r];
				suma += a[r];
				++r;
			}
			
			if (suma > ans) {
				ans = suma;
				res = l - 1;
			}
			
			sum -= a[l] - b[l];
			suma -= a[l];
		}
		printf("%d\n", res);
	}
	
	return 0;
}

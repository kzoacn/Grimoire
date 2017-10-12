#include <bits/stdc++.h>

template <class T>
void scan(T &x) {
	register char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

std::map<int, int> A, cntA;

int n, m;

int mx[1005][1005];
int cnt[1005][1005];

int main() {
	int caseCnt; scan(caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		A.clear(); cntA.clear();
		
		scan(n); scan(m);
		for (int a, b, i = 1; i <= n; ++i) {
			scan(a); scan(b);
			if (A.count(b)) {
				int t = A[b];
				if (t == a) ++cntA[b];
				else if (t < a) {
					A[b] = a;
					cntA[b] = 1;
				}
			}
			else {
				A[b] = a;
				cntA[b] = 1;
			}
		}
		
		memset(mx, 0, sizeof mx);
		memset(cnt, 0, sizeof cnt);
		for (int a, b, c, i = 1; i <= m; ++i) {
			scan(a); scan(b); scan(c);
			if (A.count(c)) {
				int t = A[c];
				if (t == mx[a][b]) cnt[a][b] += cntA[c];
				else if (t > mx[a][b]) {
					mx[a][b] = t;
					cnt[a][b] = cntA[c];
				}
			}
		}
		
		int ans = 0;
		
		for (int i = 1000; i; --i)
			for (int j = 1000; j; --j) {
				if (mx[i][j] && std::max(mx[i + 1][j], mx[i][j + 1]) < mx[i][j]) ans += cnt[i][j];
				
				mx[i][j] = std::max(mx[i][j], std::max(mx[i + 1][j], mx[i][j + 1]));
			}
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}

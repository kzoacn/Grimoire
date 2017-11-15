#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11111;
int idp[MAXN], idq[MAXN], p, q;

int main() {
	freopen("drunkard.in", "r", stdin);
	freopen("drunkard.out", "w", stdout);
	
	while (scanf("%d%d", &p, &q), p) {
		int t1 = q - 1 - p, t2 = p - 1;
		int n = t1 + t2 + 1 + 2;
//cout << t1 << " " << t2 << endl;
		idp[0] = 1;
		for (int i = 1; i <= t1; ++i) {
			idp[i] = i + 1;
		}
		idp[t1 + 1] = n - 1;
		idq[0] = 1;
		for (int i = 1; i <= t2; ++i) {
			idq[i] = t1 + 1 + i;
		}
		idq[t2 + 1] = n;
		
		printf("%d\n", 1 + t1 + t2 + 2);
		printf("%d %d\n", idp[1], idq[1]);
		for (int i = 1; i <= t1; ++i) {
			printf("%d %d\n", idp[i - 1], idp[i + 1]);
		}
		for (int i = 1; i <= t2; ++i) {
			printf("%d %d\n", idq[i - 1], idq[i + 1]);
		}
	}
}

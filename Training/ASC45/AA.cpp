#include <bits/stdc++.h>

using namespace std;

int n, A[1005], B[1005];

bool check(int x) {
	while (x > 1) {
		if (x & 1) return 0;
		x >>= 1;
	}
	return 1;
}

int main() {
	freopen("analogous.in", "r", stdin);
	freopen("analogous.out", "w", stdout);
	
	while (cin >> n && n) {
		if (!check(n)) {
			puts("No");
			continue;
		}
		puts("Yes");
		
		A[1] = 1; A[2] = 4;
		B[1] = 2; B[2] = 3;
		
		int key = 4;
		
		for (int l = 4; l <= n; l <<= 1) {
			int hf = l >> 1;
			for (int j = 1; j <= hf; ++j) {
				A[hf + j] = B[j] + key;
				B[hf + j] = A[j] + key;
			}
			key <<= 1;
		}
		
		for (int i = 1; i <= n; ++i)
			printf("%d%c", A[i], " \n"[i == n]);
		for (int i = 1; i <= n; ++i)
			printf("%d%c", B[i], " \n"[i == n]);
	}
	
	return 0;
}

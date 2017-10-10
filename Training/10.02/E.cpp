#include <bits/stdc++.h>

typedef long long ll;

const int Mod = 20140518;

struct Matrix {
	int r, c, mat[11][11];
	
	void clear() {
		memset(mat, r = c = 0, sizeof mat);
	}
	
	Matrix() {
		clear();
	}
	
	Matrix operator * (const Matrix &rhs) {
		Matrix res; res.r = r; res.c = rhs.c;
		for (int i = 1; i <= res.r; ++i)
			for (int j = 1; j <= res.c; ++j) {
				ll tmp = 0;
				for (int k = 1; k <= c; ++k)
					tmp += 1ll * mat[i][k] * rhs.mat[k][j];
				res.mat[i][j] = tmp % Mod;
			}
		return res;
	}
	
	void unit(int x) {
		clear();
		r = c = x;
		for (int i = 1; i <= x; ++i)
			mat[i][i] = 1;
	}
} A, B;

Matrix qpow(Matrix a, ll x) {
	Matrix res; res.unit(a.r);
	for (; x; x >>= 1) {
		if (x & 1) res = res * a;
		a = a * a;
	}
	return res;
}

ll n; int k;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%lld%d", &n, &k); ++k;
		
		B.clear();
		B.r = k - 1, B.c = 1;
		B.mat[1][1] = k;
		
		A.clear();
		A.r = A.c = k - 1;
		for (int j = 1; j <= k - 1; ++j) {
			if (j != k - 1) A.mat[j + 1][j] = k - j;
			for (int t = 1; t <= j; ++t)
				A.mat[j - t + 1][j] = 1;
		}
		
		B = qpow(A, n - 1) * B;
		
		int ans = 0;
		for (int i = 1; i <= k - 1; ++i)
			ans = (ans + B.mat[i][1]) % Mod;
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}

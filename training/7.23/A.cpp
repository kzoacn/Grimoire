#include <bits/stdc++.h>

typedef long long ll;

const int Mod = 1e9 + 7;

struct Matrix {
	int r, c;
	ll mat[6][6];
	
	Matrix(int r = 0, int c = 0): r(r), c(c) {
		memset(mat, 0, sizeof mat);
	}
	
	Matrix operator * (const Matrix &rhs) const {
		Matrix res(r, rhs.c);
		for (int i = 1; i <= r; ++i)
			for (int j = 1; j <= rhs.c; ++j)
				for (int k = 1; k <= c; ++k)
					res.mat[i][j] = (res.mat[i][j] + mat[i][k] * rhs.mat[k][j]) % Mod;
		return res;
	}
	
	void unit(int l) {
		r = c = l;
		for (int i = 1; i <= l; ++i)
			mat[i][i] = 1;
	}
} A, B;

Matrix qpow(Matrix a, ll x) {
	Matrix res = Matrix(); res.unit(a.r);
	for (; x; x >>= 1) {
		if (x & 1) res = res * a;
		a = a * a;
	}
	return res;
}

ll n, a0, ax, ay, b0, bx, by;

int main() {
	while (~scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &a0, &ax, &ay, &b0, &bx, &by)) {
		if (n == 0) {
			puts("0");
			continue;
		}
		A = Matrix(5, 5);
		A.mat[1][1] = 1;
		A.mat[2][1] = ay, A.mat[2][2] = ax;
		A.mat[3][1] = by, A.mat[3][3] = bx;
		A.mat[4][1] = ay * by % Mod, A.mat[4][2] = ax * by % Mod, A.mat[4][3] = ay * bx % Mod, A.mat[4][4] = ax * bx % Mod;
		A.mat[5][4] = A.mat[5][5] = 1;
		
		B = Matrix(5, 1);
		B.mat[1][1] = 1;
		B.mat[2][1] = a0;
		B.mat[3][1] = b0;
		B.mat[4][1] = a0 * b0 % Mod;
		
		printf("%lld\n", (qpow(A, n) * B).mat[5][1]);
	}
}

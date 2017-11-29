#include <bits/stdc++.h>

typedef long long LL;

const LL Mod = 1234567891LL;
LL matmod;

LL n, m, K, ks[15];

struct Matrix {
	LL mat[15][15];
	int r, c;
	
	void reset() {
		r = c = 0;
		memset(mat, 0, sizeof mat);
	}
	
	Matrix() {
		reset();
	}
	
	Matrix operator * (const Matrix &oth) const {
		Matrix res; res.r = r; res.c = oth.c;
		for (int i = 1; i <= res.r; ++i)
			for (int j = 1; j <= res.c; ++j) {
				res.mat[i][j] = 0;
				for (int k = 1; k <= c; ++k)
					res.mat[i][j] += mat[i][k] * oth.mat[k][j];
				res.mat[i][j] %= matmod;
			}
		return res;
	}
	
	void unit(int nn) {
		r = c = nn;
		for (int i = 1; i <= nn; ++i)
			for (int j = 1; j <= nn; ++j)
				mat[i][j] = (i == j);
	}
} A, B;

LL qpow(LL a, LL x) {
	LL res = 1;
	for (; x > 0; x >>= 1) {
		if (x & 1) res = res * a % Mod;
		a = a * a % Mod;
	}
	return res;
}

Matrix matrix_pow(Matrix a, LL x) {
	Matrix res; res.unit(a.r);
	for (; x > 0; x >>= 1) {
		if (x & 1) res = res * a;
		a = a * a;
	}
	return res;
}

int left[3], mods[3] = {90, 3607, 3803};

LL dp[10005];

LL Solve(LL D) {
	matmod = D;
	LL dnd = D + n % D;
//	LL dnd = n;
	
	dp[0] = 1;
	for (int i = 1; i <= dnd; ++i) {
		dp[i] = 0;
		for (int j = 1; j <= K; ++j) if (i >= ks[j])
			dp[i] = (dp[i] + (i - ks[j] + 1) * dp[i - ks[j]]) % D;
	}
	
	if (n <= dnd) return dp[n];
	
	A.reset(); B.reset();
	
//	std::cerr << "sdf" << std::endl;
	
	A.unit(10);
	for (int t = dnd + 1; t <= dnd + D; ++t) {
		static Matrix tmp;
		
		tmp.reset();
		tmp.r = tmp.c = 10;
		for (int i = 1; i <= K; ++i)
			tmp.mat[1][ks[i]] = (t - ks[i] + 1) % D;
		for (int i = 2; i <= 10; ++i)
			tmp.mat[i][i - 1] = 1;
		A = tmp * A;
	}
	
//	std::cerr << "ddd" << std::endl;
	
	B.r = 10, B.c = 1;
	for (int i = 1; i <= 10; ++i)
		B.mat[i][1] = dp[dnd - i + 1];
	
//	std::cerr << (n - n % D) / D - 1 << std::endl;
	
	A = matrix_pow(A, (n - n % D) / D - 1);
	B = A * B;
	
//	std::cerr << "snjf" << std::endl;
	
	return B.mat[1][1];
}

int main() {
#ifndef LOCAL
	freopen("stairs.in", "r", stdin);
	freopen("stairs.out", "w", stdout);
#endif
	
	std::cin >> n >> m >> K;
	for (int i = 1; i <= K; ++i)
		std::cin >> ks[i];
	
	for (int i = 0; i < 3; ++i) {
		left[i] = Solve(mods[i]);
//		std::cerr << left[i] << std::endl;
	}
	
//	std::cerr << "ends" << std::endl;
	
	for (LL i = left[2]; ; i += mods[2])
		if (i % mods[0] == left[0] && i % mods[1] == left[1]) {
			printf("%lld\n", qpow(m, i));
			break;
		}
	
	return 0;
}

// MOD is the given module
// Do not depend on LL * LL % LL
inline int CRT(int *a) {
	static int x[N];
	for (int i = 0; i < N; i ++) {
		x[i] = a[i];
		for (int j = 0; j < i; j ++) {
			int t = (x[i] - x[j] + mod[i]) % mod[i];
			if (t < 0) t += mod[i];
			x[i] = 1LL * t * Inv[j][i] % mod[i];
		}
	}
	int sum = 1, ret = x[0] % MOD;
	for (int i = 1; i < N; i ++) {
		sum = 1LL * sum * mod[i - 1] % MOD;
		ret += 1LL * x[i] * sum % MOD;
		if (ret >= MOD) ret -= MOD;
	}
	return ret;
}
for (int i = 0; i < N; i ++)
	for (int j = i + 1; j < N; j ++) {
		Inv[i][j] = fpw(mod[i], mod[j] - 2, mod[j]);
	}

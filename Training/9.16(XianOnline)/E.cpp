#include <bits/stdc++.h>

typedef unsigned long long ull;
const int Mod = 1e9 + 7;

int sum[65];
int pw2[65];

int qpow(int a, int x) {
	int res = 1;
	for (; x; x >>= 1) {
		if (x & 1) res = 1ll * res * a % Mod;
		a = 1ll * a * a % Mod;
	}
	return res;
}

void pretreatment() {
	int inv2 = qpow(2, Mod - 2);
	
	pw2[0] = 1;
	for (int i = 1; i < 64; ++i)
		pw2[i] = (pw2[i - 1] << 1) % Mod;
	
	sum[0] = 0;
	for (int i = 1; i <= 64; ++i)
		sum[i] = (pw2[i] - 1ll) * pw2[i] % Mod * inv2 % Mod;
}

int BIT(ull x) {
	int res = 0;
	while (x) {
		++res; x >>= 1;
	}
	return res;
}

int DP(ull n, int bit, int presum) {
	if (!bit) return 0;
	
	int this_bit = (bool)(n & (1ull << (bit - 1))); n &= ~(1ull << (bit - 1));
	
	if (this_bit == 0) return DP(n, bit - 1, (presum << 1) % Mod);
	
	return (DP(n, bit - 1, (presum << 1) % Mod) + (1ll * presum * pw2[bit] + pw2[bit - 1]) % Mod * pw2[bit - 1] + sum[bit - 1]) % Mod;
}

int solve(ull n) {
	int bit = BIT(n);
	
//	std::cerr << bit << " " << sum[bit - 1] << std::endl;
	
	return (1ll * sum[bit - 1] + DP(n & ~(1ull << (bit - 1)), bit - 1, 0) + n) % Mod;
}

int main() {
	pretreatment();
	
	for (ull n; ~scanf("%llu", &n); )
		printf("%d\n", solve(n - 1));
	
	return 0;
}

#include <bits/stdc++.h>

template <class T>
void scan(T &x) {
	static char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

typedef long long ll;

ll pw[40][50], cnt[40][50];
int lim[40];

void pretreatment() {
	for (int i = 1; i <= 36; ++i) {
		lim[i] = 40;
		pw[i][0] = 1;
		for (int j = 1; j <= 40; ++j) {
			pw[i][j] = pw[i][j - 1] * i;
			if (pw[i][j] > (int)1e9) {
				lim[i] = j;
				break;
			}
		}
	}
	
	for (int i = 2; i <= 36; ++i) {
		cnt[i][0] = 1; // ---
		for (int j = 1; j <= lim[i]; ++j)
			cnt[i][j] = pw[i][(j - 1) / 2] * (i - 1);
	}
}

int Bit, Base;

ll DP(int x, int bit, int mid, bool fir) {
	if (bit < mid) return 0;
	
	int this_bit = x / pw[Base][bit - 1]; x %= pw[Base][bit - 1];
	ll res = (this_bit - fir) * pw[Base][(Bit - (Bit - bit + 1) * 2 + 1) / 2];
	res += DP(x, bit - 1, mid, 0);
	return res;
}

int dig[50];

int BIT(int x, int base) {
	int res = 0;
	while (x > 0) {
		++res;
		dig[res] = x % base;
		x /= base;
	}
	return res;
}

ll Calc(int lim, int base) {
	if (lim == 0) return 0;
	
	int bit = BIT(lim, base);
	
	ll res = lim;
	for (int i = 1; i < bit; ++i)
		res += cnt[base][i] * (base - 1);
	
	int mid = (bit >> 1) + 1;
	
	Bit = bit; Base = base;
	
//	fprintf(stderr, "DP: %lld\n", DP(lim, bit, mid, 1));
	
	res += DP(lim, bit, mid, 1) * (base - 1);
	
	res += base - 1;
	
//	fprintf(stderr, "res = %lld\n", res);
	
	for (int i = mid, j = bit - mid + 1; i <= bit && j >= 1; ++i, --j) {
		if (dig[i] > dig[j]) {
			res -= base - 1; break;
		}
		else if (dig[i] < dig[j]) break;
	}
	
//	fprintf(stderr, "res = %lld\n", res);
	
	return res;
}

int main() {
	pretreatment();
	
	int caseCnt; scan(caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int L, R, l, r;
		
		scan(L); scan(R); scan(l); scan(r);
		
		ll ans = 0;
		
		for (int i = l; i <= r; ++i) {
//			fprintf(stderr, "%d-base: %lld - %lld\n", i, Calc(R, i), Calc(L - 1, i));
			ans += Calc(R, i) - Calc(L - 1, i);
		}
		
		printf("Case #%d: %lld\n", kase, ans);
	}
	
	return 0;
}

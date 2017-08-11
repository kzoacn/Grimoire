#include <bits/stdc++.h>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const long long MOD = 1E9 + 7;

long long B, Q, A, D, N, M;
long long Pw(long long a,long long b,long long p){
	long long v=1;
	for(;b;b>>=1,a=a*a%p)if(b&1)v=v*a%p;
	return v;
}
long long inverse (const long long &x){
	return Pw(x,MOD-2,MOD);   
//	f (x == 1) return 1;

//	return (MOD - MOD / x) * inverse (MOD % x) % MOD;
}

long long fpm (long long x, long long n) {
	long long ans = 1, mul = x;
	while (n) {
		if (n & 1) ans = ans * mul % MOD;
		mul = mul * mul % MOD;
		n >>= 1;
	}
	return ans;
}

long long C (long long n, long long m) {
	long long ans = 1;
	if (n < 0 || m < 0 || n < m) return 0;
	for (long long i = n; i >= n - m + 1; --i)
		ans = ans * i % MOD;
	for (long long i = 1; i <= m; ++i) 
		ans = ans * inverse (i) % MOD;
	return ans;
}

long long cc[11000];

long long f (long long n, long long m) {
	if (n < 0 || m < 0) return 0;
	if (Q % MOD == 1) return C (n + m + 1, n + 1) * B % MOD;
	if (n == 0) { cc[0] = 1; return (fpm (Q, m + 1) - 1) * inverse (Q - 1) % MOD * B % MOD; }
	long long lst = f (n - 1, m);
	cc[n] = cc[n - 1] * (n + m) % MOD * inverse (n) % MOD;
	long long ans = (MOD - B * inverse (Q - 1) % MOD * cc[n] % MOD) % MOD + Q * lst % MOD * inverse (Q - 1) % MOD;
	return ans % MOD;
}

int main () {
	int T;
	scanf ("%d", &T);
	for (int t = 0; t < T; ++t) {
		scanf (LL LL LL LL LL LL, &B, &Q, &A, &D, &N, &M);
		if (N == 0 && M == 0) {
			printf ("Case #%d: " LL "\n", t + 1, 0LL);
			continue;
		}
		if (N == 0) {
			printf ("Case #%d: " LL "\n", t + 1, fpm (Q, M - 1) * B);
			continue;
		}
		if (M == 0) {
			printf ("Case #%d: " LL "\n", t + 1, (A + D * (N - 1)) % MOD);
			continue;
		}
		long long a1 = C (N - 1 + M, N - 1) * A % MOD;
		long long a2 = C (N - 1 + M, N - 2) * D % MOD;
		long long a3 = f (N - 1, M - 1) % MOD;
		std::cout << a3 << std::endl;
		long long ans = (a1 + a2 + a3) % MOD;
		printf ("Case #%d: " LL "\n", t + 1, ans);
	}
}

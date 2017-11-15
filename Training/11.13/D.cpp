#include <bits/stdc++.h>

typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 1e4 + 5;

int n;
ULL seq[MAXN], bp[10];

std::vector<LL> ans;

LL Decode(ULL x) {
	LL res = 1;
	if (x & 1) {
		res = -1;
		x = (x >> 1) + 1;
	}
	else x >>= 1;
	res = (LL)((long double)res * x);
	return res;
}

int main() {
	const ULL base = 1ULL << 7;
	
	bp[0] = 1;
	for (int i = 1; i < 10; ++i)
		bp[i] = bp[i - 1] * base;
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%llu", seq + i);
	
	ULL tmp = 0;
	int bit = 0;
	for (int i = 1; i <= n; ++i) {
		if (seq[i] < 128U) {
			tmp += seq[i] * bp[bit++];
			ans.push_back(Decode(tmp));
			tmp = 0;
			bit = 0;
		}
		else tmp += (seq[i] - 128) * bp[bit++];
	}
	
	for (LL i: ans)
		printf("%lld\n", i);
	
	return 0;
}

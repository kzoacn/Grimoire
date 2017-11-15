#include <bits/stdc++.h>

typedef long long LL;
typedef __int128 Long;

const LL INF = 0x3f3f3f3f3f3f3f3fLL;

LL n;
int k;

LL Calc(int x, int y) {
	LL peo = x;
	LL d = 1;
	for (; peo + y < n; ++d)
		peo += std::min(peo, (n - peo) >> 1);
	return d;
}

int main() {
	std::cin >> n >> k;
	
	LL ans = INF;
	
	for (int i = 1; i < k; ++i)
		ans = std::min(ans, Calc(i, k - i));
	
	std::cout << ans << std::endl;
	
	return 0;
}

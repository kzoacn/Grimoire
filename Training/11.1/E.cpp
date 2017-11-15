#include <bits/stdc++.h>

typedef long long LL;

LL n, m;

const LL Match[17] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6, 6, 5, 4, 5, 5, 4, 78}; // 16: sum

LL iza[10];

int main() {
	iza[0] = 1;
	for (int i = 1; i < 10; ++i) iza[i] = iza[i - 1] * 0x10;
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%lld%llX", &n, &m);
		
//		fprintf(stderr, "%08llX\n", m);
		
		LL ans = 0;
		
		for (int b = 0; b < 8; ++b) {
			LL T = iza[b], soto = (iza[8] - m) % T;
			
			int thisBit = m / T % 0x10;
			
//			std::cerr << "tB " << thisBit << std::endl;
			
			if (n < soto) {
				ans += Match[thisBit] * n;
				
//				std::cerr << "ans = " << ans << std::endl;
				
				continue;
			}
			
			ans += Match[thisBit] * soto;
			LL nn = n - soto;
			
			for (thisBit += (bool)soto; thisBit < 0x10; ++thisBit) {
				LL tmp = std::min(nn, T);
				ans += Match[thisBit] * tmp;
				nn -= tmp;
			}
			
			LL tmp = nn / (T * 0x10);
			ans += Match[0x10] * tmp * T;
			nn %= T * 0x10;
			
			for (thisBit = 0; thisBit < 0x10; ++thisBit) {
				LL tmp = std::min(nn, T);
				ans += Match[thisBit] * tmp;
				nn -= tmp;
			}
			
//			std::cerr << "ans = " << ans << std::endl;
		}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}

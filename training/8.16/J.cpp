#include <bits/stdc++.h>

const int Mod = 530600414;

int ans[205005] = {0, 0, 0}, 
	pre[205005] = {0, 1, 0}, 
	suf[205005] = {0, 0, 0}, 
	cnt[205005] = {0, 1, 0}, 
	len[205005] = {0, 1, 2};

void presentation() {
	const int lim = 201314;
	
	for (int i = 3; i <= lim; ++i) {
		len[i] = (len[i - 1] + len[i - 2]) % Mod;
		cnt[i] = (cnt[i - 1] + cnt[i - 2]) % Mod;
		suf[i] = (suf[i - 1] + suf[i - 2] + 1ll * cnt[i - 2] * len[i - 1]) % Mod;
		pre[i] = (pre[i - 1] + pre[i - 2] + 1ll * cnt[i - 1] * len[i - 2]) % Mod;
		ans[i] = (ans[i - 1] + ans[i - 2] + 1ll * pre[i - 1] * cnt[i - 2] + 1ll * suf[i - 2] * cnt[i - 1]) % Mod;
	}
}

int main() {
	presentation();
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int n;
		
		scanf("%d", &n);
		printf("Case #%d: %d\n", kase, ans[n]);
	}
	
	return 0;
}

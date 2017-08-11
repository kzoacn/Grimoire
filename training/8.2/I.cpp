#include <bits/stdc++.h>

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll LNF = 0x3f3f3f3f3f3f3f3fll;

int ns[2], m;
int t[2][15];

int mn[2], mn_t[2], mn2[2], mn2_t[2], mn3_t[2];

int fix(int x) {
	return x > 0 ? x : 0;
}

int main() {
	freopen("I.in", "r", stdin);
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d", ns + 0, ns + 1, &m);
		
		mn_t[0] = mn_t[1] = INF;
		for (int i = 0; i < 2; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", t[i] + j);
				
				if (t[i][j] < mn_t[i]) {
					mn2[i] = mn[i];
					mn2_t[i] = mn_t[i];
					
					mn[i] = j;
					mn_t[i] = t[i][j];
				}
				else if (t[i][j] < mn2_t[i]) {
					mn2[i] = j;
					mn2_t[i] = t[i][j];
				}
			}
		
		if (m == 1) {
			std::cout << 1ll * ns[0] * t[0][1] + 1ll * ns[1] * t[1][1] << std::endl;
			continue;
		}
		
		bool flag = 0;
		
		for (int i = 1; i <= m; ++i) {
			if (t[0][i] == mn_t[0] && i != mn[0]) {
				flag = 1; break;
			}
			if (t[1][i] == mn_t[1] && i != mn[1]) {
				flag = 1; break;
			}
		}
		
		if (flag || mn[0] != mn[1]) {
			std::cout << std::max(1ll * ns[0] * mn_t[0], 1ll * ns[1] * mn_t[1]) << std::endl;
			continue;
		}
		
		flag = 0;
		
		for (int i = 1; i <= m; ++i) {
			if (t[0][i] == mn2_t[0] && i != mn2[0]) {
				flag = 1; break;
			}
			if (t[1][i] == mn2_t[1] && i != mn2[1]) {
				flag = 1; break;
			}
		}
		
		ll ans = LNF;
		
		if (flag || mn2[0] != mn2[1]) { // ???.jpg
			for (int cur = 0; cur < 2; ++cur) {
				for (int i = 0; i <= ns[cur]; ++i) {
					ll t1 = 1ll * i * mn_t[cur] + 1ll * fix(ns[cur] - i) * mn2_t[cur];
					ll cnt2 = 1ll * i * mn_t[cur] / mn2_t[cur ^ 1];
					cnt2 = std::min(cnt2, 1ll * ns[cur ^ 1]);
					ll t2 = 1ll * i * mn_t[cur] + 1ll * fix(ns[cur ^ 1] - cnt2) * mn_t[cur ^ 1];
					ans = std::min(ans, std::max(t1, t2));
				}
				for (int i = 0; i <= ns[cur]; ++i) {
					ll t1 = 1ll * i * mn2_t[cur] + 1ll * fix(ns[cur] - i) * mn_t[cur];
					ll cnt2 = 1ll * i * mn2_t[cur] / mn_t[cur ^ 1];
					cnt2 = std::min(cnt2, 1ll * ns[cur ^ 1]);
					ll t2 = 1ll * cnt2 * mn_t[cur ^ 1] + 1ll * fix(ns[cur ^ 1] - cnt2) * mn2_t[cur ^ 1];
					ans = std::min(ans, std::max(t1, t2));
				}
			}
			
			std::cout << ans << std::endl;
			continue;
		}
		
		mn3_t[0] = mn3_t[1] = INF;
		for (int i = 1; i <= m; ++i) {
			for (int j = 0; j < 2; ++j)
				if (i != mn[j] && i != mn2[j])
					mn3_t[j] = std::min(mn3_t[j], t[j][i]);
		}
		
//		std::cerr << mn[0] << " " << mn[1] << std::endl;
//		std::cerr << mn2[0] << " " << mn2[1] << std::endl;
//		std::cerr << mn3_t[0] << " " << mn3_t[1] << std::endl;
		
		for (int cur = 0; cur < 2; ++cur) {
			for (int i = 0; i <= ns[cur]; ++i) {
				ll t1 = 1ll * i * mn_t[cur] + 1ll * fix(ns[cur] - i) * mn2_t[cur];
				ll cnt2 = 1ll * i * mn_t[cur] / mn2_t[cur ^ 1];
				cnt2 = std::min(cnt2, 1ll * ns[cur ^ 1]);
				ll t2_1 = 1ll * i * mn_t[cur] + 1ll * fix(ns[cur ^ 1] - cnt2) * mn_t[cur ^ 1], 
				   t2_2 = 1ll * cnt2 * mn2_t[cur ^ 1] + (cnt2 < ns[cur ^ 1] ? mn3_t[cur ^ 1] : 0) + 1ll * fix(ns[cur ^ 1] - cnt2 - 1) * mn_t[cur ^ 1];
				ans = std::min(ans, std::max(t1, std::min(t2_1, t2_2)));
			}
			for (int i = 0; i <= ns[cur]; ++i) {
				ll t1 = 1ll * i * mn2_t[cur] + 1ll * fix(ns[cur] - i) * mn_t[cur];
				ll cnt2 = 1ll * i * mn2_t[cur] / mn_t[cur ^ 1];
				cnt2 = std::min(cnt2, 1ll * ns[cur ^ 1]);
				ll t2_1 = 1ll * i * mn2_t[cur] + 1ll * fix(ns[cur ^ 1] - cnt2) * mn2_t[cur ^ 1], 
				   t2_2 = 1ll * cnt2 * mn_t[cur ^ 1] + (cnt2 < ns[cur ^ 1] ? mn3_t[cur ^ 1] : 0) + 1ll * fix(ns[cur ^ 1] - cnt2 - 1) * mn2_t[cur ^ 1];
				
//				std::cerr << cur << " " << i << " " << t1 << " " << t2 << std::endl;
				
				ans = std::min(ans, std::max(t1, std::min(t2_1, t2_2)));
			}
		}
		
		std::cout << ans << std::endl;
	}
	
	return 0;
}

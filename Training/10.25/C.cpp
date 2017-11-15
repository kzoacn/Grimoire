#include <bits/stdc++.h>

const int MAXN = 5e3 + 5;

int n, a[MAXN], lis[MAXN], ideg[MAXN], tdeg[MAXN];

std::bitset<MAXN> suf[MAXN];

std::vector<int> G[MAXN];

int main() {
	while (~scanf("%d", &n)) {
		memset(ideg, 0, sizeof ideg);
		
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			
			lis[i] = 1;
			for (int j = 1; j < i; ++j) if (a[j] < a[i])
				lis[i] = std::max(lis[i], lis[j] + 1);
			
			for (int j = 1; j < i; ++j) if (a[j] < a[i] && lis[i] == lis[j] + 1) {
				G[j].push_back(i); ++ideg[i];
			}
		}
		
//		std::cerr << Cnt << std::endl;
		
		for (int i = n; i; --i) {
			static std::queue<int> que;
			
			for (int j = 1; j <= n; ++j)
				tdeg[j] = ideg[j];
			
			suf[i].reset();
			
			que.push(i);
			while (!que.empty()) {
				int now = que.front(); que.pop();
				suf[i][now] = 1;
				for (int to: G[now]) {
					if (!--tdeg[to])
						que.push(to);
				}
			}
		}
		
		int presum = 0;
		
		for (int del = 1; del <= n; ++del) {
			int ans = presum;
			presum ^= lis[del] * lis[del];
			
			for (int i = del + 1; i <= n; ++i)
				if (suf[del][i])
					ans ^= (lis[i] - 1) * (lis[i] - 1);
				else
					ans ^= lis[i] * lis[i];
			
			printf("%d%c", ans, " \n"[del == n]);
		}
	}
	
	return 0;
}

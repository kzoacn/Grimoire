#include <bits/stdc++.h>

typedef unsigned long long ull;
typedef std::pair<ull, int> pui;

#define mp std::make_pair

ull bp[10];

int n, m;
int h[10];
int l[5], dlt[5];

std::unordered_map<ull, int> mp1, mp2;

void decode(ull x, int hh[]) {
	for (int i = 0; i < n; ++i)
		hh[i] = x / bp[i] % 12;
}

void BFS(ull st, std::unordered_map<ull, int> &mapp) {
	static std::queue<pui> que;
	static pui now;
	static ull nxt;
	static int hh[10], hh2[10], step;
	
	que.push(mp(st, 0)); mapp.insert(mp(st, 0));
	while (!que.empty()) {
		now = que.front(); que.pop();
		step = now.second;
		if (step == 4) continue;
		decode(now.first, hh);
		for (int i = 1; i <= m; ++i) {
			for (int comb = (1 << l[i]) - 1; comb < (1 << n); ) {
				nxt = 0;
				for (int j = 0; j < n; ++j) {
					hh2[j] = (hh[j] + ((comb & (1 << j)) ? dlt[i] : 0)) % 12;
				}
				std::sort(hh2, hh2 + n);
				for (int j = 0; j < n; ++j) {
					nxt += hh2[j] * bp[j];
				}
				
				if (!mapp.count(nxt)) {
					mapp.insert(mp(nxt, step + 1));
					que.push(mp(nxt, step + 1));
				}
				
				int x = comb & -comb, y = comb + x;
				comb = (((comb & ~y) / x) >> 1) | y;
			}
		}
	}
}

int main() {
	bp[0] = 1;
	for (int i = 1; i <= 8; ++i) bp[i] = bp[i - 1] * 12;
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		
		ull st = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", h + i); h[i] %= 12;
		}
		std::sort(h, h + n);
		for (int i = 0; i < n; ++i) {
			st += h[i] * bp[i];
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", l + i, dlt + i);
			dlt[i] = (dlt[i] + 12) % 12;
		}
		
		mp1.clear(); mp2.clear();
		
		BFS(st, mp1);
		for (int i = 1; i <= m; ++i)
			dlt[i] = (12 - dlt[i]) % 12;
		BFS(0, mp2);
		
		int ans = 9;
		for (std::unordered_map<ull, int>::iterator it = mp1.begin(); it != mp1.end(); ++it) {
			if (mp2.count(it->first))
				ans = std::min(ans, it->second + mp2[it->first]);
		}
		printf("%d\n", ans == 9 ? -1 : ans);
	}
	
	return 0;
}

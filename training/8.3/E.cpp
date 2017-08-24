#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int n, H, W;

struct Tower {
	int p, h;
	
	Tower() {}
	Tower(int p, int h): p(p), h(h) {}
	
	bool operator < (const Tower &rhs) const {
		return p < rhs.p;
	}
	
	void scan() {
		scanf("%d%d", &p, &h);
	}
} tower[55];

int dp_l[55][505], dp_r[55][505];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d", &n, &H, &W);
		int highest = 0;
		for (int i = 1; i <= n; ++i) {
			tower[i].scan();
			highest = std::max(highest, tower[i].h);
		}
		std::sort(tower + 1, tower + n + 1);
		
		tower[0].h = tower[n + 1].h = INF;
		
		memset(dp_l, 0x3f, sizeof dp_l);
		memset(dp_r, 0x3f, sizeof dp_r);
		for (int i = n; i; --i) {
			if (tower[i].h == highest) {
				dp_l[i][tower[i].p] = 0;
				continue;
			}
			
			if (tower[i + 1].h - tower[i].h > H) continue;
			
			for (int p = 1; p <= 500; ++p)
				for (int q = p + 1; q <= 500 && q - p <= W; ++q)
					dp_l[i][p] = std::min(dp_l[i][p], dp_l[i + 1][q] + tower[i].h * std::abs(p - tower[i].p));
		}
		for (int i = 1; i <= n; ++i) {
			if (tower[i].h == highest) {
				dp_r[i][tower[i].p] = 0;
				continue;
			}
			
			if (tower[i - 1].h - tower[i].h > H) continue;
			
			for (int p = 500; p; --p)
				for (int q = p - 1; q && p - q <= W; --q)
					dp_r[i][p] = std::min(dp_r[i][p], dp_r[i - 1][q] + tower[i].h * std::abs(p - tower[i].p));
		}
		
		int ans = INF;
		for (int i = 1; i <= n; ++i) if (tower[i].h <= H)
			for (int p = 1; p <= 500; ++p)
				ans = std::min(ans, std::min(dp_l[i][p], dp_r[i][p]));
		
		if (ans == INF) ans = -1;
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}

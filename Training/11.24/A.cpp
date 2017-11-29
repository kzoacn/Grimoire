#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int brd[4][2] = {{1, 0}, {0, 1}, {0, 0}, {0, 0}};

inline int sgn(int x) { return x < 0 ? -1 : x > 0; }

int n, m, X, Y;

int sorted_x[15], sorted_y[15];
int nn, mm;

inline void pushx(int x) {
	if (x < 1 || x > n) return;
	sorted_x[++nn] = x;
}

inline void pushy(int y) {
	if (y < 1 || y > m) return;
	sorted_y[++mm] = y;
}

inline int hx(int x) {
	return std::lower_bound(sorted_x + 1, sorted_x + nn + 1, x) - sorted_x;
}

inline int hy(int y) {
	return std::lower_bound(sorted_y + 1, sorted_y + mm + 1, y) - sorted_y;
}

bool Check(int mid) {
	nn = mm = 0;
	
	pushx(1); pushx(n);
	pushx(X - 1); pushx(X); pushx(X + 1);
	pushx(mid); pushx(n - mid + 1);
	
	pushy(1); pushy(m);
	pushy(Y - 1); pushy(Y); pushy(Y + 1);
	pushy(mid); pushy(m - mid + 1);
	
	std::sort(sorted_x + 1, sorted_x + nn + 1);
	nn = std::unique(sorted_x + 1, sorted_x + nn + 1) - sorted_x - 1;
	
	std::sort(sorted_y + 1, sorted_y + mm + 1);
	mm = std::unique(sorted_y + 1, sorted_y + mm + 1) - sorted_y - 1;
	
	int cnt = 0;
	for (int i = 1; i <= nn; ++i) {
		for (int j = 1; j <= mm; ++j) {
			int x = sorted_x[i], y = sorted_y[j];
			if (x == X && y == Y) continue;
			for (int t = 0; t < 4; ++t) {
				int dx = sgn(X - x), dy = sgn(Y - y);
				if (dx == drct[t][0] && dy == drct[t][1]) continue;
				int tmp = ((n + 1) * brd[t][0] - x) * drct[t][0] + ((m + 1) * brd[t][1] - y) * drct[t][1];
				if (tmp <= mid) {
					++cnt; break;
				}
			}
		}
	}
	return cnt == nn * mm - 1;
}

int main() {
	while (~scanf("%d%d%d%d", &n, &m, &X, &Y)) {
		int ans = std::max(n, m), L = 1, R = ans - 1;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (Check(mid)) ans = mid, R = mid - 1;
			else L = mid + 1;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}

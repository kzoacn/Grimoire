#include <bits/stdc++.h>
typedef double LD;
const LD eps = 1e-9;

int sgn(LD x) { return x < -eps ? -1 : x > eps; }

template <class T>
T sqr(const T &x) {
	return x * x;
}

LD Sqrt(LD x) {
	return x < 0 ? 0 : std::sqrt(x);
}

int n;
int x[50005], r[50005];

LD h[50005];

LD Calc(LD deltaX, LD r1, LD r2) {
	if (r1 > r2) std::swap(r1, r2);
	LD cos_theta = (sqr(deltaX) + sqr(r2) - sqr(r1)) / (2 * deltaX * r2);
	LD sin_theta = Sqrt(1 - sqr(cos_theta));
	return r2 * sin_theta * 2;
}

LD st[50005][16];

void get_st_table() {
	for (int t = 1; t <= 15; ++t) {
		for (int i = 1; i <= n - (1 << t); ++i) {
			st[i][t] = std::min(st[i][t - 1], st[i + (1 << (t - 1))][t - 1]);
		}
	}
}

LD Min(int L, int R) {
	/*int len = (R - L + 1);
	for (int i = 0; i <= 15; ++i)
		if ((1 << (i + 1)) > len)
			return std::min(st[L][i], st[R - (1 << i) + 1][i]);
	assert(0);
	return -1;*/
	int len = R - L + 1;
	int t = std::__lg(len);
	return std::min(st[L][t], st[R - (1 << t) + 1][t]);
} 

bool exists(int now, LD side) {
	int ll = now, rr = now;
	int L = 1, R = now - 1;
	while (L <= R) {
		int mid = (L + R) >> 1;
		if (Min(mid, now - 1) > side) ll = mid, R = mid - 1;
		else L = mid + 1;
	}
	L = now + 1, R = n - 1;
	while (L <= R) {
		int mid = (L + R) >> 1;
		if (Min(now + 1, mid) > side) rr = mid, L = mid + 1;
		else R = mid - 1;
	}
	++rr;
	LD len = (x[rr] + Sqrt(sqr(r[rr]) - sqr(side / 2))) - (x[ll] - Sqrt(sqr(r[ll]) - sqr(side / 2)));
	return len > side;
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", x + i, r + i);
		
		for (int i = 1; i < n; ++i)
			st[i][0] = h[i] = Calc(x[i + 1] - x[i], r[i], r[i + 1]);
		
		get_st_table();
		
		LD ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = std::max(ans, Sqrt(2) * r[i]);
		
		for (int i = 1; i < n; ++i) {
			LD L = ans, R = h[i];
			int TAT=100;
			while (TAT--) {
				LD mid = (L + R) / 2;
				if (!exists(i, mid)) R = mid;
				else L = mid;
			}
			ans = std::max(ans, L);
		}
		
		printf("%.10f\n", (double)ans);
	}
	
	return 0;
}

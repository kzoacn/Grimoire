#include <bits/stdc++.h>

const int MAXN = 150 + 5;

int n, m, p;
int a[MAXN][MAXN], presum[MAXN][MAXN];

int seq[MAXN];

int mx_up[MAXN], mx_down[MAXN], mx_left[MAXN], mx_right[MAXN];
int mx_r[MAXN], mx_c[MAXN];

void get_mx() {
	for (int i = 0; i <= n + 1; ++i)
		mx_up[i] = mx_down[i] = -1000;
	for (int i = 0; i <= m + 1; ++i)
		mx_left[i] = mx_right[i] = -1000;
	
	int mx;
	
	for (int l = 1; l <= n; ++l) {
		for (int r = l; r <= n; ++r) {
			mx = -1000;
			for (int i = 1; i <= m; ++i)
				seq[i] = presum[r][i] - presum[l - 1][i];
			int tmp = 0;
			for (int i = 1; i <= m; ++i) {
				tmp = std::max(tmp, 0);
				tmp += seq[i];
				mx = std::max(mx, tmp);
			}
			
			for (int i = 1; i <= l; ++i)
				mx_down[i] = std::max(mx_down[i], mx);
			for (int i = r; i <= n; ++i)
				mx_up[i] = std::max(mx_up[i], mx);
		}
	}
	
	for (int l = 1; l <= m; ++l) {
		memset(seq, 0, sizeof seq);
		for (int r = l; r <= m; ++r) {
			mx = -1000;
			for (int i = 1; i <= n; ++i)
				seq[i] += a[i][r];
			int tmp = 0;
			for (int i = 1; i <= n; ++i) {
				tmp = std::max(tmp, 0);
				tmp += seq[i];
				mx = std::max(mx, tmp);
			}
			
			for (int i = 1; i <= l; ++i)
				mx_right[i] = std::max(mx_right[i], mx);
			for (int i = r; i <= m; ++i)
				mx_left[i] = std::max(mx_left[i], mx);
		}
	}
}

int MaximumSubmatrix() {
	int res = -1000;
	for (int l = 1; l <= n; ++l) {
		for (int r = l; r <= n; ++r) {
			for (int i = 1; i <= m; ++i)
				seq[i] = presum[r][i] - presum[l - 1][i];
			int tmp = 0;
			for (int i = 1; i <= m; ++i) {
				tmp = std::max(tmp, 0);
				tmp += seq[i];
				res = std::max(res, tmp);
			}
		}
	}
	return res;
}

int dp[MAXN][MAXN][MAXN];
int maxpre[MAXN], maxsuf[MAXN];

inline int Max(int q, int w, int e, int r) {
	return std::max(std::max(q, w), std::max(e, r));
}

bool Check(int mid) {
	for (int l = 1; l <= n; ++l) {
		for (int r = l; r <= n; ++r) {
			for (int i = 1; i <= m; ++i)
				seq[i] = presum[r][i] - presum[l - 1][i];
			maxpre[0] = maxsuf[m + 1] = 0;
			for (int i = 1; i <= m; ++i)
				maxpre[i] = std::max(maxpre[i - 1] + seq[i], 0);
			for (int i = m; i; --i)
				maxsuf[i] = std::max(maxsuf[i + 1] + seq[i], 0);
			
			for (int i = 1; i <= m; ++i) {
				int tmp = seq[i] + maxpre[i - 1] + maxsuf[i + 1];
				dp[l][r][i] = std::max(tmp - mid + p, -1000);
//printf("dp[%d][%d][%d] = %d\n", l, r, i, dp[l][r][i]);
//printf("tmp = %d\n", tmp);
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		for (int l = 1; l <= n; ++l) {
			for (int r = l; r <= n; ++r) {
				dp[l][l][i] = std::max(dp[l][l][i], dp[l][r][i]);
				dp[l + 1][r][i] = std::max(dp[l + 1][r][i], dp[l][r][i]);
			}
			if (a[l][i] >= dp[l][l][i] && Max(mx_left[i - 1], mx_right[i + 1], mx_up[l - 1], mx_down[l + 1]) <= mid)
				return 1;
		}
	}
/*	
puts("========");
for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= m; ++j)
		printf("%d%c", dp[i][i][j], " \n"[j == m]);
puts("========");
*/	
	return 0;
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &p)) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j);
				presum[i][j] = presum[i - 1][j] + a[i][j];
			}
		}
		
		int ans = MaximumSubmatrix();
		get_mx();
		
//Check(7);
//return 0;
		
		int L = -1000, R = ans - 1;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (Check(mid)) ans = mid, R = mid - 1;
			else L = mid + 1;
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}

/*
3 3 -10
-100 4 4
4 -10 4
4 4 1

*/

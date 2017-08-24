#include <bits/stdc++.h>

int N;
int loc[60][60][60];
int ans[210000][6], ans_s;

bool is_valid (int x) {
	return x >= 1 && x <= N;
}

void mv (int x[3], int d[3], int p[3]) {
	int xx[3];
	for (xx[p[0]] = x[p[0]]; is_valid (xx[p[0]]); xx[p[0]] += d[p[0]])
		for (xx[p[1]] = x[p[1]]; is_valid (xx[p[1]]); xx[p[1]] += d[p[1]])
			for (xx[p[2]] = x[p[2]]; is_valid (xx[p[2]]); xx[p[2]] += d[p[2]]) {
				if (loc[xx[0]][xx[1]][xx[2]] == 1) {
					int nx[3];
					nx[0] = xx[0]; nx[1] = xx[1]; nx[2] = xx[2];
					for (int r = 0; r < 3; ++r) {
						while (is_valid (nx[p[r]] + d[p[r]])) {
							nx[p[r]] += d[p[r]];
							if (loc[nx[0]][nx[1]][nx[2]] == 1) {
								nx[p[r]] -= d[p[r]];
								break;
							}
							nx[p[r]] -= d[p[r]];
							ans[ans_s][0] = nx[0]; ans[ans_s][1] = nx[1]; ans[ans_s][2] = nx[2];
							loc[nx[0]][nx[1]][nx[2]] = 0;
							nx[p[r]] += d[p[r]];
							ans[ans_s][3] = nx[0]; ans[ans_s][4] = nx[1]; ans[ans_s][5] = nx[2];
							loc[nx[0]][nx[1]][nx[2]] = 1;
							++ans_s;
							if (ans_s > 200000) return;
						}
					}
				}
			}
}

int main () {
	int T;
	scanf ("%d", &T);
	for (int t = 0; t < T; ++t) {
		scanf ("%d", &N);
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				for (int k = 1; k <= N; ++k) {
					char tmp;
					scanf (" %c", &tmp);
					loc[i][j][k] = tmp - '0';
				}
		int p[3] = {0, 1, 2};
		int avg[3], avg_s = 0;
		avg[0] = avg[1] = avg[2] = 0;
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				for (int k = 1; k <= N; ++k)
					if (loc[i][j][k]) {
						avg[0] += i; avg[1] += j; avg[2] += k;
						++avg_s;
					}
		if (avg_s == 0) {
			printf ("Case %d: %d\n", t + 1, 0);
			goto next_case;
		}
		avg[0] = round ((double) avg[0] / avg_s);
		avg[1] = round ((double) avg[1] / avg_s);
		avg[2] = round ((double) avg[2] / avg_s);
		//avg[0] = avg[1] = avg[2] = N + 1 >> 1;
		long long div[3];
		div[0] = div[1] = div[2] = 0;
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				for (int k = 1; k <= N; ++k)
					if (loc[i][j][k]) {
						div[0] += std::abs (i - avg[0]);
						div[1] += std::abs (j - avg[1]);
						div[2] += std::abs (k - avg[2]);
					}
		std::sort (p, p + 3, [ & ] (int a, int b) { return div[a] < div[b]; });
		ans_s = 0;
		int d[3];
		for (d[0] = -1; d[0] <= 1; d[0] += 2)
			for (d[1] = -1; d[1] <= 1; d[1] += 2)
				for (d[2] = -1; d[2] <= 1; d[2] += 2) {
					mv (avg, d, p);
					if (ans_s > 200000) {
						printf ("Case %d: %d\n", t + 1, -1);
						goto next_case;
					}
				}
		printf ("Case #%d: %d\n", t + 1, ans_s);
		/*for (int i = 0; i < ans_s; ++i)
			printf ("%d %d %d %d %d %d\n", ans[i][0], ans[i][1], ans[i][2], ans[i][3], ans[i][4], ans[i][5]);*/
next_case:;
	}
}

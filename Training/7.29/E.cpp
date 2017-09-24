#include <bits/stdc++.h>

template <class T>
void scan(T &x) {
	static char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

const int MAXT = 24 * 60;

int n, m, k;
int t1[105], t_meet[105];
bool t2[MAXT + 5];

bool qualified(int t) {
	return t >= 0 && t < MAXT;
}

bool check(int t) {
	static int tt1, tt2, t2_;
	
	for (int i = 1; i <= k; ++i) {
		bool flag = 0;
		for (int j = 1; j <= n && !flag; ++j) {
			tt1 = t_meet[i] - t1[j];
			if (!qualified(tt1)) continue;
			tt2 = t - tt1;
			if (!qualified(tt2)) continue;
			t2_ = t_meet[i] - tt2;
			if (!qualified(t2_)) continue;
			if (t2[t2_]) flag = 1;
		}
		for (int j = 1; j <= n && !flag; ++j) {
			tt1 = t_meet[i] + MAXT - t1[j];
			if (!qualified(tt1)) continue;
			tt2 = t - tt1;
			if (!qualified(tt2)) continue;
			t2_ = t_meet[i] + MAXT - tt2;
			if (!qualified(t2_)) continue;
			if (t2[t2_]) flag = 1;
		}
		if (!flag) return 0;
	}
	return 1;
}

int main() {
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		memset(t2, 0, sizeof t2);
		for (int hh, mm, i = 1; i <= n; ++i) {
			scan(hh); scan(mm);
			t1[i] = hh * 60 + mm;
		}
		for (int hh, mm, i = 1; i <= m; ++i) {
			scan(hh); scan(mm);
			t2[hh * 60 + mm] = 1;
		}
		
		scan(k);
		for (int hh, mm, i = 1; i <= k; ++i) {
			scan(hh); scan(mm);
			t_meet[i] = hh * 60 + mm;
		}
		
		int ans = 0, ans_t;
		for (int t = 1; t < MAXT; ++t)
			if (check(t)) ++ans, ans_t = t;
		
		if (!ans) puts("il bugiardo passeggeri!");
		else if (ans == 1) printf("%02d:%02d\n", ans_t / 60, ans_t % 60);
		else printf("%d scelte\n", ans);
	}
	
	return 0;
}

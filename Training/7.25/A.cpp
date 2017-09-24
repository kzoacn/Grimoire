#include <bits/stdc++.h>

int n, k;

struct Fish {
	int score, mask;
	
	Fish() {}
	
	bool operator < (const Fish &rhs) const {
		return score > rhs.score;
	}
	
	void scan() {
		static int x;
		scanf("%d%d", &score, &x);
		mask = 0;
		for (int y, i = 1; i <= x; ++i) {
			scanf("%d", &y); --y;
			mask |= (1 << y);
		}
	}
} fish[10005];

struct Query {
	Fish a; int id;
	int mask_yes, mask_no;
	
	Query() {}
	
	bool operator < (const Query &rhs) const {
		return a < rhs.a;
	}
	
	void scan(int ID) {
		static int x;
		id = ID;
		scanf("%d", &x);
		a = fish[x];
		scanf("%d", &x);
		mask_yes = mask_no = 0;
		for (int y, i = 1; i <= x; ++i) {
			scanf("%d", &y); --y;
			if (a.mask & (1 << y)) mask_yes |= (1 << y);
			else mask_no |= (1 << y);
		}
	}
} qry[100005];

int ans[100005];
int cnt[1 << 10][1 << 10];

void Add(int mask_yes) {
	static const int full_mask = (1 << k) - 1;
	
	int mask_no = full_mask ^ mask_yes;
	
	for (int s1 = mask_yes; ; s1 = (s1 - 1) & mask_yes) {
		for (int s2 = mask_no; ; s2 = (s2 - 1) & mask_no) {
			++cnt[s1][s2];
			if (!s2) break;
		}
		if (!s1) break;
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
		fish[i].scan();
	int Q; scanf("%d", &Q);
	for (int i = 1; i <= Q; ++i)
		qry[i].scan(i);
	
	std::sort(fish + 1, fish + n + 1);
	std::sort(qry + 1, qry + Q + 1);
	
	for (int i = 1, j = 1; i <= Q; ++i) {
		while (j <= n && fish[j].score > qry[i].a.score) {
			Add(fish[j].mask);
			++j;
		}
		ans[qry[i].id] = cnt[qry[i].mask_yes][qry[i].mask_no] + 1;
	}
	
	for (int i = 1; i <= Q; ++i)
		printf("%d\n", ans[i]);
	
	return 0;
}

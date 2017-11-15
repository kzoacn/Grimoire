#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;

struct Line {
	int l, r;
} line[MAXN];

inline bool cmp(const Line &p, const Line &q) {
	return p.r < q.r;
}

int c[MAXN], table[MAXN], sum[MAXN], sum_l[MAXN];
int tag[MAXN << 1], mx[MAXN << 1];

inline int get_node(int l, int r) {
	return l + r | l != r;
}

inline void build_tree(int l, int r) {
	int k = get_node(l, r);
	tag[k] = mx[k] = 0;
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	build_tree(l, mid);
	build_tree(mid + 1, r);
}

int main() {
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &line[i].l, &line[i].r);
		}
		int cnt = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &c[i]);
			table[++cnt] = c[i];
		}
		table[++cnt] = 0;
		table[++cnt] = 2e9;
		
		sort(table + 1, table + cnt + 1);
		cnt = unique(table + 1, table + cnt + 1) - table - 1;
		for (int i = 1; i <= n; ++i) {
			line[i].l = lower_bound(table + 1, table + cnt + 1, line[i].l) - table;
			line[i].r = lower_bound(table + 1, table + cnt + 1, line[i].r) - table;
		}
		for (int i = 1; i <= m; ++i) {
			c[i] = lower_bound(table + 1, table + cnt + 1, c[i]) - table;
		}
		
		for (int i = 0; i <= cnt; ++i) {
			sum[i] = 0;
			sum_l[i] = 0;
		}
		for (int i = 1; i <= m; ++i) {
			sum[c[i]]++;
		}
		
		for (int i = 1; i <= n; ++i) {
			sum_l[l[i]]++;
		}
		for (int i = cnt - 1; i; --i) {
			sum_l[i] += sum_l[i + 1];
		}
		
		sort(line + 1, line + n + 1, cmp);
		build_tree(0 + 1, cnt + 1);
		int j = 1;
		for (int i = 1; i <= cnt; ++i) {
			while (j <= n && line[j].r < i) {
				modify(0 + 1, line[j].l - 1 + 1, 1);
				++j;
			}
			if (c)
		}
	}
}

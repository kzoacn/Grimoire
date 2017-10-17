#include <bits/stdc++.h>

typedef std::pair<int, int> pii;
#define mkpair std::make_pair

struct Stick {
	int x, y;
	
	void scan() {
		scanf("%d%d", &x, &y);
	}
	
	bool operator < (const Stick &rhs) const {
		return x < rhs.x;
	} 
} sti[200005];

int h, w, n;

pii to[200005][2][18]; // 2 ** 17 = 131072, 0: <-, 1: ->

void get_to() {
	for (int i = 1; i <= w; ++i) {
		if (i != 1) to[i][0][0] = mkpair(i - 1, 0);
		if (i != w) to[i][1][0] = mkpair(i + 1, 1);
	}
	to[1][0][0] = mkpair(1, 1);
	to[w][1][0] = mkpair(w, 0);
	
	pii tmp;
	for (int t = 1; t <= 17; ++t) {
		for (int drct = 0; drct < 2; ++drct)
			for (int i = 1; i <= w; ++i) {
				tmp = to[i][drct][t - 1];
				to[i][drct][t] = to[tmp.first][tmp.second][t - 1];
			}
	}
}

pii Run(int now, int drct, int step) {
	pii res = mkpair(now, drct);
	for (int t = 0; t <= 17; ++t) if ((step >> t) & 1)
		res = to[res.first][res.second][t];
	return res;
}

int moto[200005], st[200005], inv[200005];

int main() {
	scanf("%d%d%d", &h, &w, &n);
	get_to();
	for (int i = 1; i <= w; ++i) moto[i] = i;
	
	for (int i = 1; i <= n; ++i)
		sti[i].scan();
	
	std::sort(sti + 1, sti + n + 1);
	
	for (int i = 1; i <= n; ++i) {
		int x = sti[i].x, y = sti[i].y;
		
		int u = Run(y, 1, x).first, 
			v = Run(y + 1, 0, x).first;
		
		std::swap(moto[u], moto[v]);
	}
	
	for (int i = 1; i <= w; ++i)
		st[Run(i, i & 1, h).first] = i;
	
	for (int i = 1; i <= w; ++i)
		inv[moto[st[i]]] = i;
	
	for (int i = 1; i <= w; ++i)
		printf("%d\n", inv[i]);
	
	return 0;
}

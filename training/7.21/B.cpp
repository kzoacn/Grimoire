#include <bits/stdc++.h>

int R, C, n, m;

struct Icon {
	int x, y;
	
	void scan() {
		scanf("%d%d", &x, &y);
		x += 7; y += 4; // ???.jpg
	}
} b[105], w[105];
bool skip_b[105], skip_w[105];

int sorted_x[105], sorted_y[105], cnt_x, cnt_y;

struct Event {
	int col, // 0: white, 1: black
		pos; // sorted_y[pos] is the real position
	
	Event() {}
	Event(int col, int pos): col(col), pos(pos) {}
	
	bool operator < (const Event &rhs) const {
		return pos < rhs.pos;
	}
} event[105]; int tot;

int w_out[105], b_out[105];

int Calc() {
	std::sort(event + 1, event + tot + 1);
	
	int w_cnt = 0, b_cnt = 0;
	for (int i = 1; i <= tot; ++i) {
		w_cnt += (event[i].col == 0);
		b_cnt += (event[i].col == 1);
	}
	
	w_out[0] = w_cnt;
	b_out[0] = b_cnt;
	
	for (int i = 1, j = 1; i <= cnt_y; ++i) {
		w_out[i] = w_out[i - 1];
		b_out[i] = b_out[i - 1];
		while (j <= tot && event[j].pos == sorted_y[i]) {
			if (event[j].col == 0) --w_out[i];
			else --b_out[i];
			++j;
		}
	}
	
	int res = 0x3f3f3f3f;
	
	int w_ot = 0, b_ot = 0;
	int w_mx = 0, b_mx = 0;
	
	for (int i = 1, j = 1; i <= cnt_y; ++i) {
		if (w_cnt - w_ot + b_ot < w_cnt - w_mx + b_mx) {
			w_mx = w_ot;
			b_mx = b_ot;
		}
		res = std::min(res, w_cnt - w_mx - w_out[i] + b_mx + b_out[i]);
		while (j <= tot && event[j].pos == sorted_y[i]) {
			if (event[j].col == 0) ++w_ot;
			else ++b_ot;
			++j;
		}
	}
	
	return res;
}

int main() {
	int ans = 0;
	
	scanf("%d%d%d%d", &R, &C, &n, &m);
	for (int i = 1; i <= n; ++i) {
		b[i].scan();
		if (b[i].x < 0 || b[i].x >= R || b[i].y < 0 || b[i].y >= C) {
			++ans;
			skip_b[i] = 1;
			continue;
		}
		sorted_x[++cnt_x] = b[i].x;
		sorted_y[++cnt_y] = b[i].y;
	}
	for (int i = 1; i <= m; ++i) {
		w[i].scan();
		if (w[i].x < 0 || w[i].x >= R || w[i].y < 0 || w[i].y >= C) {
			skip_w[i] = 1;
			continue;
		}
		sorted_x[++cnt_x] = w[i].x;
		sorted_y[++cnt_y] = w[i].y;
	}
	
	std::sort(sorted_x + 1, sorted_x + cnt_x + 1);
	cnt_x = std::unique(sorted_x + 1, sorted_x + cnt_x + 1) - sorted_x - 1;
	std::sort(sorted_y + 1, sorted_y + cnt_y + 1);
	cnt_y = std::unique(sorted_y + 1, sorted_y + cnt_y + 1) - sorted_y - 1;
	
	int ans_2 = 0x3f3f3f3f;
	
	for (int l, i = 1; i <= cnt_x; ++i) {
		l = sorted_x[i];
		for (int r, j = i; j <= cnt_x; ++j) {
			r = sorted_x[j];
			
			tot = 0;
			int tmp = 0;
			for (int t = 1; t <= n; ++t) if (!skip_b[t]) {
				if (b[t].x >= l && b[t].x <= r)
					event[++tot] = Event(1, b[t].y);
				else ++tmp;
			}
			for (int t = 1; t <= m; ++t) if (!skip_w[t]) {
				if (w[t].x >= l && w[t].x <= r)
					event[++tot] = Event(0, w[t].y);
			}
			
			tmp += Calc();
			ans_2 = std::min(ans_2, tmp);
		}
	}
	
	printf("%d\n", ans + ans_2);
	
	return 0;
}

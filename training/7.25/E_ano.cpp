#include <bits/stdc++.h>

const double eps = 1e-8;

int sgn(double x) { return x < -eps ? -1 : x > eps; }

int n;

struct Node {
	double val; int pos;
	
	Node() {}
	Node(double val, int pos): val(val), pos(pos) {}
	
	bool operator < (const Node &rhs) const {
		return sgn(val - rhs.val) < 0;
	}
	
	void scan(int id) {
		scanf("%lf", &val); pos = id;
	}
} a[10005];

bool cho[10005]; int cnt = 0;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		a[i].scan(i);
	}
	
	std::sort(a + 1, a + n + 1);
	
	int l = 1, r = n;
	for (; sgn(a[r].val - 1) > 0; --r) {
		++cnt; cho[a[r].pos] = 1;
	}
	for (; l + 1 <= r && sgn(a[l].val * a[l + 1].val - 1) > 0; l += 2) {
		cnt += 2;
		cho[a[l].pos] = cho[a[l + 1].pos] = 1;
	}
	
	if (!cnt) {
		if (sgn(a[1].val * a[2].val - a[n].val) > 0) {
			cnt = 2; cho[a[1].pos] = cho[a[2].pos] = 1;
		}
		else {
			cnt = 1; cho[a[n].pos] = 1;
		}
	}
	
	printf("%d\n", cnt);
	for (int i = 1; i <= n; ++i) if (cho[i]) {
		--cnt;
		printf("%d%c", i, " \n"[cnt == 0]);
	}
	
	return 0;
}

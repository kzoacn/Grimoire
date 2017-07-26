#include <bits/stdc++.h>

typedef std::pair<int, int> pii;
#define mp std::make_pair

int n, a[1005], root;
int ch[1005][2];

int lowerbound(int l, int r, int x) {
	int res = r + 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (a[mid] > x) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

void BFS() {
	static std::queue<pii> que;
	pii now;
	
	root = a[1];
	
	memset(ch, 0, sizeof ch);
	
	que.push(mp(1, n));
	while (!que.empty()) {
		now = que.front(); que.pop();
		if (now.first >= now.second) continue;
		int mid = lowerbound(now.first + 1, now.second, a[now.first]);
		ch[a[now.first]][0] = a[now.first + 1];
		ch[a[now.first]][1] = a[mid];
		que.push(mp(now.first + 1, mid - 1));
		que.push(mp(mid, now.second));
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		a[n + 1] = 0;
		
		BFS();
		
		/*for (int i = 1; i <= n; ++i)
			printf("%d <- %d -> %d\n", ch[i][0], i, ch[i][1]);
		*/
		int q; scanf("%d", &q);
		int x, now;
		while (q--) {
			scanf("%d", &x);
			now = root;
			while (now != x) {
				assert(now > 0);
				if (x < now) {
					putchar('E');
					now = ch[now][0];
				}
				else {
					putchar('W');
					now = ch[now][1];
				}
			}
			putchar('\n');
		}
	}
	
	return 0;
}

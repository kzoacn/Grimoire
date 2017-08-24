#include <bits/stdc++.h>

int n;

struct Node {
	char col;
	int l, r;
	
	Node() {}
	Node(char col, int l, int r): col(col), l(l), r(r) {}
	
	void scan() {
		static char str[5];
		
		scanf("%s", str);
		col = str[0];
		l = str[1] - '0';
		if (str[2]) r = str[3] - '0';
		else r = l;
	}
} node[9][20]; int top[9];

int dep_lim, tot;

int cnt = 0;

int DFS(int dep) {
	++cnt;
	
	if (tot == n - 2) return dep;
	if (dep == dep_lim) return -1;
	
	if (dep_lim - dep < tot - (n - 2)) return -1;
	
	bool flag = 0; int tmp;
	
	for (int i = 1; i <= n; ++i) if (top[i])
		for (int j = 1; j <= n; ++j) if (i != j && top[j]) {
			Node x = node[i][top[i]], y = node[j][top[j]];
			if (x.col == y.col && x.r == y.l - 1) {
				flag = 1;
				
				--top[i];
				node[j][top[j]] = Node(x.col, x.l, y.r);
				--tot;
				if ((tmp = DFS(dep + 1)) != -1) return tmp;
				node[i][++top[i]] = x;
				node[j][top[j]] = y;
				++tot;
			}
		}
	
	if (flag) return -1;
	
	for (int i = 1; i <= n; ++i) if (top[i])
		for (int j = 1; j <= n; ++j) if (i != j) {
			Node x = node[i][top[i]], y = node[j][top[j]];
			if ((!top[j] && top[i] > 1) || (top[j] && x.col == y.col && x.r < y.l - 1)) {
				--top[i];
				node[j][++top[j]] = x;
				if ((tmp = DFS(dep + 1)) != -1) return tmp;
				node[i][++top[i]] = x;
				--top[j];
			}
		}
	
	return -1;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		tot = 0;
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", top + i); tot += top[i];
			for (int j = 1; j <= top[i]; ++j)
				node[i][j].scan();
		}
		
		/*for (dep_lim = tot - (n - 2); ; ++dep_lim) {
			if (DFS(0)) {
				printf("Case #%d: %d\n", kase, dep_lim);
				break;
			}
			printf("%d: %d\n", dep_lim, cnt);
		}*/
		
		dep_lim = 49;
		std::cout << DFS(0) << std::endl;
		std::cout << cnt << std::endl;
	}
	
	return 0;
}

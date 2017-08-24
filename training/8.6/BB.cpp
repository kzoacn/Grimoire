#include <bits/stdc++.h>

#define __advance //__attribute__((optimize("O3")))

typedef unsigned long long ull;

int n;

int cntt[26];

struct Node {
	char col;
	int l, r;
	
	Node() {}
	Node(char col, int l, int r): col(col), l(l), r(r) {}
	
	__advance bool operator < (const Node &rhs) const {
		return cntt[col - 'A'] == cntt[rhs.col - 'A'] ? (col == rhs.col ? l < rhs.l : col < rhs.col) : cntt[col - 'A'] < cntt[rhs.col - 'A'];
		//return col == rhs.col ? l < rhs.l : col < rhs.col;
	}
	
	__advance void scan() {
		static char str[5];
		
		scanf("%s", str);
		col = str[0]; ++cntt[col - 'A'];
		l = str[1] - '0';
		if (str[2]) r = str[3] - '0';
		else r = l;
	}
} node[9][20]; int top[9];

int dep_lim, tot;

int cnt = 0;

__advance bool DFS(int dep) {
	//++cnt;
	
	if (dep == dep_lim) return tot == n - 2;
	
	if (dep_lim - dep < tot - (n - 2)) return 0;
	/*
	for (int i = 1; i <= n; ++i) if (top[i])
		for (int j = 1; j <= n; ++j) if (i != j && top[j]) {
			Node x = node[i][top[i]], y = node[j][top[j]];
			if (x.col == y.col && x.r == y.l - 1) {
				--top[i];
				node[j][top[j]] = Node(x.col, x.l, y.r);
				--tot;
				bool flag = DFS(dep + 1);
				node[i][++top[i]] = x;
				node[j][top[j]] = y;
				++tot;
				
				return flag;
			}
		}
	
	for (int i = 1; i <= n; ++i) if (top[i])
		for (int j = 1; j <= n; ++j) if (i != j) {
			Node x = node[i][top[i]], y = node[j][top[j]];
			if ((!top[j] && top[i] > 1) || (top[j] && x.col == y.col && x.r < y.l - 1)) {
				--top[i];
				node[j][++top[j]] = x;
				if (DFS(dep + 1)) return 1;
				node[i][++top[i]] = x;
				--top[j];
			}
		}
	*/
	
	std::pair<Node, int> tmp[9];
	int nn = 0, blk = 0;
	
	for (int i = 1; i <= 8; ++i)
		if (top[i]) tmp[++nn] = std::make_pair(node[i][top[i]], i);
		else blk = i;
	
	std::sort(tmp + 1, tmp + nn + 1);
	
	for (int i = 1; i < nn; ++i) {
		int x = tmp[i].second, y = tmp[i + 1].second;
		Node p = tmp[i].first, q = tmp[i + 1].first;
		if (p.col == q.col && p.r == q.l - 1) {
			--top[x];
			node[y][top[y]] = Node(p.col, p.l, q.r);
			--tot;
			--cntt[p.col - 'A'];
			bool flag = DFS(dep + 1);
			node[x][++top[x]] = p;
			node[y][top[y]] = q;
			++tot;
			++cntt[p.col - 'A'];
			return flag;
		}
	}
	
	for (int L = 1, R = 1; R <= nn; L = R) { // [L, R)
		while (R <= nn && tmp[R].first.col == tmp[L].first.col) ++R;
		
		for (int i = L; i < R; ++i)
			for (int j = i + 1; j < R; ++j) {
				int x = tmp[i].second, y = tmp[j].second;
				Node p = tmp[i].first, q = tmp[j].first;
				if (p.r == q.l - 1) continue;
				
				--top[x];
				node[y][++top[y]] = p;
				if (DFS(dep + 1)) return 1;
				node[x][++top[x]] = p;
				--top[y];
			}
	}
	if (blk)
		for (int i = 1; i <= nn; ++i) {
			int x = tmp[i].second, y = blk;
			if (top[x] == 1) continue;
			Node p = tmp[i].first;
			
			--top[x];
			node[y][++top[y]] = p;
			if (DFS(dep + 1)) return 1;
			node[x][++top[x]] = p;
			--top[y];
		}
		
	
	return 0;
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(cntt, 0, sizeof cntt);
		
		tot = 0;
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", top + i); tot += top[i];
			for (int j = 1; j <= top[i]; ++j)
				node[i][j].scan();
		}
		
		for (dep_lim = tot - (n - 2); ; ++dep_lim) {
			if (DFS(0)) {
				//printf("%d: %d\n", dep_lim, cnt);
				printf("Case #%d: %d\n", kase, dep_lim);
				break;
			}
			//printf("%d: %d\n", dep_lim, cnt);
		}
	}
	
	return 0;
}

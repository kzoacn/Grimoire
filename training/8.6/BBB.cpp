#include <bits/stdc++.h>

typedef unsigned long long ull;

int n;

struct Node {
	char col;
	int l, r;
	
	Node() {}
	Node(char col, int l, int r): col(col), l(l), r(r) {}
	
	bool operator < (const Node &rhs) const {
		return col == rhs.col ? l < rhs.l : col < rhs.col;
	}
	
	ull get_hash() {
		return (col - 'A' + 1) * 11 + l * 7 + r;
	}
	
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

std::unordered_set<ull> st;

ull get_hash(int dep) {
	static const ull base = 100003, base2 = 997, base3 = 1003;
	static ull tmp[9];
	
	for (int i = 1; i <= n; ++i) {
		tmp[i] = top[i];
		for (int j = 1; j <= top[i]; ++j)
			tmp[i] = tmp[i] * base2 + node[i][j].get_hash();
	}
	std::sort(tmp + 1, tmp + n + 1);
	ull res = 0;
	for (int i = 1; i <= n; ++i)
		res = res * base + tmp[i];
	res = res * base3 + dep;
	return res;
}

bool DFS(int dep) {
	if (dep == dep_lim) return tot == n - 2;
	
	ull hsh = get_hash(dep_lim - dep);
	if (st.count(hsh)) return 0;
	st.insert(hsh);
	
	if (tot - (n - 2) > dep_lim - dep) return 0;
	
	for (int i = 1; i <= n; ++i) if (top[i])
		for (int j = 1; j <= n; ++j) if (i != j && (!top[j] || (node[i][top[i]].col == node[j][top[j]].col && node[i][top[i]].r < node[j][top[j]].l))) {
			Node p = node[i][top[i]], q = node[j][top[j]];
			if (top[j] && p.r == q.l - 1) {
				--tot;
				--top[i];
				node[j][top[j]] = Node(p.col, p.l, q.r);
				if (DFS(dep + 1)) return 1;
				++tot;
				node[i][++top[i]] = p;
				node[j][top[j]] = q;
			}
			else {
				--top[i];
				node[j][++top[j]] = p;
				if (DFS(dep + 1)) return 1;
				node[i][++top[i]] = p;
				--top[j];
			}
		}
	
	return 0;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		std::unordered_set<ull>().swap(st);
		tot = 0;
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", top + i); tot += top[i];
			for (int j = 1; j <= top[i]; ++j)
				node[i][j].scan();
		}
		
		for (dep_lim = tot - (n - 2); ; ++dep_lim) {
			if (DFS(0)) {
				printf("Case #%d: %d\n", kase, dep_lim);
				break;
			}
			//printf("%d\n", dep_lim);
		}
	}
	
	return 0;
}

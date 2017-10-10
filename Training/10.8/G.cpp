#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>
#include <assert.h>

typedef unsigned long long ull;
#define mkpair std::make_pair

char *trans(ull x) {
	static char *s;
	
	s = new char[70];
	
	for (int i = 63; i >= 0; --i) {
		s[i] = (x & 1) + '0'; x >>= 1;
	}
	s[64] = 0;
	return s;
}

namespace Heap {
	struct Triple {
		ull val;
		int id, cnt;
		
		Triple() {}
		Triple(ull val, int id, int cnt): val(val), id(id), cnt(cnt) {}
		
		bool operator < (const Triple &rhs) const {
			return val < rhs.val;
		}
	} pool[100005];
	int tot;
	
	void init() {
		tot = 0;
	}
	
	void push(ull a, int b, int c) {
		pool[++tot] = Triple(a, b, c);
		std::push_heap(pool + 1, pool + tot + 1);
	}
	
	void pop() {
		std::pop_heap(pool + 1, pool + tot + 1);
		--tot;
	}
	
	Triple &top() {
		return pool[1];
	}
}

namespace Trie {
	const int LIM = 100005 * 70;
	
	int to[LIM][2], fa[LIM], sum[LIM], tot;
	int root = 0;
	
	int newnode(int Fa) {
		++tot;
		to[tot][0] = to[tot][1] = sum[tot] = 0;
		fa[tot] = Fa;
		return tot;
	}
	
	void init() {
		tot = 0;
		root = 0;
	}
	
	void modify(int &k, char *s, int val, int Fa) {
		if (!k) k = newnode(Fa);
		sum[k] += val;
		if (!*s) return;
		modify(to[k][*s - '0'], s + 1, val, k);
	}
	
	int Find(int &k, char *s) {
		assert(k);
		if (!*s) return k;
		return Find(to[k][*s - '0'], s + 1);
	}
	
	char s[70];
	
	void insert(ull x) {
		modify(root, trans(x), 1, 0);
	}
	
	std::pair<ull, int> getmax(ull x) {
		ull res = 0;
		int k = root;
		for (char *c = trans(x); *c; ++c) {
			if (sum[to[k][(*c - '0') ^ 1]]) {
				k = to[k][(*c - '0') ^ 1];
				res = res << 1 | ((*c - '0') ^ 1);
			}
			else {
				k = to[k][*c - '0'];
				res = res << 1 | (*c - '0');
			}
		}
		return mkpair(res, sum[k]);
	}
	
	std::pair<std::pair<ull, int>, int> getnext(ull x, ull last) {
		char *s = trans(last), *sx = trans(x);
		int k = Find(root, s), i = 63;
		
		ull res = last;
		while (k) {
			if (to[fa[k]][(sx[i] - '0') ^ 1] == k) {
				if (to[fa[k]][sx[i] - '0']) {
					k = to[fa[k]][sx[i] - '0'];
					res >>= 1;
					for (; i < 64; ++i) {
						if (sum[to[k][(s[i] - '0') ^ 1]]) {
							k = to[k][(s[i] - '0') ^ 1];
							res = res << 1 | ((s[i] - '0') ^ 1);
						}
						else {
							k = to[k][s[i] - '0'];
							res = res << 1 | (s[i] - '0');
						}
					}
					return mkpair(mkpair(res, sum[k]), 1);
				}
			}
			k = fa[k];
			res >>= 1;
			--i;
		}
		return mkpair(mkpair(0, 0), 0);
	}
}

int n, m;

int head[100005], nxt[100005 << 1], to[100005 << 1], ed;
ull d[100005 << 1];

void AddEdge(int u, int v, ull w) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v; d[ed] = w;
}

ull sum[100005];

void DFS(int now, int fa, ull tmp) {
	sum[now] = tmp;
	for (int i = head[now]; i; i = nxt[i])
		if (to[i] != fa) DFS(to[i], now, tmp ^ d[i]);
}

struct Query {
	int id, k;
	
	void scan(int ID) {
		scanf("%d", &k);
		id = ID;
	}
	
	bool operator < (const Query &rhs) const {
		return k < rhs.k;
	}
} qry[100005];
ull ans[100005];
bool noans[100005];

void Solve() {
	static std::pair<ull, int> tmp;
	static std::pair<std::pair<ull, int>, int> tmp2;
	
	Heap::init();
	for (int i = 1; i <= n; ++i) {
		tmp = Trie::getmax(sum[i]);
		Heap::push(sum[i] ^ tmp.first, i, tmp.second);
	}
	
	int t = 1;
	Heap::Triple top;
	for (int i = 1; i <= m; ++i) {
		noans[qry[i].id] = 0;
		while (Trie::sum[Trie::root] && t < qry[i].k) {
			top = Heap::top();
			if (top.cnt > 1) {
				--Heap::top().cnt;
				continue;
			}
			Heap::pop();
			
			tmp2 = Trie::getnext(sum[top.id], sum[top.id] ^ top.val);
			if (tmp2.second)
				Heap::push(sum[top.id] ^ tmp2.first.first, top.id, tmp2.first.second);
		}
		if (t != qry[i].k) {
			noans[qry[i].id] = 1;
			continue;
		}
		ans[qry[i].id] = Heap::top().val;
	}
}

int main() {
	while (~scanf("%d", &n) && n) {
		memset(head, 0, sizeof head); ed = 0;
		for (int i = 1; i < n; ++i) {
			static int u, v;
			static ull w;
			
			scanf("%d%d%llu", &u, &v, &w);
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
		
		DFS(1, 0, 0);
		
		Trie::init();
		for (int i = 1; i <= n; ++i)
			Trie::insert(sum[i]);
		
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i)
			qry[i].scan(i);
		
		std::sort(qry + 1, qry + m + 1);
		
		Solve();
		
		for (int i = 1; i <= m; ++i) {
			if (noans[i]) puts("-1");
			else printf("%llu\n", ans[i]);
		}
	}
	
	return 0;
}

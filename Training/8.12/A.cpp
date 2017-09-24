#include <bits/stdc++.h>

namespace Trie {
	int tot;
	
	struct Node *pool_pointer;
	struct Node {
		Node *to[26];
		int sz, w, l, r;
		
		Node() {
			memset(to, 0, sizeof to);
			sz = w = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[500005 << 1], *root[2];
	
	void init() {
		pool_pointer = pool;
		root[0] = root[1] = 0;
	}
	
	void insert(Node *&k, char *s) {
		if (!k) k = new Node();
		++k->sz;
		if (!*s) {
			++k->w; return;
		}
		insert(k->to[*s - 'a'], s + 1);
	}
	
	void DFS(Node *k) {
		if (!k) return;
		k->l = tot + 1; k->r = tot + k->sz;
		tot += k->w;
		for (int i = 0; i < 26; ++i) DFS(k->to[i]);
	}
	
	int query(Node *k, char *s) {
		if (!k) return 0;
		if (!*s) return k->l;
		return query(k->to[*s - 'a'], s + 1);
	}
	
	int query2(Node *k, char *s) {
		if (!k) return 0;
		if (!*s) return k->r;
		return query2(k->to[*s - 'a'], s + 1);
	}
	
	// --------
	
	void insert(int t, char *s) {
		insert(root[t], s);
	}
	
	int query(int t, char *s) {
		return query(root[t], s);
	}
	
	int query2(int t, char *s) {
		return query2(root[t], s);
	}
	
	void get_range() {
		tot = 0;
		DFS(root[0]);
		
		tot = 0;
		DFS(root[1]);
	}
}

int n, m;

namespace BIT {
	int c[100005], t[100005], T = 0;
	
	void init() {
		++T;
	}
	
#define lowbit(x) ((x) & -(x))
	
	void add(int a) {
		for (int i = a; i <= n; i += lowbit(i)) {
			if (t[i] != T) {
				t[i] = T; c[i] = 0;
			}
			++c[i];
		}
	}
	
	int query(int a) {
		int res = 0;
		for (int i = a; i > 0; i -= lowbit(i)) {
			if (t[i] != T) {
				t[i] = T; c[i] = 0;
			}
			res += c[i];
		}
		return res;
	}
}

struct Opt {
	int x1, x2, y, len, id, tp;
	int rk;
	
	bool operator < (const Opt &rhs) const {
		return len == rhs.len ? (y == rhs.y ? id < rhs.id : y < rhs.y) : len > rhs.len;
	}
	
	void print() {
		std::cerr << x1 << " " << x2 << " " << y << " " << len << " " << id << " " << tp << std::endl;
	}
} opt[300005]; int cnt;

bool cmp_rk(const Opt &a, const Opt &b) {
	return a.rk < b.rk;
}

bool cmp(const Opt &a, const Opt &b) {
	return a.y < b.y;
}

int ans[100005];

void DAC(int l, int r) {
	if (r - l <= 0) return;
	
	int mid = (l + r) >> 1;
	//std::sort(opt + l, opt + r + 1);
	std::sort(opt + l, opt + mid + 1, cmp);
	std::sort(opt + mid + 1, opt + r + 1, cmp);
	
/*std::cout << "cdq now " << l << " " << r << std::endl;
for (int i = l; i <= mid; ++i) {
	opt[i].print();
}
std::cout << std::endl;
for (int i = mid + 1; i <= r; ++i) {
	opt[i].print();
}
std::cout << std::endl;*/
	
	BIT::init();
	for (int i = l, j = mid + 1; j <= r; ++j) {
		if (opt[j].id == -1) continue;
		while (i <= mid && opt[i].y <= opt[j].y) {
			if (opt[i].id == -1)
				BIT::add(opt[i].x1);
			++i;
		}
		
/*if (1)
std::cerr << "DEBUG: " << opt[j].tp << " " << opt[j].y << " " << BIT::query(opt[j].x2) << " " << BIT::query(opt[j].x1 - 1) << std::endl;*/
		
		ans[opt[j].id] += (BIT::query(opt[j].x2) - BIT::query(opt[j].x1 - 1)) * opt[j].tp;
	}
	std::sort(opt + l, opt + r + 1, cmp_rk);
	DAC(l, mid); DAC(mid + 1, r);
}

std::string ss[100005];

char s[500005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		Trie::init();
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			opt[i].id = -1;
			
			scanf("%s", s); opt[i].len = strlen(s);
			ss[i] = std::string(s);
			Trie::insert(0, s);
			std::reverse(s, s + opt[i].len);
			Trie::insert(1, s);
		}
		
		Trie::get_range();
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < opt[i].len; ++j) s[j] = ss[i][j];
			s[opt[i].len] = '\0';
			
			opt[i].x1 = Trie::query(0, s);
			std::reverse(s, s + opt[i].len);
			opt[i].y = Trie::query(1, s);
			
			//std::cerr << opt[i].x1 << " " << opt[i].y << std::endl;
		}
		cnt = n;
		
		for (int i = 1; i <= m; ++i) {
			opt[cnt + 1].id = opt[cnt + 2].id = i;
			opt[cnt + 1].tp = -1, opt[cnt + 2].tp = 1;
			
			scanf("%s", s); opt[cnt + 1].len = strlen(s);
			opt[cnt + 1].x1 = opt[cnt + 2].x1 = Trie::query(0, s);
			opt[cnt + 1].x2 = opt[cnt + 2].x2 = Trie::query2(0, s);
			
			scanf("%s", s); opt[cnt + 1].len += strlen(s);
			std::reverse(s, s + strlen(s));
			opt[cnt + 1].y = std::max(Trie::query(1, s) - 1, 0);
			opt[cnt + 2].y = Trie::query2(1, s);
			
			opt[cnt + 2].len = opt[cnt + 1].len;
			
			/*if (i == 1) {
				std::cerr << opt[cnt + 1].x1 << " " << opt[cnt + 1].x2 << " " << opt[cnt + 1].y << std::endl << opt[cnt + 2].x1 << " " << opt[cnt + 2].x2 << " " << opt[cnt + 2].y << std::endl;
			}*/
			
			cnt += 2;
		}
		
		std::sort(opt + 1, opt + cnt + 1);
		for (int i = 1; i <= cnt; ++i) {
			opt[i].rk = i;
		}
		
		//for (int i = 1; i <= cnt; ++i) opt[i].print();
		
		memset(ans, 0, sizeof ans);
		DAC(1, cnt);
		
		for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	}
	
	return 0;
}

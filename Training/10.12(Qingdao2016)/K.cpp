#include <bits/stdc++.h>

typedef long long ll;

#define mkpair std::make_pair

const int DIM = 2;

ll norm(ll x) {
	return x * x;
}

struct vec {
	ll c[DIM]; int val, id;
	
	bool operator == (const vec &rhs) const {
		for (int i = 0; i < DIM; ++i)
			if (c[i] != rhs[i]) return 0;
		return 1;
	}
	
	ll &operator [] (const int x) {
		return c[x];
	}
	const ll operator [] (const int x) const {
		return c[x];
	}
	
	ll dist(const vec &rhs) const {
		ll res = 0;
		for (int i = 0; i < DIM; ++i)
			res += norm(c[i] - rhs[i]);
		return res;
	}
	
	void scan(int ID) {
		for (int i = 0; i < DIM; ++i)
			scanf("%lld", c + i);
		scanf("%d", &val);
		id = ID;
	}
};

struct rec {
	ll mn[DIM], mx[DIM];
	
	rec() {}
	rec(const vec &rhs) {
		for (int i = 0; i < DIM; ++i) {
			mn[i] = mx[i] = rhs[i];
		}
	}
	
	rec operator + (const rec &rhs) const {
		rec res;
		for (int i = 0; i < DIM; ++i) {
			res.mn[i] = std::min(mn[i], rhs.mn[i]);
			res.mx[i] = std::max(mx[i], rhs.mx[i]);
		}
		return res;
	}
	
	void add(const vec &rhs) {
		for (int i = 0; i < DIM; ++i) {
			mn[i] = std::min(mn[i], rhs[i]);
			mx[i] = std::max(mx[i], rhs[i]);
		}
	}
	
	ll dist(const vec &rhs) {
		ll res = 0;
		for (int i = 0; i < DIM; ++i) {
			res += norm(std::min(std::max(rhs[i], mn[i]), mx[i]) - rhs[i]);
		}
		return res;
	}
};

namespace KDTree {
	struct Node;
	
	Node *stk[200005]; int rubbish_cnt;
	Node *pool_pointer;
	struct Node {
		rec rect;
		vec sep;
		int sum, sz;
		Node *ch[2];
	
		Node() {
			sum = 0; sz = 1; ch[0] = ch[1] = 0;
		}
	
		Node *update() {
			sum = sep.val;
			rect = rec(sep);
			sz = 1;
			for (int i = 0; i < 2; ++i)
				if (ch[i]) {
					sum += ch[i]->sum;
					rect = rect + ch[i]->rect;
					sz += ch[i]->sz;
				}
			return this;
		}
		
		void *operator new (size_t) {
			if (rubbish_cnt) return stk[--rubbish_cnt];
			return pool_pointer++;
		}
	} *root, *re, pool[200005];
	
	void init() {
		rubbish_cnt = 0;
		pool_pointer = pool;
		root = 0;
	}
	
	vec tmp[200005];
	int Dim, top;
	
	bool cmp(const vec &a, const vec &b) {
		if (a[Dim] != b[Dim])
			return a[Dim] < b[Dim];
		return a.id < b.id;
	}
	
	Node *build(vec *p, int l, int r, int d) {
		int mid = (l + r) >> 1; Dim = d;
		std::nth_element(p + l, p + mid, p + r + 1, cmp);
		Node *k = new Node();
		k->sep = p[mid];
		if (l <= mid - 1)
			k->ch[0] = build(p, l, mid - 1, d ^ 1);
		if (mid + 1 <= r)
			k->ch[1] = build(p, mid + 1, r, d ^ 1);
		return k->update();
	}
	
	void DFS(Node *&k) {
		if (k->ch[0]) DFS(k->ch[0]);
		tmp[++top] = k->sep;
		if (k->ch[1]) DFS(k->ch[1]);
		stk[rubbish_cnt++] = k;
		*k = Node(); k = 0;
	}
	
	Node *rebuild(Node *&k) {
		if (!k) return 0;
		top = 0; DFS(k);
		return build(tmp, 1, top, 0);
	}
	
	#define Size(x) (x ? x->sz : 0)
	
	void Add(Node *&k, const vec &p, int d = 0) {
		Dim = d;
		if (!k) {
			k = new Node();
			k->sep = p;
			k->update();
			return;
		}
		if (k->sep == p) {
			k->sep.val += p.val;
			k->update();
			return;
		}
		if (p[Dim] < k->sep[Dim])
			Add(k->ch[0], p, d ^ 1);
		else
			Add(k->ch[1], p, d ^ 1);
		k->update();
		if (std::max(Size(k->ch[0]), Size(k->ch[1])) > 0.7 * k->sz)
			re = k;
	}
	
	std::priority_queue<std::pair<ll, int> > kNN;
	void query(Node *k, const vec &p, int kth, int d = 0) {
		Dim = d;
		if (!k || ((int)kNN.size() == kth && k->rect.dist(p) > kNN.top().first)) return;
		kNN.push(mkpair(k->sep.dist(p), k->sep.id));
		if ((int)kNN.size() > kth) kNN.pop();
		if (cmp(p, k->sep)) {
			query(k->ch[0], p, kth, d ^ 1);
			query(k->ch[1], p, kth, d ^ 1);
		}
		else {
			query(k->ch[1], p, kth, d ^ 1);
			query(k->ch[0], p, kth, d ^ 1);
		}
	}
}

int n, m, inv[200005];
vec p[200005], qry[20005], ans[20005];

bool byVal(const vec &a, const vec &b) {
	return a.val == b.val ? a.id < b.id : a.val < b.val;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		KDTree::init();
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			p[i].scan(i);
		
		for (int i = 1; i <= m; ++i)
			qry[i].scan(i);
		
		std::sort(p + 1, p + n + 1, byVal);
		std::sort(qry + 1, qry + m + 1, byVal);
		
		for (int i = 1; i <= n; ++i)
			inv[p[i].id] = i;
		
		for (int i = 1, j = 1; i <= m; ++i) {
			//std::cerr << "tkkk : " << qry[i].id << std::endl;
			while (j <= n && p[j].val <= qry[i].val) {
				//std::cerr << "cnbb : " << p[j].val << std::endl;
				KDTree::re = 0;
				KDTree::Add(KDTree::root, p[j]);
				KDTree::rebuild(KDTree::re);
				
				++j;
			}
			
			while (!KDTree::kNN.empty()) KDTree::kNN.pop();
			KDTree::query(KDTree::root, qry[i], 1);
			
			//std::cerr << "tkk2 : " << qry[i].id << std::endl;
			
			ans[qry[i].id] = p[inv[KDTree::kNN.top().second]];
			
			//printf("DEBUG: %lld %lld %d\n", ans[qry[i].id].c[0], ans[qry[i].id].c[1], ans[qry[i].id].val);
		}
		
		for (int i = 1; i <= m; ++i)
			printf("%lld %lld %d\n", ans[i].c[0], ans[i].c[1], ans[i].val);
	}
	
	return 0;
}

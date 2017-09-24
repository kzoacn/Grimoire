struct Point{
	int data[MAXK], id;
}p[MAXN];

struct KdNode{
	int l, r;
	Point p, dmin, dmax;
	KdNode() {}
	KdNode(const Point &rhs) : l(0), r(0), p(rhs), dmin(rhs), dmax(rhs) {}
	inline void merge(const KdNode &rhs) {
		for (register int i = 0; i < k; i++) {
			dmin.data[i] = std::min(dmin.data[i], rhs.dmin.data[i]);
			dmax.data[i] = std::max(dmax.data[i], rhs.dmax.data[i]);
		}
	}
	inline long long getMinDist(const Point &rhs)const {
		register long long ret = 0;
		for (register int i = 0; i < k; i++) {
			if (dmin.data[i] <= rhs.data[i] && rhs.data[i] <= dmax.data[i]) continue;
			ret += std::min(1ll * (dmin.data[i] - rhs.data[i]) * (dmin.data[i] - rhs.data[i]),
				1ll * (dmax.data[i] - rhs.data[i]) * (dmax.data[i] - rhs.data[i]));
		}
		return ret;
	}
	long long getMaxDist(const Point &rhs) {
		long long ret = 0;
		for (register int i = 0; i < k; i++) {
			int tmp = std::max(std::abs(dmin.data[i] - rhs.data[i]),
			    std::abs(dmax.data[i] - rhs.data[i]));
			ret += 1ll * tmp * tmp;
		}
		return ret;
	}
}tree[MAXN * 4];

struct Result{
	long long dist;
	Point d;
	Result() {}
	Result(const long long &dist, const Point &d) : dist(dist), d(d) {}
	bool operator >(const Result &rhs)const {
		return dist > rhs.dist || (dist == rhs.dist && d.id < rhs.d.id);
	}
	bool operator <(const Result &rhs)const {
		return dist < rhs.dist || (dist == rhs.dist && d.id > rhs.d.id);
	}
};

inline long long sqrdist(const Point &a, const Point &b) {
	register long long ret = 0;
	for (register int i = 0; i < k; i++) {
		ret += 1ll * (a.data[i] - b.data[i]) * (a.data[i] - b.data[i]);
	}
	return ret;
}

inline int alloc() {
	size++;
	tree[size].l = tree[size].r = 0;
	return size;
}

void build(const int &depth, int &rt, const int &l, const int &r) {
	if (l > r) return;
	register int middle = l + r >> 1;
	std::nth_element(p + l, p + middle, p + r + 1, 
		[=](const Point &a, const Point &b){return a.data[depth] < b.data[depth];};
	tree[rt = alloc()] = KdNode(p[middle]);
	if (l == r) return;
	build((depth + 1) % k, tree[rt].l, l, middle - 1);
	build((depth + 1) % k, tree[rt].r, middle + 1, r);
	if (tree[rt].l) tree[rt].merge(tree[tree[rt].l]);
	if (tree[rt].r) tree[rt].merge(tree[tree[rt].r]);
}

std::priority_queue<Result, std::vector<Result>, std::greater<Result> > heap;

void getMinKth(const int &depth, const int &rt, const int &m, const Point &d) { // 求K近点
	Result tmp = Result(sqrdist(tree[rt].p, d), tree[rt].p);
	if ((int)heap.size() < m) {
		heap.push(tmp);
	} else if (tmp < heap.top()) {
		heap.pop();
		heap.push(tmp);
	}
	int x = tree[rt].l, y = tree[rt].r;
	if (x != 0 && y != 0 && sqrdist(d, tree[x].p) > sqrdist(d, tree[y].p)) std::swap(x, y);
	if (x != 0 && ((int)heap.size() < m || tree[x].getMinDist(d) < heap.top().dist)) {
		getMinKth((depth + 1) % k, x, m, d);
	}
	if (y != 0 && ((int)heap.size() < m || tree[y].getMinDist(d) < heap.top().dist)) {
		getMinKth((depth + 1) % k, y, m, d);
	}
}

void getMaxKth(const int &depth, const int &rt, const int &m, const Point &d) { // 求K远点
	Result tmp = Result(sqrdist(tree[rt].p, d), tree[rt].p);
	if ((int)heap.size() < m) {
		heap.push(tmp);
	} else if (tmp > heap.top()) {
		heap.pop();
		heap.push(tmp);
	}
	int x = tree[rt].l, y = tree[rt].r;
	if (x != 0 && y != 0 && sqrdist(d, tree[x].p) < sqrdist(d, tree[y].p)) std::swap(x, y);
	if (x != 0 && ((int)heap.size() < m || tree[x].getMaxDist(d) >= heap.top().dist)) { // 这里的>=是因为在距离相等的时候需要按照id排序
		getMaxKth((depth + 1) % k, x, m, d);
	}
	if (y != 0 && ((int)heap.size() < m || tree[y].getMaxDist(d) >= heap.top().dist)) {
		getMaxKth((depth + 1) % k, y, m, d);
	}
}

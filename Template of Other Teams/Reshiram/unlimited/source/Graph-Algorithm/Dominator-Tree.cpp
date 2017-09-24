#define foreach(A, x, it) for (int it = A.h[x]; it; it = A.e[it].next)

const int MAXN = 200001;
const int MAXM = 400001;

template<class T, int MAXN, int MAXM>
struct AdjList{
	struct Edge{
		T data;
		int next;
	}e[MAXM];
	int h[MAXN], t;
	void add(int x, const T &data) {
		t++;
		e[t].data = data;
		e[t].next = h[x];
		h[x] = t;
	}
	void drop(int x) {
		h[x] = e[h[x]].next;
	}
	T & operator [](const int &index) {
		return e[index].data;
	}
	void clear(int n) {
		std::fill(h + 1, h + n + 1, t = 0);
	}
};
// $fa$是并查集的父亲，$f$是树的父亲，$sdom$是半必经点，$idom$是必经点，$smin$是带权并查集的权值
// $pred$是前驱链表，$succ$是后继链表
int dfn[MAXN], sdom[MAXN], idom[MAXN], id[MAXN], f[MAXN], fa[MAXN], smin[MAXN];
AdjList<int, MAXN, MAXM> pred, succ;
long long answer[MAXN];

void predfs(int x) {
	id[dfn[x] = ++stamp] = x;
	foreach(succ, x, i) {
		int y = succ[i];
		if (!dfn[y]) {
			f[y] = x;
			predfs(y);
		}
	}
}

int getfa(int x) {
	if (fa[x] == x) return x;
	int ret = getfa(fa[x]);
	if (dfn[sdom[smin[fa[x]]]] < dfn[sdom[smin[x]]]) {
		smin[x] = smin[fa[x]];
	}
	return fa[x] = ret;
}

void tarjan(int s) {
	static AdjList<int, MAXN, MAXN> tmp;
	stamp = tmp.t = 0;
	predfs(s);
	for (int i = 1; i <= stamp; i++) {
		fa[id[i]] = smin[id[i]] = id[i];
		tmp.h[id[i]] = idom[id[i]] = 0;
	}
	for (int o = stamp; o >= 1; o--) {
		int x = id[o];
		if (o != 1) {
			sdom[x] = f[x];
			foreach(pred, x, i) {
				int p = pred[i];
				if (!dfn[p]) continue;
				if (dfn[p] > dfn[x]) {
					getfa(p);
					p = sdom[smin[p]];
				}
				if (dfn[sdom[x]] > dfn[p]) {
					sdom[x] = p;
				}
			}
			tmp.add(sdom[x], x);
		}
		while (tmp.h[x] != 0) {
			int y = tmp[tmp.h[x]];
			tmp.drop(x);
			getfa(y);
			if (x != sdom[smin[y]]) {
				idom[y] = smin[y];
			} else {
				idom[y] = x;
			}
		}
		foreach(succ, x, i) {
			if (f[succ[i]] == x) {
				fa[succ[i]] = x;
			}
		}
	}
	idom[s] = s;
	for (int i = 2; i <= stamp; i++) {
		int x = id[i];
		if (idom[x] != sdom[x]) {
			idom[x] = idom[idom[x]];
		}
	}
}

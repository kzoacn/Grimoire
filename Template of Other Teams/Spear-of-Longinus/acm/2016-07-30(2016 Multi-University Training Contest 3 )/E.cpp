#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

const int N = 50005;
const int LOG = 20;

int n, Q, nowsize = 0;
int gxx = 0, dfn[N];
int R[N], deep[N], U_cnt = 0, root[N];

vector<int> adj[N];

struct node {
	int l, r, Max, Min, sum;
	int tag, lson, rson, used;
	void clear() {
		l = r = sum = lson = rson = tag = used = 0;
		Min = 0x3f3f3f3f;
		Max = -0x3f3f3f3f;
	}
}tree[N * LOG * 4];

void update(int root) {
	tree[root].Min = min(tree[tree[root].lson].Min, tree[tree[root].rson].Min);
	tree[root].Max = max(tree[tree[root].lson].Max, tree[tree[root].rson].Max);
	tree[root].sum = tree[tree[root].lson].sum + tree[tree[root].rson].sum;
}

void modify(int root, int x) {
	tree[root].sum += x * (tree[root].r - tree[root].l + 1);
	tree[root].Max += x;
	tree[root].Min += x;
	tree[root].tag += x;
	return ;
}

void push_down(int root) {
	if(tree[root].tag == 0) {
		return ;
	}
	modify(tree[root].lson, tree[root].tag);
	modify(tree[root].rson, tree[root].tag);
	tree[root].tag = 0;
}

void build(int x, int y) {
	adj[x].push_back(y);
}

void dfs(int x, int fa) {
	dfn[x] = ++gxx;
	deep[x] = deep[fa] + 1;
	for(int i = 0; i < adj[x].size(); i++) {
		int to = adj[x][i];
		if(to == fa) {
			continue;
		}
		dfs(to, x);
	}
	R[x] = gxx;
	return ;
}

int newtree(int l, int r, int lson, int rson) {
	nowsize++;
	tree[nowsize].l = l;
	tree[nowsize].r = r;
	tree[nowsize].lson = lson;
	tree[nowsize].rson = rson;
	update(nowsize);
	return nowsize;
}

int build_tree(int l, int r) {
	if(l == r) {
		int root = ++nowsize;
		tree[root].l = l;
		tree[root].r = r;
		tree[root].Max = tree[root].Min = deep[l];
		tree[root].sum = tree[root].tag = 0;
		tree[root].lson = tree[root].rson = 0;
		return nowsize;
	}
	int mid = l + r >> 1;
	return newtree(l, r, build_tree(l, mid), build_tree(mid + 1, r));
}

int modify(int root, int l, int r, int delta) {
	if(tree[root].l == l && tree[root].r == r) {
		nowsize++;
		tree[nowsize] = tree[root];
		modify(nowsize, delta);
		return nowsize;
	}
	push_down(root);
	int mid = tree[root].l + tree[root].r >> 1;
	if(r <= mid) {
		return newtree(tree[root].l, tree[root].r, modify(tree[root].lson, l, r, delta), tree[root].rson);
	} else if(l > mid) {	
		return newtree(tree[root].l, tree[root].r, tree[root].lson, modify(tree[root].rson, l, r, delta));
	} else {
		return newtree(tree[root].l, tree[root].r, modify(tree[root].lson, l, mid, delta), modify(tree[root].rson, mid + 1, r, delta));
	}
}

node uni(node x, node y) {
	node tmp;
	tmp.sum = x.sum + y.sum;
	tmp.Max = max(x.Max, y.Max);
	tmp.Min = min(x.Min, y.Min);
	return tmp;
}

node Query(int root, int l, int r) {
	if(tree[root].l == l && tree[root].r == r) {
		return tree[root];
	}
	push_down(root);
	int mid = tree[root].l + tree[root].r >> 1;
	if(r <= mid) {
		return Query(tree[root].lson, l, r);
	} else if(l > mid) {
		return Query(tree[root].rson, l, r);	
	} else {
		return uni(Query(tree[root].lson, l, mid), Query(tree[root].rson, mid + 1, r));
	}
}

void work() {
	for(int i = 1; i <= n; i++) {
		adj[i].clear();
	}
	for(int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		build(x, y);
		build(y, x);
	}
	gxx = 0;
	deep[1] = 0;
	dfs(1, 0);
	nowsize = 0;
	root[1] = build_tree(1, n);
	
	static bool used[N];
	for(int i = 1; i <= n; i++) {
		used[i] = false;
	}
	
	vector<int> queue;
	queue.clear();
	queue.push_back(1);
	used[1] = true;
	for(int head = 0; head < (int)queue.size(); head++) {
		int u = queue[head];
		for(int i = 0; i < adj[u].size(); i++) {
			int to = adj[u][i];
			if(used[to]) {
				continue;
			}
			root[to] = modify(root[u], dfn[to], R[to], -1);
			if(dfn[to] > 1) {
				root[to] = modify(root[to], 1, dfn[to] - 1, 1);
			}
			if(R[to] < n) {
				root[to] = modify(root[to], R[to] + 1, n, 1);
			}
			used[to] = true;
			queue.push_back(to);
		}
	}
	int last = 0;
	for(int i = 1; i <= Q; i++) {
		int k, p, t;
		scanf("%d%d%d", &k, &p, &t);
		if(last == -1) {
			last = 0;
		}
		p = (p + last) % n + 1;
		node ans;
		ans.Max = -0x3f3f3f3f;
		ans.Min = 0x3f3f3f3f;
		int Sum = tree[root[p]].sum;
		
		vector<pair<int, int> > seq, opera;
		seq.clear();
		opera.clear();
		if(k != 0) {
			for(int j = 1; j <= k; j++) {
				int x;
				scanf("%d", &x);
				seq.push_back(make_pair(dfn[x], n - R[x] + 1)); 
			}
			sort(seq.begin(), seq.end());
		
			opera.push_back(seq[0]);
		
			for(int j = 0; j < seq.size(); j++) {
				if(seq[j].second >= opera[opera.size() - 1].second)	{
					continue;
				}
				opera.push_back(seq[j]);
			}
			for(int j = 0; j < opera.size(); j++) {
				opera[j].second = n - opera[j].second + 1;
			}
			
			for(int j = 0; j < opera.size(); j++) {
				node t = Query(root[p], opera[j].first, opera[j].second);
				Sum -= t.sum;
				if(opera[j].first > 1) {
					ans = uni(ans, Query(root[p], 1, opera[j].first - 1));
				}
				if(opera[j].second < n) {
					ans = uni(ans, Query(root[p], opera[j].second + 1, n));
				}
			}
			
		} else {
			ans = tree[root[p]];
			Sum = ans.sum;
		}
		if(t == 1) {
			if(ans.Min == 0x3f3f3f3f) {
				last = -1;
				puts("-1");
			} else {
				printf("%d\n", Sum);
				last = Sum;
			}
		} else if(t == 2) {
			if(ans.Min == 0x3f3f3f3f) {
				puts("-1");
				last = -1;
			} else {
				printf("%d\n", ans.Min);
				last = ans.Min;
			}
		} else if(t == 3) {
			if(ans.Max == -0x3f3f3f3f) {
				puts("-1");
				last = -1;
			} else {
				printf("%d\n", ans.Max);
				last = ans. Max;
			}
		}
	}
	for(int i = 1; i <= nowsize; i++) {
		tree[i].clear();	
	}
	
	return ;
}

int main() {
	while(scanf("%d%d", &n, &Q) == 2) {
		work();
	}
	return 0;
}

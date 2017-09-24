struct node1 {
	int L, R, Lson, Rson, Sum;
} tree[N * 40];
int root[N], a[N], b[N];
int tot, n, m;
int Real[N];
int Same(int x) {
	++tot;
	tree[tot] = tree[x];
	return tot;
}
int build(int L, int R) {
	++tot;
	tree[tot].L = L;
	tree[tot].R = R;
	tree[tot].Lson = tree[tot].Rson = tree[tot].Sum = 0;
	if (L == R) return tot;
	int s = tot;
	int mid = (L + R) >> 1;
	tree[s].Lson = build(L, mid);
	tree[s].Rson = build(mid + 1, R);
	return s;
}
int Ask(int Lst, int Cur, int L, int R, int k) {
	if (L == R) return L;
	int Mid = (L + R) >> 1;
	int Left = tree[tree[Cur].Lson].Sum - tree[tree[Lst].Lson].Sum;
	if (Left >= k) return Ask(tree[Lst].Lson, tree[Cur].Lson, L, Mid, k);
	k -= Left;
	return Ask(tree[Lst].Rson, tree[Cur].Rson, Mid + 1, R, k);
}
int Add(int Lst, int pos) {
	int root = Same(Lst);
	tree[root].Sum++;
	if (tree[root].L == tree[root].R) return root;
	int mid = (tree[root].L + tree[root].R) >> 1;
	if (pos <= mid) tree[root].Lson = Add(tree[root].Lson, pos);
	else tree[root].Rson = Add(tree[root].Rson, pos);
	return root;
}
int main() {
	scanf("%d%d", &n, &m);
	int up = 0;
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	up = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++){
		int tmp = lower_bound(b + 1, b + up + 1, a[i]) - b;
		Real[tmp] = a[i];
		a[i] = tmp;
	}
	tot = 0;
	root[0] = build(1, up);
	for (int i = 1; i <= n; i++){
		root[i] = Add(root[i - 1], a[i]);
	}	
	for (int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		printf("%d\n", Real[Ask(root[u - 1], root[v], 1, up, w)]);
	}
	return 0;
}

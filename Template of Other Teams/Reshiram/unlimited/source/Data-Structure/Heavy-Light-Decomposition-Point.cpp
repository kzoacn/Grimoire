void modify(int x, int y, int val) {
	int fx = t[x], fy = t[y];
	while (fx != fy) {
		if (d[fx] > d[fy]) {
			modify(1, 1, n, w[fx], w[x], val);
			x = f[fx]; fx = t[x];
		}
		else{
			modify(1, 1, n, w[fy], w[y], val);
			y = f[fy]; fy = t[y];
		}
	}
	if (d[x] < d[y]) modify(1, 1, n, w[x], w[y], val);
	else modify(1, 1, n, w[y], w[x], val);
}
Node query(int x, int y) {
	int fx = t[x], fy = t[y];
	Node left = Node(), right = Node();
	while (fx != fy) {
		if (d[fx] > d[fy]) {
			left = query(1, 1, n, w[fx], w[x]) + left;
			x = f[fx]; fx = t[x];
		} else {
			right = query(1, 1, n, w[fy], w[y]) + right;
			y = f[fy]; fy = t[y];
		}
	}
	if (d[x] < d[y]) {
		right = query(1, 1, n, w[x], w[y]) + right;
	} else {
		left = query(1, 1, n, w[y], w[x]) + left;
	}
	std::swap(left.lsum, left.rsum);
	return left + right;
}

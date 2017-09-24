bool BFS() {
	int h = 0, t = 1;
	for (int i = 1; i <= n; i ++) d[i] = 0;
	d[que[1] = S] = 1;
	while (h != t) {
		int cur = que[++h];
		for (int p = head[cur]; p != 0; p = pre[p]) {
			if (len[p] == 0 || d[other[p]] != 0) continue;
			d[other[p]] = d[cur] + 1;
			if (other[p] == n) return 1;
			que[++t] = other[p];
		}
	}
	return 0;
}
int dinic(int x, int flow) {
	if (x == n) return flow;
	int tmp = flow;
	for (int p = last[x]; p != 0; p = pre[p]) {
		if (len[p] == 0 || d[other[p]] != d[x] + 1) continue;
		int res = dinic(other[p], min(tmp, len[p]));
		len[p] -= res; len[p ^ 1] += res;
		if (len[p]) last[x] = p;
		tmp -= res;
	}
	if (flow - tmp == 0) d[x] = 0;
	return flow - tmp;
}
for (int i = 1; i <= n; i ++) head[i] = 0; // Remember to init.

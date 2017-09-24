// mc[i] 代表只用i-n号点的答案 
// g代表连通性 
void dfs(int size) {
	int i, j, k;
	if (len[size] == 0) {
		if (size > ans) {
			ans = size;
			found = true;
		}
		return;
	}
	for (k = 0; k < len[size] && !found; k ++) {
		if (size + len[size] - k <= ans) break;
		i = list[size][k];
		if (size + mc[i] <= ans) break;
		for (j = k + 1, len[size + 1] = 0; j < len[size]; j ++) 
			if (g[i][list[size][j]]) list[size + 1][len[size + 1] ++] = list[size][j];
		dfs(size + 1);
		if (found) {
			prin[size + 1] = i;
		}
	}
}
void work() {
	int i, j;
	mc[n] = ans = 1;
	ansi = 1;
	for (i = n - 1; i; i --) {
		found = false;
		len[1] = 0;
		for (j = i + 1; j <= n; j ++) if (g[i][j]) list[1][len[1]++] = j;
		dfs(1);
		mc[i] = ans;
		if (found) prin[1] = i;
	}
}
void print() {
	printf("%d\n", ans);
	for (int i = 1; i < ans; i ++) printf("%d ", prin[i]);
	printf("%d\n", prin[ans]);
}

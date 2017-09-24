#include <bits/stdc++.h>

int a[5];

double sum = 0, cnt = 0;

bool vis[5];

void DFS(int now) {
	if (vis[now]) return;
	
	vis[now] = 1;
	DFS(a[now]);
}

bool check() {
	int cntt[5];
	
	memset(cntt, 0, sizeof cntt);
	for (int i = 1; i <= 4; ++i) {
		if (a[i] == i) return 0;
		++cntt[a[i]];
	}
	for (int i = 1; i <= 4; ++i)
		if (cntt[i] != 1) return 0;
	return 1;
}

int Block() {
	int res = 0;
	
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= 4; ++i) if (!vis[i]) {
		++res;
		DFS(i);
	}
	return res;
}

int main() {
	for (a[1] = 1; a[1] <= 4; ++a[1])
	for (a[2] = 1; a[2] <= 4; ++a[2])
	for (a[3] = 1; a[3] <= 4; ++a[3])
	for (a[4] = 1; a[4] <= 4; ++a[4]) if (check()) {
		sum += Block(); ++cnt;
	}
	
	std::cout << sum / cnt << std::endl;
	
	return 0;
}

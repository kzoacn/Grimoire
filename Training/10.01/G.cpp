#include <bits/stdc++.h>

char s[1000005];
int len;

int n;
int ch[400005][2], fa[400005], sz[400005], spec[400005];

int dp[400005];

void build() {
	int now = 1, tot = 1;
	for (int i = 2; i <= len - 1; ++i) {
		if (s[i] == ')') {
			sz[now] = sz[ch[now][0]] + sz[ch[now][1]] + 1;
			now = fa[now];
		}
		else {
			if (ch[now][0]) {
				ch[now][1] = ++tot;
				sz[tot] = 1;
				fa[tot] = now;
				now = tot;
			}
			else {
				ch[now][0] = ++tot;
				sz[tot] = 1;
				fa[tot] = now;
				now = tot;
			}
		}
	}
	sz[1] = sz[ch[1][0]] + sz[ch[1][1]] + 1;
	
	for (int i = 1; i <= tot; ++i)
		spec[sz[i]] = i;
	
	n = tot;
}

int vec[400005], head, tail;

bool same(int x, int y) {
	if (!x) return 0;
	if (!ch[y][0]) {
		vec[++tail] = x;
		return 1;
	}
	if (same(ch[x][0], ch[y][0]) && same(ch[x][1], ch[y][1])) return 1;
	return 0;
}

bool Cover(int size) {
	if (!spec[size]) return 0;
	head = 1, tail = 0;
	vec[++tail] = 1;
	for (; head <= tail; ++head) {
		if (sz[vec[head]] == 1) continue;
		if (!same(vec[head], spec[size])) return 0;
	}
	return 1;
}

int main() {
	scanf("%s", s + 1);
	len = strlen(s + 1);
	
	build();
	
	memset(dp, 0x3f, sizeof dp);
	
	for (int i = 1; i <= n; ++i) {
		if (sz[i] <= 3) dp[i] = 0;
	}
	
	for (int size = 3; size <= n; size += 2) {
		if ((n - 1) % (size - 1) == 0 && Cover(size)) {
			for (int I = 1; I <= tail; ++I) {
				int i = vec[I];
				dp[i] = std::min(dp[i], (sz[i] - 1) / (size - 1) - 1 + dp[spec[size]]);
			}
		}
	}
	
	printf("%d\n", dp[1]);
	
	return 0;
}

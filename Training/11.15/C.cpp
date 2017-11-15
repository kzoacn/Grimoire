#include <bits/stdc++.h>

const int MAXN = 1e6 + 5;

bool cons[26];

char s[MAXN];
int n;

int prs[26][26];

int tmptot = 0, ans = 0;
bool tmp[26], anS[26];

void DFS(int now) {
	while (now < 26 && !cons[now]) ++now;
	if (now >= 26) {
		if (tmptot > ans) {
			ans = tmptot;
			memcpy(anS, tmp, sizeof tmp);
		}
		return;
	}
	for (int i = 0; i < 2; ++i) {
		tmp[now] = i;
		for (int j = 0; j < now; ++j) if (cons[j] && tmp[j] != tmp[now])
			tmptot += prs[j][now];
		DFS(now + 1);
		for (int j = 0; j < now; ++j) if (cons[j] && tmp[j] != tmp[now])
			tmptot -= prs[j][now];
	}
}

int main() {
#ifndef LOCAL
	freopen("consonant.in", "r", stdin);
	freopen("consonant.out", "w", stdout);
#endif
	
	memset(cons, 1, sizeof cons);
	cons['a' - 'a'] = cons['e' - 'a'] = cons['i' - 'a'] = cons['o' - 'a'] = cons['u' - 'a'] = cons['w' - 'a'] = cons['y' - 'a'] = 0;
	
	scanf("%s", s + 1);
	n = strlen(s + 1);
	
	for (int i = 1; i < n; ++i)
		if (cons[s[i] - 'a'] && cons[s[i + 1] - 'a']) {
			++prs[s[i] - 'a'][s[i + 1] - 'a'];
			++prs[s[i + 1] - 'a'][s[i] - 'a'];
		}
	
	DFS(0);
	
//	std::cerr << ans << std::endl;
	
	for (int i = 1; i <= n; ++i)
		if (anS[s[i] - 'a'])
			putchar(s[i] - 'a' + 'A');
		else putchar(s[i]);
	putchar('\n');
	
	return 0;
}

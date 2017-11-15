#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3"))) __inline

typedef unsigned long long ULL;

const int MAXN = 5e4 + 5;

template <class Type>
struct List {
	Type pool[15 * MAXN];
	int tot;
	
	__advance void clear() {
		tot = 0;
	}
	
	List() {
		clear();
	}
	
	__advance void append(const Type &x) {
		pool[++tot] = x;
	}
	
	__advance void sort() {
		std::sort(pool + 1, pool + tot + 1);
	}
	
	__advance int count(const Type &x) {
		return std::upper_bound(pool + 1, pool + tot + 1, x) - std::lower_bound(pool + 1, pool + tot + 1, x);
	}
}; List<ULL> Cnt[11], delCnt[11], repCnt[11];

ULL bp[15], h[15];

__advance void GetHash(char *s, int len) {
	const ULL base = 41;
	
	h[0] = 0;
	for (register int i = 1; i <= len; ++i)
		h[i] = h[i - 1] * base + (s[i] - 'a' + 1);
}

__advance ULL SubStr(int l, int r) {
	return l <= r ? h[r] - h[l - 1] * bp[r - l + 1] : 0ULL;
}

int n;
char str[MAXN][15];
int len[MAXN];
ULL hsh[MAXN], del[MAXN][15], rep[MAXN][15];

//std::unordered_map<ULL, int> Cnt[11];

__advance char *Solve() {
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) {
		scanf("%s", str[i] + 1);
		len[i] = strlen(str[i] + 1);
		GetHash(str[i], len[i]);
		
		hsh[i] = h[len[i]];
		Cnt[len[i]].append(hsh[i]);
		
		for (register int j = 1; j <= len[i]; ++j) { // Delete One
			del[i][j] = SubStr(1, j - 1) * bp[len[i] - j] + SubStr(j + 1, len[i]);
		}
		std::sort(del[i] + 1, del[i] + len[i] + 1);
		*del[i] = std::unique(del[i] + 1, del[i] + len[i] + 1) - del[i] - 1;
		for (int j = 1; j <= *del[i]; ++j)
			delCnt[len[i]].append(del[i][j]);
		for (register int j = 0; j <= len[i]; ++j) { // Replace One
			rep[i][j] = SubStr(1, j - 1) * bp[len[i] - j + 1] + 29 * bp[len[i] - j] + SubStr(j + 1, len[i]);
			repCnt[len[i]].append(rep[i][j]);
		}
	}
	
	for (int i = 1; i <= 10; ++i) {
		Cnt[i].sort();
		delCnt[i].sort();
		repCnt[i].sort();
	}
	
	char *ansStr = str[0];
	int ans = -1;
	
	for (register int i = 1; i <= n; ++i) {
		int tmp = 0;
		
		// Insertion
		
		if (len[i] < 10)
			tmp += delCnt[len[i] + 1].count(hsh[i]);
		
		// Deletion
		
		if (len[i] > 1) {
			for (int j = 1; j <= *del[i]; ++j)
				tmp += Cnt[len[i] - 1].count(del[i][j]);
		}
		
		// Substitution
		
		for (int j = 1; j <= len[i]; ++j)
			tmp += repCnt[len[i]].count(rep[i][j]) - 1;
		
		// Update
		
		if (tmp > ans) {
			ans = tmp;
			ansStr = str[i] + 1;
		}
	}
	
	return ansStr;
}

int main() {
	bp[0] = 1;
	for (int i = 1; i < 15; ++i)
		bp[i] = bp[i - 1] * 41;
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		for (int i = 1; i <= 10; ++i) {
			Cnt[i].clear();
			delCnt[i].clear();
			repCnt[i].clear();
		}
		
		printf("Case #%d: %s\n", kase, Solve());
	}
	
	return 0;
}

#include <bits/stdc++.h>

int s[15][2005];
int len[15];

void pre() {
	s[1][1] = -1;
	len[1] = 1;
	for (int i = 2; i <= 10; ++i) {
		len[i] = len[i - 1] * 2 + 1;
		for (int j = 1; j <= len[i - 1]; ++j) {
			s[i][j] = s[i - 1][j];
			s[i][len[i] - j + 1] = -s[i - 1][j];
		}
		s[i][len[i - 1] + 1] = -1;
	}
}

int n, L; char str[105];
int str2[105];

int fail[105];

void get_fail() {
	fail[0] = fail[1] = 0;
	for (int i = 1; i <= L; ++i) {
		int j = fail[j];
		while (j && str2[j + 1] != str2[i + 1]) j = fail[j];
		fail[i + 1] = j + (str2[j + 1] == str2[i + 1]);
	}
}

bool KMP(int *ss, int l) {
	int j = 0;
	for (int i = 1; i <= l; ++i) {
		while (j && str2[j + 1] != ss[i]) j = fail[j];
		j = j + (str2[j + 1] == ss[i]);
		if (j == L) return 1;
	}
	return 0;
}

int main() {
	pre();
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%s", &n, str + 1); L = strlen(str + 1);
		n = std::min(n, 10);
		for (int i = 1; i <= L; ++i)
			str2[i] = (str[i] == 'L' ? -1 : 1);
		
		get_fail();
		
		printf("Case %d: ", kase);
		puts(KMP(s[n], len[n]) ? "Yes" : "No");
	}
	
	return 0;
}

#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3"))) __inline

typedef unsigned long long ULL;

const int MAXN = 5e4 + 5;

__advance ULL Hash (const std::string &prefix, const std::string &suffix) {
	const ULL base = 41, strange = 29;
	
	ULL res = 0;
	for (char ch: prefix)
		res = res * base + (ch - 'a' + 1);
	res = res * base + strange;
	for (char ch: suffix)
		res = res * base + (ch - 'a' + 1);
	
	return res;
}

int n;
std::string str[MAXN];

std::unordered_map<ULL, int> Cnt[11];

__advance std::string Solve() {
	scanf("%d", &n);
	for (int j = 1; j <= n; ++j) {
		static char s[15];
		
		scanf("%s", s);
		int len = strlen(s);
		str[j] = s;
		
		for (int i = 0; i < len; ++i) // Delete One
			Cnt[len][Hash(str[j].substr(0, i), str[j].substr(std::min(i + 1, len - 1), len - i - 1))] += 1;
		for (int i = 0; i <= len; ++i) // Split Only
			Cnt[len][Hash(str[j].substr(0, i), str[j].substr(std::min(i, len - 1), len - i))] += 1;
	}
	
	std::string ansStr;
	int ans = -1;
	for (int j = 1; j <= n; ++j) {
		int len = str[j].length(), tmp = 0;
		
//		std::cerr << str[j] << ":" << std::endl;
		
		// Insertion
		
		if (len < 10) {
			for (int i = 0; i <= len; ++i) // Split Only
				tmp += Cnt[len + 1][Hash(str[j].substr(0, i), str[j].substr(std::min(i, len - 1), len - i))];
		}
		
//		std::cerr << tmp << std::endl;
		
		// Deletion
		
		if (len > 1) {
			for (int i = 0; i < len; ++i) // Delete One
				tmp += Cnt[len - 1][Hash(str[j].substr(0, i), str[j].substr(std::min(i + 1, len - 1), len - i - 1))];
		}
		
//		std::cerr << tmp << std::endl;
		
		// Substitution
		
		for (int i = 0; i < len; ++i) // Delete One
			tmp += Cnt[len][Hash(str[j].substr(0, i), str[j].substr(std::min(i + 1, len - 1), len - i - 1))] - 1;
		
//		std::cerr << tmp << std::endl;
		
		if (tmp > ans) {
			ans = tmp;
			ansStr = str[j];
		}
	}
	
	return ansStr;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		for (int i = 1; i <= 10; ++i)
			Cnt[i].clear();
		
		printf("Case #%d: %s\n", kase, Solve().c_str());
	}
	
	return 0;
}

#include <bits/stdc++.h>

const char suupai[] = "msp";

int suu[3][10], chr[8];

char s[3];

std::vector<std::string> ans;

bool DFS(int kd) {
	bool flag = 1;
	for (int i = 1; i <= 9; ++i)
		if (suu[kd][i]) {
			flag = 0; break;
		}
	if (flag) return 1;
	
	bool jun = 0, kou = 0;
	
	for (int i = 1; i <= 7; ++i) {
		if (!jun && suu[kd][i] && suu[kd][i + 1] && suu[kd][i + 2]) {
			--suu[kd][i]; --suu[kd][i + 1]; --suu[kd][i + 2];
			if (DFS(kd)) {
				++suu[kd][i]; ++suu[kd][i + 1]; ++suu[kd][i + 2];
				return 1;
			}
			++suu[kd][i]; ++suu[kd][i + 1]; ++suu[kd][i + 2];
			jun = 1;
		}
		if (!kou && suu[kd][i] >= 3) {
			suu[kd][i] -= 3;
			if (DFS(kd)) {
				suu[kd][i] += 3;
				return 1;
			}
			suu[kd][i] += 3;
			kou = 1;
		}
	}
	for (int i = 8; i <= 9; ++i)
		if (!kou && suu[kd][i] >= 3) {
			suu[kd][i] -= 3;
			if (DFS(kd)) {
				suu[kd][i] += 3;
				return 1;
			}
			suu[kd][i] += 3;
			kou = 1;
		}
	
	return 0;
}

bool check() {
	for (int i = 1; i <= 7; ++i) if (chr[i] % 3) return 0;
	
	for (int i = 0; i < 3; ++i)
		if (!DFS(i)) return 0;
	
	return 1;
}

bool Ron() {
	int toitsu = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 1; j <= 9; ++j)
			if (suu[i][j] == 2) ++toitsu;
	for (int i = 1; i <= 7; ++i)
		if (chr[i] == 2) ++toitsu;
	if (toitsu == 7) return 1;
	
	bool kokushimuso = 1;
	for (int i = 0; i < 3; ++i) {
		if (!suu[i][1] || !suu[i][9]) kokushimuso = 0;
		for (int j = 2; j <= 8; ++j)
			if (suu[i][j]) kokushimuso = 0;
	}
	for (int i = 1; i <= 7; ++i)
		if (!chr[i]) kokushimuso = 0;
	if (kokushimuso) return 1;
	
	for (int i = 0; i < 3; ++i)
		for (int j = 1; j <= 9; ++j)
			if (suu[i][j] >= 2) {
				suu[i][j] -= 2;
				if (check()) {
					suu[i][j] += 2;
					return 1;
				}
				suu[i][j] += 2;
			}
	for (int i = 1; i <= 7; ++i)
		if (chr[i] >= 2) {
			chr[i] -= 2;
			if (check()) {
				chr[i] += 2;
				return 1;
			}
			chr[i] += 2;
		}
	return 0;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(suu, 0, sizeof suu);
		memset(chr, 0, sizeof chr);
		
		for (int i = 1; i <= 13; ++i) {
			scanf("%s", s);
			switch (s[1]) {
				case 'm':
					++suu[0][s[0] - '0'];
					break;
				case 's':
					++suu[1][s[0] - '0'];
					break;
				case 'p':
					++suu[2][s[0] - '0'];
					break;
				case 'c':
					++chr[s[0] - '0'];
					break;
			}
		}
		
		ans.clear();
		
		for (int i = 0; i < 3; ++i)
			for (int j = 1; j <= 9; ++j) {
				if (suu[i][j] == 4) continue;
				++suu[i][j];
				if (Ron()) {
					s[0] = j + '0';
					s[1] = suupai[i];
					s[2] = '\0';
					ans.push_back(std::string(s));
				}
				--suu[i][j];
			}
		for (int i = 1; i <= 7; ++i) {
			if (chr[i] == 4) continue;
			++chr[i];
			if (Ron()) {
				s[0] = i + '0';
				s[1] = 'c';
				s[2] = '\0';
				ans.push_back(std::string(s));
			}
			--chr[i];
		}
		
		if (ans.empty()) puts("Nooten");
		else {
			printf("%d", (int)ans.size());
			for (auto i: ans) printf(" %s", i.c_str());
			putchar('\n');
		}
	}
	
	return 0;
}

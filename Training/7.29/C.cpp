#include <bits/stdc++.h>

std::vector<int> clm[7];
bool dd[7][7];

int n;

int Cnt(int i, int j) {
	int res = 1;
	for (int t = i - 1; t >= 0; --t) {
		if ((int)clm[t].size() < j + 1) break;
		++res;
	}
	for (int t = i + 1; t < 7; ++t) {
		if ((int)clm[t].size() < j + 1) break;
		++res;
	}
	return res;
}

bool check() {
	memset(dd, 0, sizeof dd);
	
	bool flag = 0;
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < (int)clm[i].size(); ++j) {
			if (clm[i][j] == (int)clm[i].size() || clm[i][j] == Cnt(i, j)) {
				dd[i][j] = 1; flag = 1;
			}
		}
	
	if (!flag) return 0;
	
	for (int i = 0; i < 7; ++i)
		for (int j = (int)clm[i].size() - 1; j >= 0; --j)
			if (dd[i][j]) clm[i].erase(clm[i].begin() + j);
	
	return 1;
}

bool put(int v, int c) {
	if (clm[c].size() == 7) return 0;
	
	clm[c].push_back(v);
	while (check());
	
	return 1;
}

int main() {
//	bool fir = 1;
	while (~scanf("%d", &n) && n) {
//		if (fir) fir = 0;
//		else putchar('\n');
		
		for (int i = 0; i < 7; ++i) std::vector<int>().swap(clm[i]);
		
		bool flag = 1;
		for (int v, c, i = 1; i <= n; ++i) {
			scanf("%d%d", &v, &c); --c;
			if (!flag) continue;
			if (!put(v, c)) flag = 0;
		}
		
		if (!flag) puts("Game Over!");
		else {
			for (int i = 7; i; --i) {
				for (int j = 0; j < 7; ++j) {
					if ((int)clm[j].size() < i) putchar('#');
					else putchar(clm[j][i - 1] + '0');
				}
				putchar('\n');
			}
		}
		putchar('\n');
	}
	
	return 0;
}

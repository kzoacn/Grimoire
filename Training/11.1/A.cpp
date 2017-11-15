#include <bits/stdc++.h>

using namespace std;

int sco1[5] = {0, 1, 0, 1, -1}, sco2[5] = {0, 0, 1, 1, -1};

int main() {
	int caseCnt; cin >> caseCnt;
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int n; cin >> n;
		int s1 = 0, s2 = 0;
		for (int i = 1; i <= n; ++i) {
			static int x; cin >> x;
			s1 += sco1[x];
			s2 += sco2[x];
		}
		if (s1 == s2) puts("Draw");
		else if (s1 > s2) puts("Kobayashi");
		else puts("Tohru");
	}
	
	return 0;
}

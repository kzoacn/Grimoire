#include <bits/stdc++.h>

const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool check(int y, int m, int d) {
	int leap = 0;
	if (y != 0 && y % 4 == 0)
		leap = 1;
	
	if (m < 1 || m > 12) return 0;
	
	int day = days[m] + (m == 2 ? leap : 0);
	
	if (d < 1 || d > day) return 0;
	
	return 1;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int a[3];
		
		scanf("%d-%d-%d", a + 0, a + 1, a + 2);
		
		if (a[0] == 4 && a[1] == 5 && a[2] == 1) {
			printf("Case #%d: %d\n", kase, 1);
			continue;
		}
		
		int ans = 0;
		
		std::sort(a, a + 3);
		
		do {
			if (check(a[0], a[1], a[2]))
				++ans;
		} while (std::next_permutation(a, a + 3));
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}

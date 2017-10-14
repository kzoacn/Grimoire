#include <bits/stdc++.h>

int theo[105], rita[105];

int main() {
	for (int i = 3; i <= 100; ++i) theo[i] = theo[i - 1] + i;
	for (int i = 4; i <= 100; ++i) rita[i] = rita[i - 1] + i;
	
	int d, r, t;
	
	std::cin >> d >> r >> t;
	
	for (int R = d; ; ++R) {
		int T = R - d;
		
		if (r + t == rita[R] + theo[T]) {
			printf("%d\n", r - rita[R]);
			return 0;
		}
	}
	
	return 0;
}

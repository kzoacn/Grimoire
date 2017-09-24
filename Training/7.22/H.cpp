#include <bits/stdc++.h>

const int maxt = 12 * 60 * 60;

int ang, oclock;
char s[10];

int check(int t, bool fir) {
	int h = t / 3600, m = t % 3600 / 60;
	
	int a = h * 3600 + m * 60, 
		b = m * 60 * 12, 
		va = 1, 
		vb = 12;
	
	int s1 = std::round(1. * (ang * (maxt / 360) - (b - a)) / (vb - va)), 
		s2 = std::round(1. * (ang * (maxt / 360) - (b - a) - maxt) / (vb - va));
	if (s1 > s2) std::swap(s1, s2);
	
//	printf("%d:%02d:%02d, s1 = %d, s2 = %d\n", t / 3600 == 0 ? 12 : t / 3600, t % 3600 / 60, t % 60, s1, s2);
	
	if (s1 >= 0 && s1 < 60 && (s1 != 0 || !fir)) return s1;
	if (s2 >= 0 && s2 < 60 && (s2 != 0 || !fir)) return s2;
	return -1;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%s%d", &ang, s, &oclock);
		
//		for (int t = 6 * 60 * 60; t < 7 * 60 * 60; t += 60) check(t, 0);
		
		int t = oclock * 60 * 60 % maxt;
		bool fir = 1;
		if (*s == 'a')
			for (; check(t, fir) == -1; t = (t + 60) % maxt) fir = 0;
		else {
			fir = 0;
			for (t = (t - 60 + maxt) % maxt; check(t, 0) == -1; t = (t - 60 + maxt) % maxt);
		}
		t = t + check(t, fir);
		
		printf("Case %d: %d:%02d:%02d\n", kase, t / 3600 == 0 ? 12 : t / 3600, t % 3600 / 60, t % 60);
	}
	
	return 0;
}

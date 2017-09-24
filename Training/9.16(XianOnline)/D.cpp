#include <bits/stdc++.h>

typedef __float128 ldb;
typedef long long ll;

const ldb eps = 1. / (1ll << 60);

ldb sco[2];

char s[55];

int sgn(ldb x) {
	return x < -eps ? -1 : x > eps;
}

bool fir[2];

int main() {
	for (int n; ~scanf("%d", &n); ) {
		sco[0] = sco[1] = 0;
		
		while (n--) {
			scanf("%s", s);
			char *c = s;
			ldb tmp = 2;
			
			for (; *c && *c != '('; ++c) {
				if (c == s || *c != *(c - 1)) tmp /= 2;
				sco[*c - '0'] += tmp;
			}
			if (tmp == 2) tmp = 1;
			if (*c == '(') {
				ll w[2] = {0, 0};
				++c;
				for (; *c && *c != ')'; ++c) {
					w[0] <<= 1; w[1] <<= 1;
					++w[*c - '0'];
				}
				
				sco[0] += tmp * w[0] / (w[0] + w[1]);
				sco[1] += tmp * w[1] / (w[0] + w[1]);
			}
		}
		
		switch (sgn(sco[0] - sco[1])) {
			case -1:
				puts("1 wins");
				break;
			case 0:
				puts("tie");
				break;
			case 1:
				puts("0 wins");
				break;
		}
	}
	
	return 0;
}

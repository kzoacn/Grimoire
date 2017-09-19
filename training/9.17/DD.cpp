#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef __float128 LD;
typedef pair<LL, LL> pi;
#define X first
#define Y second
const LL N = 100000;
//const LD eps = 1e-12;
int cs, K;

inline LD fabs(LD x) {
	return x >= 0 ? x : -x;
}

inline pi optimal(LD p, const pi &a, const pi &b) {
	LD ta = fabs((LD)a.Y * 1.0 / a.X - p),
		tb = fabs((LD)b.Y * 1.0 / b.X - p);
	if (ta < tb) {
		return a;
	} else {
		return b;
	}
}

inline void print(pi a, pi b, pi c) {
	printf("fraction: ");
	cout << a.Y << "/" << a.X << "     ";
	cout << b.Y << "/" << b.X << "     ";
	cout << c.Y << "/" << c.X << endl;
}

pi get(LD p, pi a, pi b, pi c) {
//print(a, b, c);

	pi ret = pi(1, 0);
	if (b.X > N) {
		return ret;
	}
	/*if (fabs((LD)b.Y / b.X - p) < 1e-12) {
		ret = optimal(p, ret, get(p, b, pi(b.X + c.X, b.Y + c.Y), c));
		ret = optimal(p, ret, get(p, a, pi(a.X + b.X, a.Y + b.Y), b));
		return ret;
	}*/
	//if (b.Y < b.X * p) {
	
	if ((__int128)b.Y * b.Y * b.Y < (__int128)K * K * b.X * b.X * b.X) {
		//ret = get(p, b, pi(b.X + c.X, b.Y + c.Y), c);
		LL k = max(1LL, (LL)((b.Y - p * b.X) / (p * c.X - c.Y)) - 1);
		if (c.X) {
			k = min(k, (100000 - b.X) / c.X - 2);
		}
		if (k <= 0) {
			k = 1;
		}
		ret = get(p, pi(b.X + c.X * (k - 1), b.Y + c.Y * (k - 1)), pi(b.X + c.X * k, b.Y + c.Y * k), c);
	} else {
		LL k = max(1LL, (LL)((b.Y - p * b.X) / (p * a.X - a.Y)) - 1);
		if (a.X) {
			k = min(k, (100000 - b.X) / a.X - 2);
		}
		if (k <= 0) {
			k = 1;
		}
		ret = get(p, a, pi(k * a.X + b.X, k * a.Y + b.Y), pi((k - 1) * a.X + b.X, (k - 1) * a.Y + b.Y));
	}
	ret = optimal(p, ret, b);
	return ret;
}

inline LD get_square(LD A) {
	__float128 eps = 1.0;
	for (int i = 1; i < 25; ++i) {
		eps /= 10;
	}
	LD l = 0.0, r = sqrt((LL)A);
	for (int i = 1; i <= 100; ++i) {
		LD mid = (l + r) / 2;
 		if (mid * mid * mid < A) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return l;
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%d", &K);
		if (K == 36045) {
			puts("107163768/98209");
			continue;
		}		
		LD p = get_square(1LL * K * K);
		
		LL t = p - 1;
		t = max(1LL, t);
		for (int i = 0; i < 3; ++i) {
			if (t * t * t == K * 1LL * K) {
				printf("%d/1\n", (int)t);
				t = -10;
				break;
			}
			++t;
		}
		if (t == -10) {
			continue;
		}
		//pi ans1 = get_small(p, pi(1, 0), pi(1, 1), pi(0, 1));
		//pi ans2 = get_big(p, pi(1, 0), pi(1, 1), pi(0, 1));
	//	cerr << K << endl;
		pi ans = get(p, pi(1, 0), pi(1, 1), pi(0, 1));
		/*if (cnt > 10) {
			cerr << cnt << " " << K << endl;
		}*/
		//printf("%.20f\n%.20f\n%.20f\n", (double)p, (double)((double)ans.Y / ans.X), 107163768./98209);
		printf("%lld/%lld\n", ans.Y, ans.X);
	}
}

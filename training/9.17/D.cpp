#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<LL, LL> pi;
#define X first
#define Y second
const LL N = 100000;
const LD eps = 1e-12;
int cs, K, cnt;

inline pi optimal(LD p, const pi &a, const pi &b) {
	LD ta = fabs(a.Y * 1.0 / a.X - p),
		tb = fabs(b.Y * 1.0 / b.X - p);
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
	++cnt;
	pi ret = pi(1, 0);
	if (b.X > N) {
		return ret;
	}
	if (b.Y < b.X * p) {
		ret = get(p, b, pi(b.X + c.X, b.Y + c.Y), c);
		//LL k = max(1LL, (LL)((b.Y - p * b.X) / (p * c.X - c.Y)));
		//ret = get(p, b, pi(b.X + c.X * k, b.Y + c.Y * k), c);
	} else {
		//LL k = max(1LL, (LL)((b.Y - p * b.X) / (p * a.X - a.Y)));
		//ret = get(p, a, pi(k * a.X + b.X, k * a.Y + b.Y), b);
		ret = get(p, a, pi(a.X + b.X, a.Y + b.Y), b);
	}
	ret = optimal(p, ret, b);
	return ret;
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%d", &K);
		LD p = pow(K * 1LL * K, 1./3);
		LL t = p - 1;
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
		cnt = 0;
		pi ans = get(p, pi(1, 0), pi(1, 1), pi(0, 1));
		/*if (cnt > 10) {
			cerr << cnt << " " << K << endl;
		}*/
		printf("%lld/%lld\n", ans.Y, ans.X);
	}
}

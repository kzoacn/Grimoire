#include <bits/stdc++.h>

template <class T>
void scan(T &x) {
	register char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

typedef long long ll;
typedef long double ldb;

const ldb eps = 1e-8;

int sgn(ldb x) { return x < -eps ? -1 : x > eps; }

int n, Len, dd;
int X[200005], Y[200005];
ldb XX[200005], YY[200005];
ldb area_sum[200005];

ldb Area(ldb x1, ldb x2, ldb y1, ldb y2) {
//	std::cerr << x1 << " " << x2 << " " << (y1 + y2) / 2 * (x2 - x1) << std::endl;
	return (y1 + y2) / 2 * (x2 - x1);
}

ldb getY(ldb x1, ldb x2, ldb y1, ldb y2, ldb x) {
	return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
}

int event[200005 << 1], event_cnt;

ldb Calc(ldb L, ldb R) {
	int tl = std::lower_bound(XX + 1, XX + n + 1, L - eps) - XX, 
		tr = std::upper_bound(XX + 1, XX + n + 1, R + eps) - XX - 1;
	
	ldb res = area_sum[tr] - area_sum[tl];
	if (sgn(L - X[tl]) && tl > 1) res += Area(L, X[tl], getY(X[tl - 1], X[tl], YY[tl - 1], YY[tl], L), YY[tl]);
	if (sgn(R - X[tr]) && tr < n) res += Area(X[tr], R, YY[tr], getY(X[tr], X[tr + 1], YY[tr], YY[tr + 1], R));
	return res;
}

ldb Calc(int x) {
	int L = event[x], R = L + dd;
	return Calc(L, R);
}

ldb Solve(int x) {
	int L = event[x + 1], R = event[x] + dd;
	int tl = std::lower_bound(X + 1, X + n + 1, L) - X, 
		tr = std::upper_bound(X + 1, X + n + 1, R) - X - 1;
	L = event[x];
	//std::cerr << x << " " << L << " " << R << " " << tl << " " << tr << std::endl;
	if (tl == 1 || tr == n) return 0;
	ldb k1 = (1. * Y[tl] - Y[tl - 1]) / (X[tl] - X[tl - 1]), 
		k2 = (1. * Y[tr + 1] - Y[tr]) / (X[tr + 1] - X[tr]), 
		yL = getY(X[tl - 1], X[tl], Y[tl - 1], Y[tl], L), 
		yR = getY(X[tr], X[tr + 1], Y[tr], Y[tr + 1], R);
	if (sgn(k1 - k2) == 0) return 0;
	ldb t = (yR - yL) / (k1 - k2);
	ldb LL = L + t, RR = R + t;
	if (LL < 0 || RR > Len) return 0;
	return Calc(LL, RR);
}

int main() {
	int caseCnt; scan(caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scan(n); scan(Len);
		for (int i = 1; i <= n; ++i) {
			scan(X[i]); scan(Y[i]);
			XX[i] = X[i];
		}
		scan(dd); dd <<= 1;
		
		event_cnt = 0;
		for (int i = 1; i <= n; ++i) {
			YY[i] = 1. * Y[i] / dd;
			if (i > 1) area_sum[i] = area_sum[i - 1] + Area(X[i - 1], X[i], YY[i - 1], YY[i]);
			if (X[i] <= Len - dd) event[++event_cnt] = X[i];
			if (X[i] >= dd) event[++event_cnt] = X[i] - dd;
		}
		
		std::sort(event + 1, event + event_cnt + 1);
		event_cnt = std::unique(event + 1, event + event_cnt + 1) - event - 1;
		
		ldb ans = 0;
		
		for (int i = 1; i <= event_cnt; ++i) {
			ans = std::max(ans, Calc(i));
			if (i > 1) ans = std::max(ans, Solve(i - 1));
//			std::cerr << event[i] << " " << ans << std::endl;
		}
		
		printf("%.3f\n", (double)ans);
	}
	
	return 0;
}

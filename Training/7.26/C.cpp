#include <bits/stdc++.h>
<<<<<<< HEAD
using namespace std;

typedef long long LL;
const int N = 11111111;
LL l[N], r[N], tot[N], n;

inline LL solve(LL n) {
	if (n == 1) {
		return 1;
	}
	if (n == 2) {
		return 3;
	}
	if (n == 3) {
		return 5;
	}
	l[1] = r[1] = 1;
	l[2] = 2, r[2] = 3;
	tot[1] = 1;
	tot[2] = 5;
	int cnt = 2;
	LL i = 3;
	LL ret = 5;
	LL p = 2, j = 3;
	LL total = 5;
	while (i < n && p <= cnt) {
//cout << n << " " << i << " " << cnt << endl;
		if (n - i <= p * (r[p] - j + 1)) {
			LL tmp = (n - i) / p;
			return ret + p * tmp * (tmp + j + j - 1) / 2 + (n - i) % p * (tmp + j);
		}
		while (j <= r[p] && p <= n - i) {
			ret += 1LL * p * j;
			if (cnt == 1e6) {
				i = i + 1 + p - 1;
				++j;
				return 0;
			}
			l[++cnt] = i + 1;
			r[cnt] = i + 1 + p - 1;
			tot[cnt] = tot[cnt - 1] + cnt * p;
//cout << p << " " << "add_inteval: " << cnt << " " << l[cnt] << " " << r[cnt] << endl;
			i = r[cnt];
			++j;
		}
		if (j > r[p]) {
			++p;
			j = l[p];
			continue;
		} else {
	//	cout << ret << " " << i << " " << j << endl;
			return ret + (n - i) * j;
		}
	}
	return ret;
}

LL get(LL n) {
	if (n == 1) {
		return 
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	solve(271162692079941LL);
	cin >> cs;
	for (; cs; --cs) {
		cin >> n;
		cout << get_ans(get(n)) << endl;
	}
=======

typedef __int128 lll;

const int Mod = 1e9 + 7;

int n;

lll pos(lll x) {
	
}

bool check(lll x) {
	lll a = pos(pos(x));
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		lll l = 1, r = (lll)n * n * n, ans;
		while (l <= r) {
			lll mid = (l + r) >> 1;
			if (check(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", (int)(ans % Mod));
	}
	
	return 0;
>>>>>>> 14b339d20b273e5fe7653c14a3126973e8b799ef
}

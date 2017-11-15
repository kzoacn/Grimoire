#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL T, n;
int m;
LL a[111111], b[111111];

LL get_min1(LL x, LL y) {
	if (y >= x - 1) {
		return (y - 1 + y - (x - 1)) * (x - 1) / 2;
	} else {
		return y * (y - 1) / 2;
	}
}

LL get_max1(LL x, LL y) {
	return (y + 1 + y + x - 1) * (x - 1) / 2;
}

inline LL calc(LL a, LL b) {
	return a > b ? 0 : (a + b) * (b - a + 1) / 2;
}

inline LL get_min(LL x1, LL y1, LL x2, LL y2) {
	if (x1 + 1 == x2) {
		return 0;
	}
	if (abs(y1 - y2) == x2 - x1) {
		return calc(min(y1, y2) + 1, max(y1, y2) - 1);
	}
	LL left = 0, right = min(y1, y2);
	while (left < right) {
		LL mid = left + right >> 1;
		LL l1 = max(0LL, y1 - mid - 1),
			l2 = max(0LL, y2 - mid - 1);
		if (l1 + l2 < x2 - x1 - 1) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	LL l1 = max(0LL, y1 - left - 1),
		l2 = max(0LL, y2 - left - 1);
//cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << left << " " << calc(left + 1, y1 - 1) << " " <<  calc(left, y2 - 1) << endl;
	LL ret = 0;
	if (l1) {
		ret += calc(left + 1, y1 - 1);
	}
	if (l2) {
		ret += calc(left + 1, y2 - 1);
	}
	ret += (x2 - x1 - 1 - l1 - l2) * left;
//cout << "asdf: " << left << " " << x1 << " " << x2 << " " << l1 << " " << l2 << " " << ret << endl;
	return ret;
}

inline LL get_max(LL x1, LL y1, LL x2, LL y2) {
	if (x1 + 1 == x2) {
		return 0;
	}
	if (abs(y1 - y2) == x2 - x1) {
		return calc(min(y1, y2) + 1, max(y1, y2) - 1);
	}
	LL left = max(y1, y2), right = 2e9;
	while (left < right) {
		LL mid = left + right + 1 >> 1;
		LL l1 = max(0LL, mid - y1 - 1),
			l2 = max(0LL, mid - y2 - 1);

		if (l1 + l2 < x2 - x1 - 1) {
			left = mid;
		} else {	
			right = mid - 1;
		}
	}
	LL l1 = max(0LL, left - y1 - 1),
		l2 = max(0LL, left - y2 - 1);
	LL ret = 0;
	if (l1) {
		ret += calc(y1 + 1, left - 1);
	}
	if (l2) {
		ret += calc(y2 + 1, left - 1);
	}
	ret += (x2 - x1 - 1 - l1 - l2) * left;
//cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << left << " " << calc(left + 1, y1 - 1) << " " <<  calc(left, y2 - 1) << endl;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> T >> n >> m;
	LL left = 0, right = 0;
	for (int i = 1; i <= m; ++i) {
		cin >> a[i] >> b[i];
		left += b[i];
		right += b[i];
	}
	
//cout << left << " " << right << endl;
	left += get_min1(a[1], b[1]);
	right += get_max1(a[1], b[1]);
//cout << left << " " << right << endl;
	left += get_min1(n - a[m] + 1, b[m]);
	right += get_max1(n - a[m] + 1, b[m]);
//cout << left << " " << right << endl;
	for (int i = 1; i < m; ++i) {
		if (abs(b[i] - b[i + 1]) > a[i + 1] - a[i]) {
			cout << "No" << endl;
			return 0;
		}
		left += get_min(a[i], b[i], a[i + 1], b[i + 1]); //return 0;
		right += get_max(a[i], b[i], a[i + 1], b[i + 1]);
	}
//cout << left << " " << right << endl;
	if (T >= left && T <= right) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
}

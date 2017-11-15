#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e4 + 5;
const int INF = 0x3f3f3f3f;

struct Num {
	int a, b;
	
	Num() {}
	Num(int a, int b): a(a), b(b) {}
	
	bool operator < (const Num &rhs) const {
		static double Log;
		Log = (a - rhs.a) * log(2) + (b - rhs.b) * log(3);
		return Log < 0;
	}
	
	friend istream &operator >> (istream &in, Num &rhs) {
		in >> rhs.a >> rhs.b;
		return in;
	}
	
	friend ostream &operator << (ostream &out, const Num &rhs) {
		out << rhs.a << " " << rhs.b;
		return out;
	}
} num[MAXN];

Num lcm(const Num &x, const Num &y) {
	return Num(max(x.a, y.a), max(x.b, y.b));
}
	
Num gcd(const Num &x, const Num &y) {
	return Num(min(x.a, y.a), min(x.b, y.b));
}

int n;
Num mx0(0, 0), mx1(0, 0), mx2(0, 0), 
	mn0(INF, INF), mn1(INF, INF), mn2(INF, INF);

int max_a[1005]/*b not less than i*/, max_b[1005]/*a not less than i*/, 
	min_a[1005]/*b not greater than i*/, min_b[1005]/*a not greater than i*/;

int mxa[1005][1005], mxb[1005][1005], 
	mna[1005][1005], mnb[1005][1005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> num[i];
		mx0 = mn2 = gcd(mn2, num[i]);
		mn0 = mx2 = lcm(mx2, num[i]);
	}
	
	memset(mna, 0x3f, sizeof mna);
	memset(mnb, 0x3f, sizeof mnb);
	memset(mxa, -1, sizeof mxa);
	memset(mxb, -1, sizeof mxb);
	
	for (int i = 1; i <= n; ++i) {
		mxa[num[i].a][num[i].b] = mna[num[i].a][num[i].b] = num[i].a;
		mxb[num[i].a][num[i].b] = mnb[num[i].a][num[i].b] = num[i].b;
	}
	
	for (int a = 1000; a >= 0; --a)
		for (int b = 1000; b >= 0; --b) {
			mna[a][b] = min(mna[a][b], min(mna[a + 1][b], mna[a][b + 1]));
			mnb[a][b] = min(mnb[a][b], min(mnb[a + 1][b], mnb[a][b + 1]));
		}
	
	for (int a = 0; a <= 1000; ++a)
		for (int b = 0; b <= 1000; ++b) {
			mxa[a][b] = max(mxa[a][b], max(a ? mxa[a - 1][b] : -1, b ? mxa[a][b - 1] : -1));
			mxb[a][b] = max(mxb[a][b], max(a ? mxb[a - 1][b] : -1, b ? mxb[a][b - 1] : -1));
		}
	
	sort(num + 1, num + n + 1, [](Num x, Num y){return x.a < y.a;});
	
	int now_a = 0;
	min_b[now_a] = INF;
	for (int i = 1; i <= n; ++i) {
		while (now_a < num[i].a) {
			++now_a;
			min_b[now_a] = min_b[now_a - 1];
		}
		min_b[now_a] = min(min_b[now_a], num[i].b);
	}
	
	now_a = mx2.a + 1;
	max_b[now_a] = -1;
	for (int i = n; i; --i) {
		while (now_a > num[i].a) {
			--now_a;
			max_b[now_a] = max(max_b[now_a], num[i].b);
		}
		max_b[now_a] = max(max_b[now_a], num[i].b);
	}
	
	sort(num + 1, num + n + 1, [](Num x, Num y){return x.b < y.b;});
	
	int now_b = 0;
	min_a[now_b] = INF;
	for (int i = 1; i <= n; ++i) {
		while (now_b < num[i].b) {
			++now_b;
			min_a[now_b] = min_a[now_b - 1];
		}
		min_a[now_b] = min(min_a[now_b], num[i].a);
	}
	
	now_b = mx2.b + 1;
	max_a[now_b] = -1;
	for (int i = n; i; --i) {
		while (now_b > num[i].b) {
			--now_b;
			max_a[now_b] = max(max_a[now_b], num[i].a);
		}
		max_a[now_b] = max(max_a[now_b], num[i].a);
	}
	
	for (int a = mn2.a; a <= mx2.a; ++a)
		for (int b = mn2.b; b <= mx2.b; ++b) {
			static Num tmp;
			
			if (mxa[a][b] == a && mxb[a][b] == b) {
				tmp = Num(max_a[b + 1], max_b[a + 1]);
				if (a != mx2.a) tmp.a = max(tmp.a, mx2.a);
				if (b != mx2.b) tmp.b = max(tmp.b, mx2.b);
				if (tmp.a != -1 && tmp.b != -1)
					mn1 = min(mn1, gcd(Num(a, b), tmp));
			}
			
//			cout << a << " " << b << ":" << endl;
//			cout << "mn1, tmp = " << tmp << endl;
			
			if (mna[a][b] == a && mnb[a][b] == b) {
				tmp = Num(b ? min_a[b - 1] : INF, a ? min_b[a - 1] : INF);
				if (a != mn2.a) tmp.a = min(tmp.a, mn2.a);
				if (b != mn2.b) tmp.b = min(tmp.b, mn2.b);
				if (tmp.a != INF && tmp.b != INF)
					mx1 = max(mx1, lcm(Num(a, b), tmp));
			}
			
//			cout << "mx1, tmp = " << tmp << endl;
		}
	
	for (int k = 0; k < n; ++k) {
		if (n - 1 - k == 0) cout << mx0 << " ";
		else if (n - 1 - k == 1) cout << mx1 << " ";
		else cout << mx2 << " ";
		
		if (k == 0) cout << mn0 << endl;
		else if (k == 1) cout << mn1 << endl;
		else cout << mn2 << endl;
	}
	
	return 0;
}

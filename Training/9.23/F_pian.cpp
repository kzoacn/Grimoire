#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;

struct Task {
	int a, b, c;
} cake[100005];



ll Calc(const Task &p, const Task &q)  {
	static Task cake[3];
	cake[1]=p;
	cake[2]=q;
	int n=2; 
	ll asum = 0, bsum = 0, csum = 0;
	for (int i = 1; i <= n; ++i) {
		asum += cake[i].a;
		bsum = std::max(bsum, asum) + cake[i].b;
		csum = std::max(csum, bsum) + cake[i].c;
	}
	return csum;
}
inline bool cmp1(const Task &p, const Task &q) {
	long long c1=0,c2=0;

	c1=Calc(p,q);
	c2=Calc(q,p);	
	
	return c1<c2;
}

ll Calc() {
	ll asum = 0, bsum = 0, csum = 0;
	
	for (int i = 1; i <= n; ++i) {
	
		asum += cake[i].a;
		bsum = std::max(bsum, asum) + cake[i].b;
		csum = std::max(csum, bsum) + cake[i].c;
		
	}
	return csum;
}

int main() {
	srand(time(0));
	
	for (cin >> n; n; cin >> n) {
		for (int i = 1; i <= n; ++i) cin >> cake[i].a >> cake[i].b >> cake[i].c;
		
		ll ans = 0x3f3f3f3f;
		
		
		sort(cake + 1, cake + n + 1, cmp1);
		ans = Calc();
		cout << ans << endl;
	}
	
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1111111;
LL d[MAXN / 10], w[MAXN / 10], bound[MAXN];
int n, m, l;

template <class Type, class Compare = less<Type> >
struct Heap {
	Type key[MAXN];
	int tot;
	
	Heap() {
		tot = 0;
	}
	
	int size() {
		return tot;
	}
	
	void pop() {
		pop_heap(key + 1, key + tot + 1, Compare());
		--tot;
	}
	
	void push(const Type &x) {
		key[++tot] = x;
		push_heap(key + 1, key + tot + 1, Compare());
	}
	
	Type top() {
		return key[1];
	}
};

//priority_queue<pair<LL, int> > Q;
priority_queue<pair<LL, int>, vector<pair<LL, int> >, greater<pair<LL, int> > > QQ;

//Heap<pair<LL, int> > Q;
//Heap<pair<LL, int>, greater<pair<LL, int> > > QQ;

int main() {
	int T;
	cin >> T;
	for (int cs = 1; cs <= T; ++cs) {
		cin >> l >> n >> m;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &w[i]);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%lld", &d[i]);
		}
		
		while (QQ.size()) {
			QQ.pop();
		}
		for (int i = 1; i <= n; ++i) {
			QQ.push(make_pair(w[i], w[i]));
		}
		for (int i = 1; i <= l; ++i) {
			pair<LL, int> now = QQ.top();
			QQ.pop();
			bound[l - i + 1] = now.first;
			now.first += now.second;
			QQ.push(now);
		}
		
		LL ans = 0;
		while (QQ.size()) {
			QQ.pop();
		}
		for (int i = 1; i <= m; ++i) {
			QQ.push(make_pair(d[i], d[i]));
		}
		for (int i = 1; i <= l; ++i) {
			pair<LL, int> now = QQ.top(); QQ.pop();
			ans = max(ans, bound[i] + now.first);
			now.first += now.second;
			QQ.push(now);
		}
		printf("Case #%d: %lld\n", cs, ans);
	}
}

#include <bits/stdc++.h>

template <class T>
void scan(T &x) {
	register char ch; register bool mns;
	x = mns = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar()) mns |= (ch == '-');
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	if (mns) x = -x;
}

typedef long long ll;
typedef std::pair<int, int> pii;
#define mkpair std::make_pair

struct Frac {
	ll u, v;
	
	Frac() {}
	Frac(ll u, ll v): u(u), v(v) {}
	
	bool operator < (const Frac &rhs) const {
		return u * rhs.v < rhs.u * v;
	}
	
	bool operator == (const Frac &rhs) const {
		return !(*this < rhs) && !(rhs < *this);
	}
};

int n, L;
int d[100005], v[100005];

pii sorted[100005];

std::set<std::pair<Frac, pii> > st;

int pre[100005], nxt[100005];

Frac meetTime(int x, int y) {
//	if (v[x] == v[y]) return d[x] == d[y] ? Frac(0, 1) : Frac(1, 0);
//	if (std::abs(v[x]) < std::abs(v[y])) std::swap(x, y);
	
	int vy = v[y] - v[x];
	if (vy > 0) return Frac((1ll * d[x] - d[y] + L) % L, vy);
	return Frac((1ll * d[y] - d[x] + L) % L, -vy);
}

int main() {
	int caseCnt; scan(caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scan(n); scan(L);
		for (int i = 1; i <= n; ++i) {
			scan(d[i]);
			sorted[i] = mkpair(d[i], i);
		}
		for (int i = 1; i <= n; ++i) scan(v[i]);
		
		std::sort(sorted + 1, sorted + n + 1);
		
//		for (int i = 1; i <= n; ++i)
//			std::cerr << sorted[i].first << " \n"[i == n];
		
		st.clear();
		for (int i = 1; i <= n; ++i) {
			if (i == 1) pre[sorted[i].second] = sorted[n].second;
			else pre[sorted[i].second] = sorted[i - 1].second;
			
			if (i == n) nxt[sorted[i].second] = sorted[1].second;
			else nxt[sorted[i].second] = sorted[i + 1].second;
			
//			assert(meetTime(i, nxt[i]) == meetTime(nxt[i], i));
			
			st.insert(mkpair(meetTime(sorted[i].second, nxt[sorted[i].second]), mkpair(sorted[i].second, nxt[sorted[i].second])));
		}
		
		Frac ans;
		
//		std::cerr << "hhh" << std::endl;
		
		while (1) {
			auto it = st.begin();
			
//			std::cerr << d[it->second.first] << " " << d[it->second.second] << std::endl;
			
			if (it->second.first == it->second.second) break;
			ans = it->first;
			int x = std::min(it->second.first, it->second.second);
//			st.erase(it);
			st.erase(st.find(mkpair(meetTime(pre[x], x), mkpair(pre[x], x))));
			st.erase(st.find(mkpair(meetTime(x, nxt[x]), mkpair(x, nxt[x]))));
			
			st.insert(mkpair(meetTime(pre[x], nxt[x]), mkpair(pre[x], nxt[x])));
			nxt[pre[x]] = nxt[x];
			pre[nxt[x]] = pre[x];
		}
		
		ll gcd = std::__gcd(ans.u, ans.v);
		ans.u /= gcd;
		ans.v /= gcd;
		
		printf("%lld/%lld\n", ans.u, ans.v);
	}
	
	return 0;
}

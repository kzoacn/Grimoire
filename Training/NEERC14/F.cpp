#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1111;
int trans[505];
bitset<MAXN> bs[MAXN], now;
int n, q, k, m, cnt[MAXN], a[MAXN], u[MAXN];

int scanBi(int id) {
	static char s[MAXN];
	
	scanf("%s", s);
	int len = strlen(s), res = 0;
	for (int i = 0; i < len; ++i) {
		int tmp = trans[(int)s[i]];
		for (int j = 0; j < 4; ++j) {
			bs[id][res++] = tmp & 1;
			tmp >>= 1;
		}
	}
	
	return res;
}

int main() {
	freopen("filter.in", "r", stdin);
	freopen("filter.out", "w", stdout);
	
	for (int i = '0'; i <= '9'; ++i)
		trans[i] = i - '0';
	for (int i = 'a'; i <= 'f'; ++i)
		trans[i] = i - 'a' + 10;
	for (int i = 'A'; i <= 'F'; ++i)
		trans[i] = i - 'A' + 10;
	
	cin >> m >> k;
	for (int i = 0; i < k; ++i) {
		scanf("%d", &a[i]);
	}
	cin >> n;
	for (int i = 0; i < n; ++i) {
		scanBi(i);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		int u;
		scanf("%d", &u);
		now.reset();
		for (int j = 0; j < k; ++j) {
			now[1LL * u * a[j] % m] = 1;
		}
		for (int j = 0; j < n; ++j) {
			if ((now & bs[j]) == now) {
				++cnt[j];
			}
		}
	}
	
	vector<int> ans;
	for (int i = 0; i < n; ++i) {
		if (cnt[i]) {
			ans.push_back(i);
		}
	}
	cout << (int)ans.size();
	for (auto x : ans) {
		printf(" %d", x);
	}
	cout << endl;
}

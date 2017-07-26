#include <bits/stdc++.h>
#define hash my_hash
#define less my_less
using namespace std;

typedef long long LL;

const int SEED = 233;
const int MOD = 1e9 + 9;
const int MAXN = 524288;
set<int> S;
vector<int> event[MAXN];
vector<pair<int, int> > v[MAXN];
int hash[MAXN], pw[MAXN], ans[MAXN], Q, n;
char str[MAXN];

inline int get_hash(int l, int r) {
assert(l > 0);
	int ret = (hash[r] - 1LL * hash[l - 1] * pw[r - l + 1]) % MOD;
	return ret < 0 ? ret + MOD : ret;
}

inline int less(int l1, int l2) {
	int left = 0, right = min(n - l1 + 1, n - l2 + 1);
	while (left < right) {
		int mid = left + right + 1 >> 1;
		if (get_hash(l1, l1 + mid - 1) == get_hash(l2, l2 + mid - 1)) {
			left = mid;
		} else {
			right = mid - 1;
		}
	}
	if (l1 + left <= n && l2 + left <= n && str[l2 + left] > str[l1 + left]) {
		return left;
	}
	return -1;
}

inline void print(set<int> &S) {
	printf("set:");
	for (auto u : S) {
		cout << " " << u;
	}
	cout << endl;
}

int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) {
		pw[i] = 1LL * pw[i - 1] * SEED % MOD;
		hash[i] = (1LL * hash[i - 1] * SEED + str[i]) % MOD;
	}
	
	cin >> Q;
	for (int i = 1; i <= Q; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		v[r].push_back(make_pair(l, i));
	}
	set<int>::iterator it;
	for (int i = 1; i <= n; ++i) {
cout << i - 1 << endl;
print(S);
		while (S.size()) {
			it = S.end();
			//cerr << "asdf" << endl;
			--it;
			//cerr << "asdf" << endl;
			int len = less(*it, i);
//cerr << *it << " " << i << " " << len << endl;
			if (len == -1) {
				break;
			}
			if (len == 0) {
				S.erase(it);
			} else {
//cout << "put event: ( " << *it << ", " << i << " )" << i + len << endl;
				event[i + len].push_back(i);
				break;
			}
		}
cout << i << endl;
print(S);
cout << i << endl;
		S.insert(i);
		for (auto l : event[i]) {
//cout << "bruteforce: " << l << endl;
//print(S);
			it = S.lower_bound(l);
			if (it == S.end() || it == S.begin()) {
				continue;
			}
			while (it != S.end()) {
//cout << "iterator: " << *it << endl;
				if (less(*it, l) + l <= i) {
					it = S.erase(it);
					if (it != S.begin()) {
						--it;
					} else {
						break;
					}
				} else {
					break;
				}
			}
			int len = less(*it, l);
			if (len == -1) {
				continue;
			}
//cout << "put event: ( " << *it << ", " << i << " )" << i + len << endl;
			event[l + len].push_back(l);
		}
		
//cout << i << endl;
//print(S);
//puts("");
//cout << i << endl;
	//	if (n > 100) {
	//		continue;
	//	}
		for (auto now : v[i]) {
			it = S.lower_bound(now.first);
			//assert(it != S.end());
			ans[now.second] = *it;
		}
	}
	
	for (int i = 1; i <= Q; ++i) {
		printf("%d\n", ans[i]);
	}
}

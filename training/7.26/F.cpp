#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int INF = 1e9;
const int SEED = 233;
//const int SEED = 100;
const int MOD = 1e9 + 9;
char str[MAXN], s1[MAXN], s2[MAXN];
int testcase, n, h[MAXN], pw[MAXN];

inline pair<string, int> sol(char *s) {
	int n = strlen(s);
/*cout << n << endl;
for (int i = 0; i < n; ++i) {
	cout << (int)s[i] << " ";
}
cout << endl;
cout << endl;
cout << endl;
	*/
	int i = 0, j = 1, k = 0, p;
	while (i < n && j < n && k < n) {
		int t = s[(i + k) % n] - s[(j + k) % n];
		if (!t) {
			++k;
		} else {
			if (t < 0) {
				j += k + 1;
				k = 0;
			} else {
				i += k + 1;
				k = 0;
			}
		}
		if (i == j) {
			j++;
		}
	}
	p = min(i, j);
	string S; S.clear();
	for (int i = p; i < p + n; ++i) {
		S.push_back(s[i % n]);
	}
//	cout << S << endl; exit(0);
	return make_pair(S, p);
}

inline int get_hash_(string str) {
	int ret = 0;
	for (int i = 0; i < (int)str.size(); ++i) {
		ret = (1LL * ret * SEED + (int)str[i]) % MOD;
	}
	return ret;
}

inline int get_hash(int l, int r) {
	int ret = (h[r] - 1LL * h[l - 1] * pw[r - l + 1]) % MOD;
	return ret < 0 ? ret + MOD : ret;
}

int main() {
	pw[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		pw[i] = 1LL * pw[i - 1] * SEED % MOD;
	}
	scanf("%d", &testcase);
	for (; testcase; --testcase) {
		scanf("%d", &n);
		scanf(" %s", str);
		s1[n] = s2[n] = 0;
		for (int i = 0; i < n; ++i) {
			s1[i] = 127 - str[i];
			s2[i] = 127 - str[n - 1 - i];
			//cout << "node: " << i << " " << (int)s1[i] << " " << (int)s2[i] << endl;
		}
/*for (int i = 0; i < n; ++i) {
	cout << (int)s1[i] << " ";
}
cout << endl;
cout << endl;*/
		pair<string, int> ans1 = sol(s1), ans2 = sol(s2);
		int target = ans1 <= ans2 ? get_hash_(ans1.first) : get_hash_(ans2.first);
/*for (int i = 0; i < n; ++i) {
	cout << (int)ans1.first[i] << " ";
}
cout << endl;
cout << target << endl;*/
		pair<int, int> ans = make_pair(INF, 0);
		s1[0] = 0;
		for (int i = 1; i <= n; ++i) {
			s1[i + n] = s1[i] = 127 - str[i - 1];
		}
		h[0] = 0;
		for (int i = 1; i <= n + n; ++i) {
			h[i] = (1LL * h[i - 1] * SEED + s1[i]) % MOD;
		}
		for (int i = 1; i <= n; ++i) {
		//cout << get_hash(i, i + n - 1) << endl;
			if (get_hash(i, i + n - 1) == target) {
				ans = min(ans, make_pair(i, 0));
			}
		}
		s1[0] = 0;
		for (int i = 1; i <= n; ++i) {
			s1[i + n] = s1[i] = 127 - str[n - i];
		}
		h[0] = 0;
		for (int i = 1; i <= n + n; ++i) {
			h[i] = (1LL * h[i - 1] * SEED + s1[i]) % MOD;
		}
		for (int i = 1; i <= n; ++i) {
			if (get_hash(i, i + n - 1) == target) {
				ans = min(ans, make_pair(n - i + 1, 1));
			}
		}
		printf("%d %d\n", ans.first, ans.second);
	}
}

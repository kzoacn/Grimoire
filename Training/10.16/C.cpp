#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef long long ll;

int n, a[5];

int cnct[1005], tot = 0;

std::vector<int> real[5];

__advance ll DFS(int);
__advance ll DFS2(int, int, int, int);

__advance ll DFS(int now) {
	if (now == n) return 0;
	
	return DFS2(now, 0, a[now], 1 << now);
}

__advance ll DFS2(int dep, int now, int left, int S) {
	if (now == dep || !left) return left + DFS(dep + 1);
	ll res = DFS2(dep, now + 1, left, S);
	
	if ((int)real[now].size() < a[now]) {
		cnct[++tot] = (1 << now) | (1 << dep);
		real[now].push_back(tot);
		real[dep].push_back(tot);
		res = std::min(res, DFS2(dep, now + 1, left - 1, S | (1 << now)));
		real[now].pop_back();
		real[dep].pop_back();
		--tot;
		return res;
	}
	
	for (register int i: real[now]) {
		if (S & cnct[i]) continue;
		cnct[i] |= (1 << dep);
		real[dep].push_back(i);
		res = std::min(res, DFS2(dep, now + 1, left - 1, S | cnct[i]));
		cnct[i] ^= (1 << dep);
		real[dep].pop_back();
	}
	
	return res;
}

int main() {
	std::cin >> n;
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	
	std::sort(a, a + n, std::greater<int>());
	
	printf("%lld\n", DFS(0));
	
	return 0;
}

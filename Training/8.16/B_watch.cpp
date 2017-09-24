#include <bits/stdc++.h>

int prime[50005];
bool notprime[50005];

void get_prime() {
	const int lim = 46337;
	
	for (int i = 2; i <= lim; ++i) {
		if (!notprime[i]) prime[++*prime] = i;
		for (int j = 1; j <= *prime && i * prime[j] <= lim; ++j) {
			notprime[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}
/*
typedef std::pair<int, int> pii;
#define mkpair std::make_pair

std::set<pii> st;
*/
int calc(int Mod) {
//	st.clear();
	int x, y = 2 % Mod, z = 10 % Mod;
	for (int i = 2; ; ++i) {
//		if (st.count(mkpair(y, z))) return i;
//		st.insert(mkpair(y, z));
		if (i > 2 && y == 2 % Mod && z == 10 % Mod) return i;
		x = y, y = z;
		z = ((y * 10 - x) % Mod + Mod) % Mod;
	}
	return -1;
}

int main() {
	get_prime();
	
	for (int i = 1; i <= *prime; ++i) {
//		fprintf(stderr, "%d is calculating...\n", prime[i]);
		printf("%d: %d\n", prime[i], calc(prime[i]));
//		calc(prime[i]);
	}
	
	return 0;
}

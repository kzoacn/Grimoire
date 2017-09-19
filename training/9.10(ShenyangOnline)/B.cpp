#include <bits/stdc++.h>
using namespace std;

long long m, k;

int main() {
	while (scanf("%lld%lld", &m, &k) == 2) {
		printf("%lld\n", k * (m - k + 1));
	}
}

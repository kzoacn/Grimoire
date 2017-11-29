#include <bits/stdc++.h>

typedef std::pair<int, int> PII;
#define mkpair std::make_pair

const int MAXN = 100 + 5;

int m, n, x;
int c[MAXN];

int comp, incomp;

std::multiset<PII> st;

int main() {
	while (~scanf("%d%d%d", &m, &n, &x)) {
		st.clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", c + i);
			st.insert(mkpair(0, c[i]));
		}
		
		comp = m, incomp = 0;
		while (!st.empty()) {
			PII tmp = *st.begin(); st.erase(st.begin());
			if (tmp.first > x) break;
			if (tmp.first != 0) --incomp;
			if (tmp.first >= x) continue;
			if (!comp) continue;
			--comp;
			++incomp;
			st.insert(mkpair(tmp.first + tmp.second, tmp.second));
		}
		printf("%d %d\n", comp, incomp);
	}
	
	return 0;
}

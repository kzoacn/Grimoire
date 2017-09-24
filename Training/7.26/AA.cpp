#include <bits/stdc++.h>
using namespace std;

const int MAXN = 233333;
int n, m, Q, cs, val[MAXN], peo[MAXN];
char name[MAXN][233];

struct Door {
	int t, p;
} door[MAXN];

inline bool cmp_Door(const Door &p, const Door &q) {
	return p.t < q.t;
}

set<pair<int, int> > S;

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%d%d%d", &n, &m, &Q);
		for (int i = 1; i <= n; ++i) {
			scanf(" %s%d", name[i], &val[i]);
		}
		int cnt = 0, j = 1;
		S.clear();
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &door[i].t, &door[i].p);
		}
		sort(door + 1, door + m + 1, cmp_Door);
		for (int i = 1; i <= m; ++i) {
			while (j <= door[i].t) {
				S.insert(make_pair(-val[j], j));
				++j;
			}
			for (int k = 0; k < door[i].p && S.size(); ++k) {
				peo[++cnt] = S.begin() -> second;
				S.erase(S.begin());
			}
		}
		while (j <= n) {
			S.insert(make_pair(-val[j], j));
			++j;
		}
		for (; S.size();) {
			peo[++cnt] = S.begin() -> second;
			S.erase(S.begin());
		}
		for (int i = 1; i <= Q; ++i) {
			int q;
			scanf("%d", &q);
			if (q > cnt) {
				if (i == Q) {
					cout << endl;
				} else {
					//printf(" ");
				}
				continue;
			}
			printf("%s%s", name[peo[q]], i == Q ? "\n" : " ");
		}
	}
}

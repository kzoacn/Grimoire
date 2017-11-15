#include <bits/stdc++.h>

using namespace std;

map<multiset<int>, set<int> > st;
multiset<int> tmp;

const int n = 10, Lim = 40;

int A[1005];

void check() {
	tmp.clear();
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			tmp.insert(A[i] + A[j]);
	if (st.count(tmp)) {
		for (int i: st[tmp])
			cout << i << " ";
		cout << endl;
		for (int i = 0; i < n; ++i)
			cout << A[i] << " ";
		cout << endl;
		exit(0);
	}
	for (int i = 0; i < n; ++i)
		st[tmp].insert(A[i]);
}

void DFS(int now, int fir) {
	if (now == n) {
		check(); return;
	}
	for (int i = fir; i <= Lim; ++i) {
		if (now == 0) {
			cout << i << endl;
		}
		A[now] = i;
		DFS(now + 1, i + 1);
	}
}

int main() {
	DFS(0, 1);
	
	return 0;
}

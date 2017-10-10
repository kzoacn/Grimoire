#include <bits/stdc++.h>

typedef long long ll;

struct Node {
	ll val; int id, x, y;
	
	Node() {}
	Node(ll val, int id, int x, int y): val(val), id(id), x(x), y(y) {}
	
	bool operator < (const Node &rhs) const {
		if (val != rhs.val) return val < rhs.val;
		if (id != rhs.id) return id < rhs.id;
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
} ZERO(0, 0, 0, 0);

std::set<Node> st;

int n;

ll wp[10005][4][4], mx[7];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		st.clear();
		memset(mx, 0, sizeof mx);
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			for (int x = 0; x < 4; ++x)
				for (int y = 0; y < 4; ++y) {
					scanf("%lld", &wp[i][x][y]);
					if (x == y) continue;
					st.insert(Node(wp[i][x][y], i, x, y));
				}
		
		ll ans = 0;
		for (int day = 1; day <= 3; ++day) {
			static Node tmp;
			
			tmp = *--st.end();
			ans += tmp.val;
			mx[day + 3] = std::max(mx[day + 3], wp[tmp.id][tmp.y][tmp.x]);
			int i, j;
			for (i = 0; i < 4; ++i) if (i != tmp.x && i != tmp.y) break;
			for (j = 0; j < 4; ++j) if (j != tmp.x && j != tmp.y && j != i) break;
			
			mx[day + 3] = std::max(mx[day + 3], std::max(wp[tmp.id][i][j], wp[tmp.id][j][i]));
			
			st.erase(--st.end());
			st.erase(st.find(Node(wp[tmp.id][tmp.y][tmp.x], tmp.id, tmp.y, tmp.x)));
			st.erase(st.find(Node(wp[tmp.id][i][j], tmp.id, i, j)));
			st.erase(st.find(Node(wp[tmp.id][j][i], tmp.id, j, i)));
		}
		
		std::sort(mx + 4, mx + 7);
		
		for (int day = 4; day <= 6; ++day) {
			static Node tmp;
			
			if (st.empty()) {
				ans += mx[day]; continue;
			}
			tmp = *--st.end();
			ans += std::max(tmp.val, mx[day]);
			
			int i, j;
			for (i = 0; i < 4; ++i) if (i != tmp.x && i != tmp.y) break;
			for (j = 0; j < 4; ++j) if (j != tmp.x && j != tmp.y && j != i) break;
			
			st.erase(--st.end());
			st.erase(st.find(Node(wp[tmp.id][tmp.y][tmp.x], tmp.id, tmp.y, tmp.x)));
			st.erase(st.find(Node(wp[tmp.id][i][j], tmp.id, i, j)));
			st.erase(st.find(Node(wp[tmp.id][j][i], tmp.id, j, i)));
		}
		
		printf("Case #%d: %lld\n", kase, ans);
	}
	
	return 0;
}

#include <bits/stdc++.h>

typedef long long LL;
typedef std::pair<int, int> PII;
#define mkpair std::make_pair

const int MAXN = 500 + 5;

const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int label[4] = {-1, 1, 1, -1};

int n, m;

LL r[MAXN][MAXN], c[MAXN][MAXN];

LL edge[MAXN][MAXN][4];

bool vis[MAXN][MAXN];
int X[MAXN], Y[MAXN];

struct Num { // A * x + B
	LL A, B;
	
	Num() {}
	Num(LL a, LL b): A(a), B(b) {}
	Num(LL x): A(0), B(x) {}
	
	Num operator + (const Num &rhs) const {
		return Num(A + rhs.A, B + rhs.B);
	}
	
	Num operator - (const Num &rhs) const {
		return Num(A - rhs.A, B - rhs.B);
	}
	
	Num operator * (LL x) const {
		return Num(A * x, B * x);
	}
	
	bool operator == (const Num &rhs) const {
		return A == rhs.A && B == rhs.B;
	}
	
	void print(char endChar) {
		printf("%lldx + %lld%c", A, B, endChar);
	}
} ans[MAXN][MAXN];

bool lim = 0;
LL limx;

bool Equal(const Num a, const Num b) {
	LL A = a.A, B = a.B, C = b.A, D = b.B;
	
	if (a == b) return 1;
	if (!lim) {
		if (A == C && B != D) return 0;
		if ((D - B) % (A - C)) return 0;
		lim = 1;
		limx = (D - B) / (A - C);
		return 1;
	}
	return a.A * limx + a.B == b.A * limx + b.B;
}

bool BFS() {
	static std::queue<PII> que;
	static PII now;
	
	vis[1][1] = 1;
	ans[1][1] = Num(1, 0);
	que.push(mkpair(1, 1));
	
	while (!que.empty()) {
		now = que.front(); que.pop();
		int x = now.first, y = now.second;
		for (int t = 0; t < 4; ++t) {
			int xx = X[x + drct[t][0]], yy = Y[y + drct[t][1]];
			if (vis[xx][yy]) {
				if (!Equal((ans[x][y] - ans[xx][yy]) * label[t], Num(edge[x][y][t]))) return 0;
				continue;
			}
			vis[xx][yy] = 1;
			ans[xx][yy] = (ans[x][y] * label[t] - Num(edge[x][y][t])) * label[t];
			que.push(mkpair(xx, yy));
		}
	}
	return 1;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%lld%lld", &r[i][j], &c[i][j]);
	
	for (int i = 1; i <= n; ++i)
		X[i] = i;
	X[0] = n; X[n + 1] = 1;
	
	for (int i = 1; i <= m; ++i)
		Y[i] = i;
	Y[0] = m; Y[m + 1] = 1;
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			edge[X[i]][Y[j]][2] = edge[X[i - 1]][Y[j]][0] = r[i][j];
			edge[X[i]][Y[j - 1]][1] = edge[X[i]][Y[j]][3] = c[i][j];
		}
	
	/*for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			fprintf(stderr, "(%d, %d):", i, j);
			for (int t = 0; t < 4; ++t)
				std::cerr << " " << edge[i][j][t];
			std::cerr << std::endl;
		}*/
	
	puts(BFS() ? "Yes" : "No");
	
	/*for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			ans[i][j].print(" \n"[j == m]);
	printf("lim = %d\n", lim);
	printf("x = %lld\n", limx);*/
	
	return 0;
}
/*
(1, 1): 1 0 -1 -2
(1, 2): 0 2 0 0
(1, 3): 3 -2 -3 2
(2, 1): -1 1 1 0
(2, 2): 0 -1 0 1
(2, 3): -3 0 3 -1
No
1x + 0 1x + 0 0x + 0
1x + 1 0x + 0 0x + 0
lim = 0
x = 0
*/

#include <bits/stdc++.h>

int X, Y, Z;
int n;
int cube[55][55][55];

struct vec {
	int x, y, z;
	
	vec() {}
	vec(int x, int y, int z): x(x), y(y), z(z) {}
	
	void print(char endChar) {
		printf("%d %d %d%c", x, y, z, endChar);
	}
};

struct Ans {
	vec a, b;
	
	Ans() {}
	Ans(vec a, vec b): a(a), b(b) {}
	
	void print() {
		a.print(' '); b.print('\n');
	}
}; std::vector<Ans> ans;

int main() {
	srand(time(0));
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		ans.clear();
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				for (int k = 1; k <= n; ++k)
					scanf("%1d", cube[i][j] + k);
		
		//X = Y = Z = (n + 1) >> 1;
		X = rand() % n + 1;
		Y = rand() % n + 1;
		Z = rand() % n + 1;
		
		for (int i = 1; i <= 1000; ++i) {
			int x = rand() % n + 1,
				y = rand() % n + 1,
				z = rand() % n + 1;
			if (cube[x][y][z]) {
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				for (int k = Z; k; --k) if (cube[i][j][k]) {
					cube[i][j][k] = 0;
					int t = k;
					for (; t + 1 <= Z && !cube[i][j][t + 1]; ++t) {
						ans.push_back(Ans(vec(i, j, t), vec(i, j, t + 1)));
					}
					cube[i][j][t] = 1;
				}
				for (int k = Z; k <= n; ++k) if (cube[i][j][k]) {
					cube[i][j][k] = 0;
					int t = k;
					for (; t - 1 >= Z && !cube[i][j][t - 1]; --t) {
						ans.push_back(Ans(vec(i, j, t), vec(i, j, t - 1)));
					}
					cube[i][j][t] = 1;
				}
			}
		}
		
		for (int i = 1; i <= n; ++i) {
			for (int k = 1; k <= n; ++k) {
				for (int j = Y; j; --j) if (cube[i][j][k]) {
					cube[i][j][k] = 0;
					int t = j;
					for (; t + 1 <= Y && !cube[i][t + 1][k]; ++t) {
						ans.push_back(Ans(vec(i, t, k), vec(i, t + 1, k)));
					}
					cube[i][t][k] = 1;
				}
				for (int j = Y; j <= n; ++j) if (cube[i][j][k]) {
					cube[i][j][k] = 0;
					int t = j;
					for (; t - 1 >= Y && !cube[i][t - 1][k]; --t) {
						ans.push_back(Ans(vec(i, t, k), vec(i, t - 1, k)));
					}
					cube[i][t][k] = 1;
				}
			}
		}
		
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				for (int i = X; i; --i) if (cube[i][j][k]) {
					cube[i][j][k] = 0;
					int t = i;
					for (; t + 1 <= X && !cube[t + 1][j][k]; ++t) {
						ans.push_back(Ans(vec(t, j, k), vec(t + 1, j, k)));
					}
					cube[t][j][k] = 1;
				}
				for (int i = X; i <= n; ++i) if (cube[i][j][k]) {
					cube[i][j][k] = 0;
					int t = i;
					for (; t - 1 >= X && !cube[t - 1][j][k]; --t) {
						ans.push_back(Ans(vec(t, j, k), vec(t - 1, j, k)));
					}
					cube[t][j][k] = 1;
				}
			}
		}
		
		if (ans.size() > 200000) {
			printf("Case #%d: -1\n", kase);
			continue;
		}
		
		printf("Case #%d: %d\n", kase, (int)ans.size());
		for (auto i: ans) i.print();
	}
	
	return 0;
}

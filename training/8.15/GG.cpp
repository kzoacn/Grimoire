#include <bits/stdc++.h>

int vis[55][55][55][55], kase;
double dp[55][55][55][55];

int def[3];
const double eps=1e-9;
double DP(int atk1, int hp1, int atk2, int hp2) {
	if (hp1 <= 0) return hp2 <= 0 ? 0 : -100;
	if (hp2 <= 0) return 100;
	
	if (vis[atk1][hp1][atk2][hp2] == kase) return dp[atk1][hp1][atk2][hp2];
	vis[atk1][hp1][atk2][hp2] = kase;
	double &res = dp[atk1][hp1][atk2][hp2];
	
	double tmp[2][2];
	for (int i = 0; i < 2; ++i) {
		if (i) std::swap(atk1, hp1);
		for (int j = 0; j < 2; ++j) {
			if (j) std::swap(atk2, hp2);
			tmp[i][j] = DP(atk1, hp1 - (atk2 + def[1] - 1) / def[1], atk2, hp2 - (atk1 + def[2] - 1) / def[2]);
			if (j) std::swap(atk2, hp2);
		}
		if (i) std::swap(atk1, hp1);
	}
	
	for (int i = 0; i < 2; ++i) {
		if (tmp[i][0] -eps> tmp[i ^ 1][0] && tmp[i][1] -eps> tmp[i ^ 1][1]) return res = std::min(tmp[i][0], tmp[i][1]);
		if (tmp[0][i] +eps< tmp[0][i ^ 1] && tmp[1][i] +eps< tmp[1][i ^ 1]) return res = std::max(tmp[0][i], tmp[1][i]);
	}
	//cerr<<tmp[0][0]<<" "<<tmp[0][1]<<endl;
//	cerr<<tmp[1][0]<<" "<<tmp[1][1]<<endl;
//	while(1); 
	
	return res = (tmp[0][0] + tmp[0][1] + tmp[1][0] + tmp[1][1]) * 0.25;
}

int main() {
	int atk[3], hp[3];
	
	int caseCnt; scanf("%d", &caseCnt);
	for (kase = 1; kase <= caseCnt; ++kase) {
		for (int i = 1; i <= 2; ++i) scanf("%d%d%d", hp + i, atk + i, def + i);
		
		printf("Case #%d: %.8f\n", kase, DP(atk[1], hp[1], atk[2], hp[2]));
	}
	
	return 0;
}

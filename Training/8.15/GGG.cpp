#include <bits/stdc++.h>
using namespace std;
int vis[55][55][55][55], kase;
double dp[55][55][55][55];
const double INF = 1e9;
const double eps = 1e-9;
int def[3];

double calc(double tmp[2][2], double p1, double p2) {
	return tmp[0][0] * p1 * p2 + tmp[0][1] * p1 * (1 - p2) + tmp[1][0] * (1 - p1) * p2 + tmp[1][1] * (1 - p1) * (1 - p2);
}
double calcP2(double tmp[2][2], double p1) {
	double p2=0;
	
	return ;
}


void three(double tmp[2][2],double &p1,double &p2){
	double l=0,r=1;
	int TAT=50;
	while(TAT--){
		double mid1=l+(r-l)*0.45;
		double mid2=r-(r-l)*0.45;
		double p21=calcP2(tmp,mid1);
		double p22=calcP2(tmp,mid1);
		if(calc(tmp,mid1,p21)>calc(tmp,mid2,p22))
			r=mid2;
		else
			l=mid1;
	}
	p1=l;
	p2=calcP2(tmp,p1);
}

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
	
	return res;
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

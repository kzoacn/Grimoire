#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int N = 60;

int Case, n;
long double f[N][N * 2][N][4][2];
long double b[2][3], d[2][3];

int used[N][N * 2][N][4][2];
int U_cnt = 0;

long double dcmp(long double x){
	if (x > 1.0) return 1.0;
	if (x < 0.0) return 0.0;
	return x;
}

long double dp(int sa, int sbd, int sc, int cnt, int who){
	long double Cur = 0.0;
	long double Nxt;
	
	if(used[sa][sbd][sc][cnt][who] == U_cnt) 
		return f[sa][sbd][sc][cnt][who];
	
	used[sa][sbd][sc][cnt][who] = U_cnt;
	
	int tot = sa + sbd + sc + 1;
	if (cnt < 3){
		if (sa >= 2){
			Nxt = dp(sa - 1, sbd + 1, sc, cnt + 1, 1 - who);
			Cur = max(Cur, (1 - Nxt) * (dcmp(b[who][0] - d[who][0] * tot)));
		}
		if (sa >= 2){
			Nxt = dp(sa - 1, sbd, sc + 1, cnt + 1, 1 - who);
			Cur = max(Cur, (1 - Nxt) * (dcmp(b[who][1] - d[who][1] * tot)));
		}
		if (sc >= 1){
			Nxt = dp(sa, sbd + 1, sc - 1, cnt + 1, 1 - who);
			Cur = max(Cur, (1 - Nxt) * (dcmp(b[who][2] - d[who][2] * tot)));
		}
	
	} else {
		if (sa >= 0){
			Nxt = dp(sa + 1 - 1, sbd + 1, sc, 1, 1 - who);
			Cur = max(Cur, (1 - Nxt) * (dcmp(b[who][0] - d[who][0] * tot)));
		}
		if (sa >= 0){
			Nxt = dp(sa + 1 - 1, sbd, sc + 1, 1, 1 - who);
			Cur = max(Cur, (1 - Nxt) * (dcmp(b[who][1] - d[who][1] * tot)));
		}
		if (sc >= 1){
			Nxt = dp(sa + 1, sbd + 1, sc - 1, 1, 1 - who);
			Cur = max(Cur, (1 - Nxt) * (dcmp(b[who][2] - d[who][2] * tot)));
		}
	}
	
	f[sa][sbd][sc][cnt][who] = Cur;
	return Cur;
}

double fix(long double x) {
	return (double)x;
}

int main(){

	scanf("%d", &Case);
	while (Case){
		Case--;
		scanf("%d", &n);
		cin >> b[0][0] >> d[0][0] >> b[0][1] >> d[0][1] >> b[0][2] >> d[0][2];
		cin >> b[1][0] >> d[1][0] >> b[1][1] >> d[1][1] >> b[1][2] >> d[1][2];
		U_cnt++;
		
		printf("%.4f\n", (double)fix((dp(n - 1, 0, 0, 3, 0))));
		
	}

	return 0;
}



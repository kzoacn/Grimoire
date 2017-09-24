#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 105;
const int S = 260;
const int INF = 99999999;

int f[2][N][S][10];
int h[N];
int n, m, Case;
int Have;
int Cnt[S];

int main(){
	
	Cnt[0] = 0;
	for (int i = 1; i < S; i++)
		Cnt[i] = Cnt[i / 2] + (i & 1);
	
	Case = 0;
	while (1){
		scanf("%d%d", &n, &m);
		if (!n && !m) break;
		
		Have = 0;
		for (int i = 1; i <= n; i++){
			scanf("%d", &h[i]);
			h[i] -= 25;
			Have |= (1 << h[i]);
		}
		
		for (int i = 0; i <= 1; i++)
			for (int j = 0; j <= m; j++)
				for (int k = 0; k <= 255; k++)
					for (int l = 0; l <= 8; l++)
						f[i][j][k][l] = INF;
		f[0][0][0][8] = 0;
		int Now = 0,  Nxt = 1;
		for (int i = 1; i <= n; i++){
			
			for (int j = 0; j <= m; j ++)
				for (int k = 0; k <= 255; k++)
					for (int l = 0; l <= 8; l++)
						f[Nxt][j][k][l] = INF;
			
			for (int j = 0; j <= i - 1 && j <= m; j++)
				for (int k = 0; k <= 255; k++)
					for (int l = 0; l <= 8; l++)
					if (f[Now][j][k][l] != INF){
						if (j < m) f[Nxt][j + 1][k][l] = min(f[Nxt][j + 1][k][l], f[Now][j][k][l]);
						if (h[i] == l) f[Nxt][j][k][l] = min(f[Nxt][j][k][l], f[Now][j][k][l]);
						else f[Nxt][j][k | (1 << h[i])][h[i]] = min(f[Nxt][j][k | (1 << h[i])][h[i]], f[Now][j][k][l] + 1);
					}
			
			Now = Nxt; Nxt= 1 - Now;
		}
		
		int Ans = INF;
		for (int k = 0; k <= 255; k++)
			for (int l = 0; l <= 8; l++)
				if (f[Now][m][k][l] != INF){
					int Cur = k ^ Have;
					Ans = min(Ans, f[Now][m][k][l] + Cnt[Cur]);
				}
				
		Case++;
		printf("Case %d: %d\n", Case, Ans);
		printf("\n");
		
	}
	
	return 0;
}

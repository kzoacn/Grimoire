#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 105;
const int M = 55;

int a[M][M];
int f[N][M];
int b[N];
int Le, Ri;
int n, m;

int main(){
	
	int Case;
	scanf("%d", &Case);
	while (Case -- ){
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &a[i][j]);
		
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		
		if (b[1] == -1) Le = 1, Ri = m;
		else Le = Ri = b[1];
		
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				f[i][j] = -999999999;
		
		for (int i = Le; i <= Ri; i++)
			f[1][i] = 0;
		 
		for (int i = 2; i <= n; i++){
			
			if (b[i] == -1) Le = 1, Ri = m;
			else Le = Ri = b[i];
			
			int Le0, Ri0;
			
			if (b[i - 1] == -1) Le0 = 1, Ri0 = m;
			else Le0 = Ri0 = b[i - 1];
			
			for (int j = Le; j <= Ri; j++){
				for (int k = Le0; k <= Ri0; k++){
					f[i][j] = max(f[i][j], f[i - 1][k] + a[k][j]);
				}
			}
		}
		
		if (b[n] == -1) Le = 1, Ri = m;
		else Le = Ri = b[n];
		
		int Ans = 0;
		for (int j = Le; j <= Ri; j++)
			if (f[n][j] > Ans) Ans = f[n][j];
		
		printf("%d\n", Ans);
	}	
	
}

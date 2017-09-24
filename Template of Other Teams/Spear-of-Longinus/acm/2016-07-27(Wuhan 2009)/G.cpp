#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int V1 = 505;
const int V2 = 55;
const int N = 305;

int v1,v2,n;
int p[N], h[N];
int must[N];

int f[2][V1][V2][2];

int main(){

	int Case = 0;
	while (1){
		scanf("%d%d%d", &v1, &v2, &n);
		
		if (!v1 && !v2 && !n) break;
		
		int pos = 1;
		for (int i = 1; i <= n; i++){
			scanf("%d%d%d", &p[i], &h[i], &must[i]);
			if (must[i]) pos = i;
		}
		
		for (int j = 0; j <= v1; j++)
			for (int k = 0; k <= v2; k++)
				for (int l = 0; l < 2; l++)
					f[0][j][k][l] = -99999999;
		f[0][0][0][1] = 0;
		
		int Now = 1, Lst = 0;
		int Ans = -1;
		
		for (int i = 1; i <= n; i ++){
			
			for (int j = 0; j <= v1; j++)
				for (int k = 0; k <= v2; k++)
					for (int l = 0; l < 2; l++)
						f[Now][j][k][l] = -99999999;
			
			for (int j = 0; j <= v1; j++)
				for (int k = 0; k <= v2; k++)
					for (int l = 0; l < 2; l++){
						if (j >= p[i]) f[Now][j][k][l] = max(f[Now][j][k][l], f[Lst][j - p[i]][k][l] + h[i]);
						if (k >= p[i]) f[Now][j][k][l] = max(f[Now][j][k][l], f[Lst][j][k - p[i]][l] + h[i]);
						if (l == 0) f[Now][j][k][l] = max(f[Now][j][k][l], f[Lst][j][k][1] + h[i]);
						
						if (!must[i]){
							f[Now][j][k][l] = max(f[Now][j][k][l], f[Lst][j][k][l]);
						}
						
						if (i >= pos) {
							//printf("f[%d][%d][%d][%d] = %d\n",i,j,k,l,f[Now][j][k][l]);	
							Ans = max(Ans, f[Now][j][k][l]);
						}
					}
			
			Now = Lst; Lst = 1 - Now;
			
		}
		++Case;
		if (Ans <= 0) Ans = -1;
		printf("Case %d: %d\n", Case, Ans);
		printf("\n");
		
	}
	return 0;
}

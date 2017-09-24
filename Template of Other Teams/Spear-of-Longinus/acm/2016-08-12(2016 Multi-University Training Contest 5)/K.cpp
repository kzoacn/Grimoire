#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int Mo = 1000000007;
const int N = 1005;

int f[N][N], sum[N][N];
int n, m;
int a[N], b[N];

int main(){
	
	while (scanf("%d%d", &n, &m) == 2){
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= m; i++)
			scanf("%d", &b[i]);
		
		for (int i = 1; i <= m; i++){
			f[0][i] = 0;
			sum[0][i] = 1;
		}
		for (int i = 1; i <= n; i++){
			f[i][0] = 0;
			sum[i][0] = 1;
		}
		
		f[0][0] = 1;
		sum[0][0] = 1;
		
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if (a[i] != b[j]) f[i][j] = 0;
				else {
					f[i][j] = sum[i - 1][j - 1];
				}
				
				sum[i][j] = ((sum[i][j - 1] + sum[i - 1][j]) % Mo - sum[i - 1][j - 1]) % Mo;
				sum[i][j] = (sum[i][j] + f[i][j]) % Mo;
			}
		}
		
		printf("%d\n", (sum[n][m] - 1 + Mo) % Mo);
		
		/*for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++)
				printf("%d ", sum[i][j]);
			printf("\n");
		}*/
	}
	
	return 0;
}

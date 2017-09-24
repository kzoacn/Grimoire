#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 30;
const int L = 1005;

int n, m, len;
double p[N];
char pattern[N], c[N];
int fail[N];
double f[L][N][2];

void build(){
	int length = (int)strlen(pattern + 1);
	fail[0] = -1;
	for (int i = 1, j; i <= length; i++){
		for (j = fail[i - 1]; j != -1 && pattern[i] != pattern[j + 1]; j = fail[j]);
		fail[i] = j + 1;
		//printf("pattern[%d] = %c\n", i, pattern[i]);
		//printf("fail[%d] = %d\n", i, j + 1);
	}
}

int main(){
	
	while (1){
		scanf("%d%d", &n, &m);
		if (!n && !m) break;
		char str[104];
		for (int i = 1; i <= n; i++){
			char space, hang;
			scanf("%s", str + 1);
			c[i] = str[1];
			scanf("%lf", &p[i]);
		}
		scanf("%s",  pattern + 1);
		len = (int)strlen(pattern + 1);
		
		//printf("%c %c %lf\n",c[1],pattern[1]);
		//printf("%lf\n",p[4]);
		
		build();
		for (int i = 0; i <= m; i++)
			for (int j = 0; j <= len; j++)
				for (int k = 0; k < 2; k++)
					f[i][j][k] = 0.0;
		f[0][0][0] = 1.0;
		
		for (int i = 0; i < m; i++){
			for (int j = 0; j <= len; j++){
				for (int k = 0; k < 2; k++){
					for (int now = 1; now <= n; now++){
						int pos;
						
						for (pos = j; pos != -1 && c[now] != pattern[pos + 1]; pos = fail[pos]);
						
						
						
						int kk = 0;
						if (pos + 1 == len) kk = 1;
						//printf("f[%d][%d][%d] = %.2lf now = %d pos = %d kk = %d\n",i ,j , k, f[i][j][k], now, pos, kk);
						f[i + 1][pos + 1][k | kk] += f[i][j][k] * p[now];
						//printf("%f\n", f[4][4][1]);
					}
				}
			}
		}
		//printf("%.2lf\n",f[1][1][0]);
		//printf("%.2lf\n",f[2][2][0]);
		//printf("%.2lf\n",f[3][3][0]);
		//printf("%f\n",f[4][4][1]);
		
		double Ans = 0.0;
		for (int i = 0; i <= len; i++)
			Ans += f[m][i][1];
		printf("%.2f", Ans * 100);
		puts("%");
	}
		
		
	return 0;
}


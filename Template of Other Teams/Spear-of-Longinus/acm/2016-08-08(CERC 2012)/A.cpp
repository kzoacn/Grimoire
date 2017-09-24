#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int N = 25;
const int S = 1048600;

int f[S];

int sum[N], cur[N];
int cnt_have, cnt_no, hav[N], no[N];
bool sur[N];

int n;
int d[N][N];

int main(){

	int Case;
	scanf("%d", &Case);
	
	int Time = 0;
	
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &d[i][j]);
		
		for (int i = 1; i <= n; i++)
			sum[i] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++){
				sum[i] -= d[i][j];
				sum[j] -= d[j][i];
			}
		
		
		++Time;	
		f[0] = Time;
		
		for (int i = 1; i <= n; i++)
			sur[i] = 0;
		
		for (int s = 0; s < (1 << n); s++){
			if (f[s] != Time) continue;
			
			
			for (int i = 1; i <= n; i++) cur[i] = sum[i];
			
			cnt_have = 0;
			cnt_no = 0;
			
			
			for (int i = 1; i <= n; i++)
				if (s & (1 << (i - 1))){
					hav[++cnt_have] = i;
				} else
					no[++cnt_no] = i;
			
			for (int i = 1; i <= cnt_have; i++)
				for (int j = 1; j <= cnt_no; j++)
					cur[no[j]] -= d[hav[i]][no[j]];
			
			
			if (cnt_have == n - 1 && cur[no[1]] >= 0) {
				
				sur[no[1]] = 1;
				continue;
				
			}
			
			for (int i = 1; i <= cnt_no; i++)
				if (cur[no[i]] < 0)
					f[s | (1 << (no[i] - 1))] = Time;
		
		}
		
		bool flag = 0;
		for (int i = 1; i <= n; i++)
			if (sur[i]) {
				if(!flag) {
					printf("%d", i);
				} else {
					printf(" %d", i);
				}
				flag = 1;
			}
		if (flag) printf("\n");
		else puts("0");
	}

	return 0;
	
}

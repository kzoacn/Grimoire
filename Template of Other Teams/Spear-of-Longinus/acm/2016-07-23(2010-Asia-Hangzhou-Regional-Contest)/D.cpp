#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 250;
const int M = 15;

const int dir[8][2] = {{-1,0},{1,0},{0,-1},{0,1},{-1,1},{1,-1},{-1,-1},{1,1}};

int n, cnt;
int a[M][M];
int q[N][2];

void Calc(int col){
	cnt = 0;
	
	for (int i = 0; i <= 14; i++){
		for (int j = 0; j <= 14; j++){
			if (a[i][j] != -1) continue;
			
			bool flag = 0;
			
			for (int k = 0; k <= 6; k += 2){
				int x = i + dir[k][0], y = j + dir[k][1];
				int sum = 1;
				while (1){
					if (x < 0 || x > 14 || y < 0 || y > 14) break;
					if (a[x][y] != col) break;
					sum++;
					x += dir[k][0];
					y += dir[k][1]; 
				}
				x = i - dir[k][0], y = j - dir[k][1];
				while (1){
					if (x < 0 || x > 14 || y < 0 || y > 14) break;
					if (a[x][y] != col) break;
					sum++;
					x -= dir[k][0];
					y -= dir[k][1]; 
				}
				if (sum >= 5){
					flag = 1;
					break;
				}
			}
			
			if (flag){
				q[++cnt][0] = i;
				q[cnt][1] = j;
			}
		}
	}
}

int main(){

	while (1){
		scanf("%d", &n);
		if (!n) break;
		
		for (int i = 0; i <= 14; i++)
			for (int j = 0; j <= 14; j++)
				a[i][j] = -1;
		
		int cnt0 = 0;
		int cnt1 = 0;
		
		for (int i = 1; i <= n; i++){
			int x, y, col;
			scanf("%d%d%d", &x, &y, &col);
			a[x][y] = col;
			if (col) cnt1++; else cnt0++;
		}
		
		bool valid = 0;
		int first;
		
		if (cnt1 == cnt0){
			valid = 1;
			first = 1;
		}
		if (cnt1 == cnt0 + 1){
			valid = 1;
			first = 0;
		}

		if (!valid){
			puts("Invalid.");
			continue;
		}
		
		int second = 1 - first;
		int third = 1 - second;
		
		Calc(first);
		
		if (cnt > 0){
			if (first)
				printf("Place black at (%d,%d) to win in 1 move.\n",q[1][0],q[1][1]);
			else
				printf("Place white at (%d,%d) to win in 1 move.\n",q[1][0],q[1][1]);
			continue;
		}
		
		Calc(second);
		if (cnt > 1){
			printf("Lose in 2 moves.\n");
			continue;
		}
		
		bool flag = 0;
		int ansx = 0, ansy = 0;
		
		for (int i = 0; i <= 14; i++){
			for (int j = 0; j <= 14; j++){
				if (a[i][j] != -1) continue;
				a[i][j] = first;
				Calc(second);
				
				if (cnt > 0){
					a[i][j] = -1;
					continue;
				}
				
				Calc(third);
				
				if (cnt > 1){
					flag = 1;
					ansx = i;
					ansy = j;
					break;
				}
				
				a[i][j] = -1;
				
			}
			if (flag) break;
		}
		
		if (flag){
			if (first)
				printf("Place black at (%d,%d) to win in 3 moves.\n",ansx,ansy);
			else
				printf("Place white at (%d,%d) to win in 3 moves.\n",ansx,ansy);
			continue;
		}
		
		printf("Cannot win in 3 moves.\n");
		
	}	
	
	return 0;
}

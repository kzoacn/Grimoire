#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 2005;

int Queen[N][N];
int Knight[N][N];
int k, n, m;

void makeQueen(){
	memset(Queen, 0, sizeof(Queen));
	for (int i = 1; i <= 1000; i++)
		for (int j = 1; j <= 1000; j++)
		if (Queen[i][j] == 0){
			for (int k = 1; k <= 1000; k++){
				Queen[i + k][j] = 1;
				Queen[i][j + k] = 1;
				Queen[i + k][j + k] = 1;
			}
		}
}

void makeKnight(){
	memset(Knight, -1, sizeof(Knight));
	
	Knight[1][1] = 0;
	for (int i = 1; i <= 1000; i++)
		for (int j = 1; j <= 1000; j++)
		if (i != 1 || j != 1){
			int ok1 = 1, ok2 = 1;
			int x1 = i - 1, y1 = j - 2;
			int x2 = i - 2, y2 = j - 1;
			
			if (x1 < 1 || y1 < 1) ok1 = 0;
			if (x2 < 1 || y2 < 1) ok2 = 0;
			
			
			if (!ok1 && !ok2){
				Knight[i][j] = 2;
				continue;
			}
			
			if (ok1 && ok2){
				
				if (Knight[x1][y1] == 0 || Knight[x2][y2] == 0){
					Knight[i][j] = 1;
					continue;
				}
				
				if (Knight[x1][y1] == 1 && Knight[x2][y2] == 1){
					Knight[i][j] = 0;
					continue;
				}
				
				Knight[i][j] = 2;
				
				continue;
			}
			
			if (ok1){
				if (Knight[x1][y1] == 2)
					Knight[i][j] = 2;
				else
					Knight[i][j] = 1 - Knight[x1][y1];
				continue;
			}
			
			if (ok2){
				if (Knight[x2][y2] == 2)
					Knight[i][j] = 2;
				else
					Knight[i][j] = 1 - Knight[x2][y2];
				continue;
			}
			
		}
	
}


int main(){
	
	makeQueen();
	makeKnight();
	
	int Case;
	scanf("%d", &Case);
	
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d%d%d", &k, &n, &m);
		if (k == 1){
			if (n & 1 && m & 1){
				printf("G\n");
			} else
				printf("B\n");
			
			continue;
		}
		if (k == 2){
			if (n == m){
				printf("G\n");
			} else
				printf("B\n");
			
			continue;
		}
		if (k == 3){
			if (Knight[n][m] == 2){
				printf("D\n");
			} else
			if (Knight[n][m] == 1){
				printf("B\n");
			} else
				printf("G\n");
						
			continue;
		}
		if (k == 4){
			if (Queen[n][m])
				printf("B\n");
			else
				printf("G\n");
			continue;
		}
	}
	
	return 0;
}

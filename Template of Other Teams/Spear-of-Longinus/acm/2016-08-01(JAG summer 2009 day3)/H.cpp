#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 31;
const int M = N * N * N * N * 2;

const int dir[5][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};

int n, m;

// Army + Queen + (0 : Army 1 : Queen)

vector<int> G;

int id[N][N][N][N][2];
short flag[M], deg[M];
char str[N];
char map[N][N];
int Ax, Ay, Qx, Qy;
int Q[M];
int tmp[M][4];
int cnt;

int main(){
	
	while (1){
		scanf("%d%d", &m, &n);
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++){
			scanf("%s", str + 1);
			for (int j = 1; j <= m; j++){
				map[i][j] = str[j];
			
				if (map[i][j] == 'A'){
					Ax = i;
					Ay = j;
					
					map[i][j] = '.';
				}
				
				if (map[i][j] == 'Q'){
					Qx = i;
					Qy = j;
					
					map[i][j] = '.';
				}
					
			}
		}
		
		cnt = 0;
		for (int ai = 1; ai <= n; ai++)
			for (int aj = 1; aj <= m; aj++)
				for (int qi = 1; qi <= n; qi++)
					for (int qj = 1; qj <= m; qj++)
						for (int who = 0; who < 2; who++){
							++cnt;
							id[ai][aj][qi][qj][who] = cnt;
							
							tmp[cnt][0] = ai;
							tmp[cnt][1] = aj;
							tmp[cnt][2] = qi;
							tmp[cnt][3] = qj;
							//tmp[cnt][4] = who;
						}
		
		for (int i = 1; i <= cnt; i++){
			flag[i] = -1;
			deg[i] = 0;
		}
		
		for (int ai = 1; ai <= n; ai++)
			for (int aj = 1; aj <= m; aj++)
			if (map[ai][aj] != '#')
				for (int qi = 1; qi <= n; qi++)
					for (int qj = 1; qj <= m; qj++)
					if (map[qi][qj] != '#')
						for (int who = 0; who < 2; who++){
							
							int Cur = id[ai][aj][qi][qj][who];
							
							//catch
							if (ai == qi && aj == qj){
								if (who == 0) flag[Cur] = 1;
								else flag[Cur] = 0;
								
								continue;
							}
							
							//escape
							if (who == 1 && map[qi][qj] == 'E' && abs(ai - qi) + abs(aj - qj) >= 1){
								flag[Cur] = 1;
								continue;
							}
							
							if (who == 0 && map[qi][qj] == 'E' && abs(ai - qi) + abs(aj - qj) > 1){
								flag[Cur] = 0;
								continue;
							}
							
							
							for (int i = 0; i <= 4; i++){
								int ax = ai, ay = aj, qx = qi, qy = qj;
								
								if (who == 0){
									ax += dir[i][0];
									ay += dir[i][1];	
									
									if (ax < 1 || ax > n || ay < 1 || ay > m || map[ax][ay] == '#') continue;
									
								} else {
									qx += dir[i][0];
									qy += dir[i][1];
									
									if (qx < 1 || qx > n || qy < 1 || qy > m || map[qx][qy] == '#') continue;
								}
								
								int To = id[ax][ay][qx][qy][1 - who];
								
								deg[Cur]++;
								
							}
							
						}
						
		int ii = 0, jj = 0;
		for (int i = 1; i <= cnt; i++)
			if (flag[i] != -1){
				Q[++jj] = i;	
			}
		
		while (ii < jj){
			int Cur = Q[++ii];
			
			int lst = Cur % 2;
			
			G.clear();
			for (int i = 0; i <= 4; i++){
				int ax = tmp[Cur][0], ay = tmp[Cur][1], qx = tmp[Cur][2], qy = tmp[Cur][3];
								
				if (lst == 0){
					ax += dir[i][0];
					ay += dir[i][1];	
									
					if (ax < 1 || ax > n || ay < 1 || ay > m || map[ax][ay] == '#') continue;
									
				} else {
					qx += dir[i][0];
					qy += dir[i][1];
									
					if (qx < 1 || qx > n || qy < 1 || qy > m || map[qx][qy] == '#') continue;
				}
								
				int To = id[ax][ay][qx][qy][lst];
				
				
				G.push_back(To);			
			}
			
			
			if (flag[Cur] == 0){
				for (int i = 0; i < G.size(); i++){
					int To = G[i];
					
					if (flag[To] != -1) continue;
					
					flag[To] = 1;
					deg[To]--;
					Q[++jj] = To;
				}
			} else {
				for (int i = 0; i < G.size(); i++){
					int To = G[i];
					
					if (flag[To] != -1) continue;
					
					deg[To]--;					
					if (deg[To] == 0){
						
						flag[To] = 0;
						Q[++jj] = To;
					}
				
				}
			}
		}
		
		if (flag[id[Ax][Ay][Qx][Qy][1]] == -1)
			printf("Queen can not escape and Army can not catch Queen.\n");
		if (flag[id[Ax][Ay][Qx][Qy][1]] == 1)
			printf("Queen can escape.\n");
		if (flag[id[Ax][Ay][Qx][Qy][1]] == 0)
			printf("Army can catch Queen.\n");
		
	}
	
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 2005;

int n, m;
char str[N];
int Q[3][N * 2];

vector<int> G[3][N * 2];
int Cnt[3][N * 2],id[3][N * 2];;

void Add(int Col, int x, int y){
	G[Col][x].push_back(y);
	Cnt[Col][y]++;
}

bool Topu(int Col){
	int ii = 0, jj = 0;
	for (int i = 1; i <= n * 2; i++)
		if (Cnt[Col][i] == 0){
			++jj;
			Q[Col][jj] = i;
		}
	
	while (ii < jj){
		++ii;
		int Cur = Q[Col][ii];
		for (int i = 0; i < G[Col][Cur].size(); i++){
			int To = G[Col][Cur][i];
			--Cnt[Col][To];
			if (Cnt[Col][To] == 0){
				++jj;
				Q[Col][jj] = To; 
			}
		}
	}
	
	if (jj != n * 2) return 0;
	
	for (int i = 1; i <= n * 2; i++)
		id[Col][Q[Col][i]] = i;
	return 1;
}

int main(){
	
	int Case = 0;
	while (1){
		
		scanf("%d%d", &n, &m);
		if (!n && !m) break;
		
		for (int i = 1; i <= n * 2; i++)
			for (int Col = 0; Col < 3; Col++){
				G[Col][i].clear();
				Cnt[Col][i] = 0;
			}
		
		for (int i = 1; i <= m; i++){
			scanf("%s", str);
			if (str[0] == 'I'){
				int u, v;
				scanf("%d%d", &u, &v);
				for (int Col = 0; Col < 3; Col++){
					Add(Col, u, v + n);
					Add(Col, v, u + n);
				}
			} else {
				int u, v;
				scanf("%d%d", &u, &v);
				int Col = str[0] - 'X'; 
				Add(Col, u + n, v);
			}
		}
		
		for (int i = 1; i <= n; i++)
			for (int Col = 0; Col < 3; Col++)
				Add(Col, i, n + i);
		
		++Case;
		printf("Case %d: ", Case);
		if (!Topu(0) || !Topu(1) || !Topu(2)){
			printf("IMPOSSIBLE\n");
			printf("\n");
			continue;
		}
		
		printf("POSSIBLE\n");
		for (int i = 1; i <= n; i++){
			printf("%d %d %d %d %d %d\n",id[0][i],id[1][i],id[2][i],id[0][n + i],id[1][n + i],id[2][n + i]);
		}
		printf("\n");
		
	}
	
	return 0;
}

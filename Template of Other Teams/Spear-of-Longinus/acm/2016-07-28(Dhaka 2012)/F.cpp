#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

const int R = 20;
const int C = 50;
const int N = 50;

struct Arr{
	char s[R][C];
};

map<char, Arr> M;
int n, q, len;
char str[N], Ans[N];
int Vis[R][C];

void Solve(){
	for (int i = 1; i <= len; i++)
		Ans[i] = 'N';
	
	for (int i = 1; i <= 17; i++)
		for (int j = 1; j <= 43; j++)
			Vis[i][j] = -1;
	
	for (int i = 1; i <= len; i++){
		for (int j = 1; j <= 17; j++)
			for (int k = 1; k <= 43; k++){
				if (M[str[i]].s[j][k] == '*'){
					if (Vis[j][k] == -1){
						Vis[j][k] = i;
					} else {
						Vis[j][k] = -99999999;
					}
				}
			}
	}
	
	for (int i = 1; i <= 17; i++)
		for (int j = 1; j <= 43; j++)
			if (Vis[i][j] > 0)
				Ans[Vis[i][j]] = 'Y';
}

int main(){
	
	scanf("%d%d", &n, &q);
	scanf("%s", str + 1);
	
	for (int i = 1; i <= n; i++){
		Arr Cur;
		for (int j = 1; j <= 17; j++){
			scanf("%s", Cur.s[j] + 1);
		}
		M[str[i]] = Cur;
	}	
	
	for (int ii = 1; ii <= q; ii++){
		scanf("%s", str + 1);
		len = strlen(str + 1);
		
		Solve();
		
		printf("Query %d: ", ii);
		for (int i = 1; i <= len; i++)
			printf("%c", Ans[i]);
		printf("\n");
	}
	
	return 0;
}


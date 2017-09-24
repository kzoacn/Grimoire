#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>

#define foreach(e, x) for(__typeof(x.begin()) e = x.begin(); e != x.end(); ++e)

using namespace std;

const int N = 35;
const int L = 10005;
const int INF = (1 << 30);

int Case, n, m, k;
char s[L];
char t[L];
char str[N];

int mat[N][N], lx[N], ly[N], vx[N], vy[N], slack[N];
int match[N];

bool find(int x){
	vx[x] = 1;
	for (int i = 1; i <= 26; i++){
		if (vy[i]){
			continue;
		}
		int temp = lx[x] + ly[i] - mat[x][i];
		if (temp == 0){
			vy[i] = 1;
			if (match[i] == -1 || find(match[i])) {
				match[i] = x;
				return true;
			}
		} else {
			slack[i] = min(slack[i], temp);
		}
	}
	return false;
}

int KM(){
	for (int i = 1; i <= 26; i++){
		lx[i] = -INF;
		ly[i] = 0;
		match[i] = -1;
		for (int j = 1; j <= 26; j++){
			lx[i] = max(lx[i], mat[i][j]);
		}
	}
	for (int i = 1; i <= 26; i++){
		for (int j = 1; j <= 26; j++){
			slack[j] = INF;
		}
		for (; ;){
			memset(vx, 0, sizeof(vx));
			memset(vy, 0, sizeof(vy));
			for (int j = 1; j <= 26; j++){
				slack[j] = INF;
			}
			if (find(i)){
				break;
			}
			int delta = INF;
			for (int j = 1; j <= 26; j++){
				if (!vy[j]){
					delta = min(delta, slack[j]);
				}
			}
			for (int j = 1; j <= 26; j++){
				if (vx[j]){
					lx[j] -= delta;
				}
				if (vy[j]){
					ly[j] += delta;
				} else {
					slack[j] -= delta;
				}
			}
		}
	}
	
	int answer = 0;
	for (int i = 1; i <= 26; i++){
		answer += mat[match[i]][i];
	}
	return answer;
}

int main(){
	scanf("%d", &Case);
	while (Case){
		--Case;
		scanf("%d%d%d", &n, &k, &m);
		for (int i = 1; i <= n; i++){
			scanf("%s", str);
			s[i] = str[0];
		}
		for (int times = 1; times <= m; times++){
			
			for (int i = 1; i <= 26; i++)
				for (int j = 1; j <= 26; j++)
					mat[i][j] = 0;
			
			for (int i = 1; i <= n; i++){
				scanf("%s", str);
				t[i] = str[0];                                                                                                       
			}
			
			for (int i = 1; i <= n; i++){
				mat[t[i] - 'A' + 1][s[i] - 'A' + 1]++;	
			}
			
			/*for (int i = 1; i <= 26; i++){
				for (int j = 1; j <= 26; j++)
					printf("%d ", mat[i][j]);
				printf("\n");
			}*/
			
			double Ans = 1.0 * KM() / n;
			printf("%.4f\n", Ans);
			
		}
		
	}
	return 0;
}

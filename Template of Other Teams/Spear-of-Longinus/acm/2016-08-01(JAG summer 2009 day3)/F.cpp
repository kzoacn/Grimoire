#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

int n, m;
int fa[N], bcj[N], first[N];
char s[10];
int Q[N][2];

int Get(int x){
	if (bcj[x] == x) return x;
	bcj[x] = Get(bcj[x]);
	return bcj[x];
}

int main(){
	
	while (1){
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		
		for (int i = 2; i <= n; i++)
			scanf("%d", &fa[i]);
		
		for (int i = 1; i <= n; i++){
			bcj[i] = i;
			first[i] = -1;
		}
		
		first[1] = 0;
		for (int i = 1; i <= m; i++){
			int u;
			scanf("%s", s);
			scanf("%d", &u);
			
			Q[i][1] = u;
			
			if (s[0] == 'M'){
				if (first[u] == -1) first[u] = i;
				Q[i][0] = 0;
			} else 
				Q[i][0] = 1;
		}
		
		for (int i = 1; i <= n; i++)
			if (first[i] == -1) bcj[i] = fa[i];
		
		long long Ans = 0;
		for (int i = m; i >= 1; i--){
			int Cur = Q[i][1];
			//for (int j = 1; j <= n; j++)
			//	printf("%d ", bcj[j]);
			//puts("");
			
			if (Q[i][0] == 0){
				if (i == first[Cur]) bcj[Cur] = fa[Cur];
				
			} else {
				Ans += Get(Cur);
				//printf("%d\n", Get(Cur));
			}
		}
		
		cout << Ans << endl;
	}
	
	return 0;
}

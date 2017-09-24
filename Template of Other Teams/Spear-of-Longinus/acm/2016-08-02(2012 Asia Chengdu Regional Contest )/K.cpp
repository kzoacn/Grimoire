#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 10005;

int n, m, tot;
bool vis[10];
int can[10];
int lst[N], cur[N], mo[N];
bool flag[N];

void work(int x){
	if (x == 0) return;
	work(lst[x]);
	printf("%d", cur[x]);
}

int main(){
	
	int ii = 0;
	while (scanf("%d%d", &n, &tot) == 2){
		for (int i = 0; i <= 9; i++)
			vis[i] = 0;
		for (int i = 1; i <= tot; i++){
			int x;
			scanf("%d", &x);
			vis[x] = 1;
		}
		
		m = 0;
		for (int i = 0; i <= 9; i++)
			if (!vis[i]){
				can[++m] = i;
			}
		
		++ii;
		printf("Case %d: ", ii);
		
		if (m == 0){
			puts("-1");
			continue;
		}
		
		for (int i = 0; i < n; i++)
			flag[i] = 0;
		
		int le = 0, ri = 0;
		for (int i = 1; i <= m; i++){
			if (can[i] == 0) continue;
			++ri;
			lst[ri] = 0;
			cur[ri] = can[i];
			mo[ri] = cur[ri] % n;
			flag[mo[ri]] = 1;
		}
		
		int Ans = -1;
		while (le < ri && Ans == -1){
			++le;
			if (mo[le] == 0){
				Ans = le;
				break;
			}
			for (int i = 1; i <= m; i++){
				int Mo = (mo[le] * 10 + can[i]) % n;
				if (!flag[Mo]){
					++ri;
					lst[ri] = le;
					cur[ri] = can[i];
					mo[ri] = Mo;
					flag[Mo] = 1;
				}
			}
		}
		
		if (Ans == -1) puts("-1");
		else {
			work(Ans);
			puts("");
		}
	}
	
	return 0;
}



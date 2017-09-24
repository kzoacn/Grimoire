#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

int a[N];
int ans[N];
int maxl;
int n, m;

int main(){

	int Case;
	scanf("%d", &Case);
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d", &m);
		int cnt = 0;
		n = 0;
		for (int i = 1; i <= m; i++){
			int x;
			scanf("%d", &x);
			if (x == 0) cnt++;
			else {
				a[++n] = x - cnt;
			}
		}
		
		if (!n){
			printf("Case #%d: %d\n", ii, m);
			continue;
		}
		
		int maxl = 1;
		ans[1] = a[1];
		for (int i = 2; i <= n; i++){
			if (a[i] > ans[maxl]){
				ans[++maxl] = a[i];
			} else {
				int id = lower_bound(ans + 1, ans + maxl, a[i]) - ans;
				ans[id] = a[i];
			}
		}
		
		printf("Case #%d: %d\n", ii, maxl + cnt);
		
	}

	return 0;
}

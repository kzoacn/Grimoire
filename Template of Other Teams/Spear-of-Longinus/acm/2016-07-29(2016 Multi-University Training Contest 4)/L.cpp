#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

int tree[N], Ans[N];
int n;
int a[N];

int Query(int x){
	int Ret = 0;
	while (x <= n){
		Ret += tree[x];
		x = x + (x & (-x));
	}
	return Ret;
}

void Add(int x){
	while (x > 0){
		tree[x]++;
		x = x - (x & (-x));
	}
}

int main(){
	
	int Case;
	scanf("%d", &Case);
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		
		for (int i = 1; i <= n; i++) tree[i] = 0;
		
		for (int i = 1; i <= n; i++){
			int le , ri;
			le = min(i, a[i]);
			
			ri = max(a[i], a[i] + Query(a[i]));
			
			Add(a[i]);
			
			Ans[a[i]] = ri - le;
		}
		
		printf("Case #%d: ", ii);
		for (int i = 1; i < n; i++)
			printf("%d ",Ans[i]);
		printf("%d\n", Ans[n]);
	}
	
	return 0;
}

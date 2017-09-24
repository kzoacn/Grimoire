#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>

using namespace std;

int calc(int x, int y, int type) {
	if(type == 1) {
		return x & y;
	}
	if(type == 2) {	
		return x | y;
	}
	return x ^ y;
}

const int N = 1 << 17;
const int MOD = 1000000007;

int nowtype, start[N], w[N];
long long f[N];
vector<int> adj[N];

void build(int x, int y) {
	adj[x].push_back(y);
}

long long Max[1 << 8][1 << 8];

long long tmp[N][1 << 8];

void dfs(int x, int fa) {
	long long ans = 0;
	int front = w[x] >> 8;
	int tail = w[x] - (w[x] >> 8 << 8);
	
	for(int i = 0; i < 1 << 8; i++) {
		ans = max(ans, 1LL * (calc(i, front, nowtype) << 8) + Max[i][tail]);
	}
	
	for(int i = 0; i < 1 << 8; i++) {
		tmp[x][i] = Max[front][i];
	}
	
	f[x] = ans;
	for(int i = 0; i < 1 << 8; i++) {
		long long key = calc(tail, i, nowtype) + f[x];
		if(Max[front][i] < key) {
			Max[front][i] = key;
		}
	}
	for(int i = 0; i < adj[x].size(); i++) {
		int to = adj[x][i];
		if(to == fa) {
			continue;
		}
		dfs(to, x);
	}
	
	for(int i = 0; i < 1 << 8; i++) {
		Max[front][i] = tmp[x][i];
	}
	return ;
}

void work() {
	int n;
	char s[15];
	scanf("%d", &n);
	scanf("%s", s + 1);
	if(s[1] == 'A') {
		nowtype = 1;
	} else if(s[1] == 'O') {
		nowtype = 2; 
	} else if(s[1] == 'X') {
		nowtype = 3;
	}
	for(int j = 0; j < 1 << 8; j++) {
		for(int i = 0; i < 1 << 8; i++) {
			Max[j][i] = -0x3f3f3f3f;
		}
	}
	for(int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
	}
	for(int i = 1; i <= n; i++) {
		adj[i].clear();
		f[i] = 0;
	}
	for(int i = 2; i <= n; i++) {
		int fa;
		scanf("%d", &fa);
		build(fa, i);
	}
	dfs(1, 0);
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans = (ans + 1LL * i * (f[i] + w[i]) % MOD) % MOD;
	}	
	printf("%d\n", ans);
}

int main() {	
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++) {
		work();
	}
	return 0;
}


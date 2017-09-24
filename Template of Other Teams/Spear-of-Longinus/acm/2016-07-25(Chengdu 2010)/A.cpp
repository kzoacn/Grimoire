#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 25;
const int S = 2005;

typedef long long LL;

int Case;
LL n, m;
LL f[N][N][S];
int a[N];

LL dfs(int pos, int cent, int pre, bool limit){
	if (pos <= 0)
		return (pre == 0);
	if (pre < 0)
		return 0;
	if (!limit && f[pos][cent][pre] != -1) return f[pos][cent][pre];
	int up;
	if ( limit ) up = a[pos]; else up = 9;
	
	LL Ans = 0;
	
	for (int i = 0; i <= up; i++){
		bool limit1;
		if (i < up) limit1 = 0; else limit1 = 1;
		Ans += dfs(pos - 1, cent, pre + (pos - cent) * i, limit & limit1);
	} 
	
	if (!limit) f[pos][cent][pre] = Ans;
	return Ans;
}

LL Solve(LL n){
	if (n < 0) return 0;
	int len = 0;
	while (n > 0){
		++len;
		a[len] = n % 10;
		n /= 10;
	}
	LL Ans = 0;
	for (int i = 1; i <= len; i++)
		Ans += dfs(len, i, 0, 1);
	return Ans - len + 1;
}

int main(){
	
	scanf("%d", &Case);
	memset(f, -1, sizeof(f));
	while (Case){
		Case--;
		scanf("%I64d%I64d", &n, &m);
		
		printf("%I64d\n", Solve(m) - Solve(n - 1));
	}
	
	return 0;
	
}

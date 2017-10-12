#include<bits/stdc++.h>
using namespace std;
const int maxn=505;
char s[maxn][2010];
int n;
int fail[2020];

bool contain(int x,int y){
	int n = strlen(s[x] + 1), m = strlen(s[y] + 1);
	if (n < m) {
		return false;
	}
	fail[1] = fail[0] = 0;
	for (int i = 2; i <= m; ++i) {
		int j = fail[i - 1];
		while (j && s[y][j + 1] != s[y][i]) {
			j = fail[j];
		}
		if (s[y][j + 1] == s[y][i]) {
			++j;
		}
		fail[i] = j;
	}
	int j = 0;
	for (int i = 1; i <= n; ++i) {
		while (j && s[y][j + 1] != s[x][i]) {
			j = fail[j];
		}
		if (s[y][j + 1] == s[x][i]) {
			++j;
		}
		if (j == m) {
			return true;
		}
	}
	return false;
}

int tmp[maxn],sz;

int solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}
	int ans=-1;
	for(int i=1,j=1;i<=n;i++){
		while(j<i){
			if(contain(i,j))
				j++;
			else break;
		}
		if(j!=i)
			ans=i;
	}
	return ans;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}

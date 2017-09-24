#include<bits/stdc++.h>
using namespace std;

void solve(){
	int n;
	scanf("%d",&n);
	int cnt=0;
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		if(x%2)cnt++;
	}
	if(cnt>=n-cnt)
		puts("2 1");
	else puts("2 0");
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}

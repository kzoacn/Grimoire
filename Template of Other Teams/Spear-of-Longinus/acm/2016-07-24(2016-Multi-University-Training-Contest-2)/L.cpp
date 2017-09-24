#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
char s[maxn],t[maxn];
bitset<maxn>dp[2][3];
bitset<maxn>vec[26];
bitset<maxn>ans;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		scanf("%s",s);
		scanf("%s",t);
		for(int i=0;i<26;i++)
			vec[i].reset();
		for(int i=0;i<n;i++)
			vec[s[i]-'a'][i]=1;
		
		int cur=0;	
		
		dp[cur][1]=vec[t[0]-'a'];
		if(1<m)dp[cur][2]=vec[t[1]-'a'];
		
		cur^=1;
		for(int j=1;j<m;j++){
			dp[cur][0].reset();
			dp[cur][1].reset();
			dp[cur][2].reset();
			
			if(j)
				dp[cur][0]=(dp[cur^1][2]<<1)&vec[t[j-1]-'a'];
			
			dp[cur][1]=((dp[cur^1][0]|dp[cur^1][1])<<1)&vec[t[j]-'a'];
			
			if(j+1<m)
				dp[cur][2]=((dp[cur^1][0]|dp[cur^1][1])<<1)&vec[t[j+1]-'a'];
			
			cur^=1;
		}
		
		cur^=1;
		ans.reset();
		for(int i=m-1;i<n;i++)
			if(dp[cur][0][i]|dp[cur][1][i])
				ans[i-m+1]=1;
		for(int i=0;i<n;i++)
			putchar(ans[i]+'0');
		puts("");
	}	
	return 0;
}


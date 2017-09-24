

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+4;
typedef unsigned long long UL;
char s[maxn],t[maxn];
int n;
UL h_l[maxn];
UL hs[maxn];
UL ht[maxn];
int cnts[maxn][26];
int cntt[maxn][26];
UL get(int l,int r){
	if(l>r)return 0;
	return hs[r]-hs[l-1]*h_l[r-l+1];
}
int ans[maxn];
int main(){
	h_l[0]=1;
	for(int i=1;i<maxn;i++)
		h_l[i]=h_l[i-1]*233;
	while(scanf("%s%s",s+1,t+1)==2){
		int n=strlen(s+1);
		for(int i=1;i<=n;i++)	
			hs[i]=hs[i-1]*233+s[i];
		for(int i=1;i<=n;i++)	
			ht[i]=ht[i-1]*233+t[i];
		for(int i=1;i<=n;i++)
		for(int j=0;j<26;j++){
			cnts[i][j]=0;
			cntt[i][j]=0;
		}
		
		for(int i=1;i<=n;i++){
			cnts[i][s[i]-'a']++;
			cntt[i][t[i]-'a']++;
		}	
		
		for(int i=1;i<=n;i++)
		for(int j=0;j<26;j++){
			cnts[i][j]+=cnts[i-1][j];
			cntt[i][j]+=cntt[i-1][j];
		}
		
		for(int i=1;i<=n;i++){
			int flag=1;
			for(int j=0;j<26;j++)
				if(cnts[i][j]!=cntt[i][j]){
					flag=0;
					continue;
				}
			if(!flag){
				ans[i]=0;
				continue;
			}
			ans[i]=0;
			for(int j=1;j<=i;j++){
				UL h=get(1,j)+get(j+1,i)*h_l[j];
				if(h==ht[i]){
					ans[i]=1;
					break;
				}
			}
		}
		for(int i=1;i<=n;i++)
			putchar(ans[i]?'1':'0');
		puts("");
	}
	return 0;
}

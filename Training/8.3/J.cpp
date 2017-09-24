#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long UL;
const int maxn=1010;
int n;
UL h1[maxn],h2[maxn];
int len[maxn];
UL h_l[maxn];
UL base=233;
char s[2232];
int solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		len[i]=strlen(s+1);
		h1[i]=h2[i]=0;
		for(int j=1;j<=len[i];j++){
			h1[i]=h1[i]*base+s[j];
		}
		reverse(s+1,s+1+len[i]);
		for(int j=1;j<=len[i];j++){
			h2[i]=h2[i]*base+s[j];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(i!=j){
			UL hh1,hh2;
			
			hh1=h1[i]*h_l[len[j]]+h1[j];
			
			hh2=h2[j]*h_l[len[i]]+h2[i];
			
			if(hh1==hh2)
				ans++;
		}
	}
	return ans;
}

int main(){
	h_l[0]=1;
	for(int i=1;i<maxn;i++)
		h_l[i]=h_l[i-1]*base;
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %d\n",t,solve());
	}		
	return 0;
}

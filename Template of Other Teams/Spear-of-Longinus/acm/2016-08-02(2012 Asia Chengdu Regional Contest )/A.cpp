#include<bits/stdc++.h>
using namespace std;
char s[233333];

int main(){
	int t=0;
	int n;
	while(scanf("%d",&n)==1){
		t++;
		int ans=0;
		for(int i=1;i<=n;i++){
			scanf("%s",s);
			int len=strlen(s);
			int res=0;
			for(int j=0;j<len;j++)
				res+=int(s[j]);
			ans=max(ans,res);
		}
		printf("Case %d: %d\n",t,ans);
	}
	return 0;
}



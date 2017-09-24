#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
char s[201];
int fa[201];
int cnt[201];
int vis[201];
int main(){
	int T;scanf("%d",&T);
	for(int t=1;t<=T;t++){
		printf("Case %d\n",t);
		scanf("%s",s+1);
		int len=strlen(s+1);
		for(int i=1;i<=26;i++){
			fa[i]=0;
			cnt[i]=0;
			vis[i]=0;
		}
		int u=0;
		cnt[s[1]-'A'+1]--;
		for(int i=1;i<=len;i++){
			int v=s[i]-'A'+1;
			if(!vis[v]){
				vis[v]=1;
				fa[v]=u;
				u=v;
				cnt[u]++;
			}else{
				u=fa[u];
				cnt[u]++;
			}
		}
		for(int i=1;i<=26;i++)
			if(cnt[i]>0)
				printf("%c = %d\n",'A'+i-1,cnt[i]);
	}
	return 0;
}

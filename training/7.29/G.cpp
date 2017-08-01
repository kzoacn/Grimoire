#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long UL;
const int maxn=3003;
UL rnd(){
	return ((UL)rand()<<32) ^ ((UL)rand()<<16) ^ rand();
}

int n;
int a[maxn],b[maxn];
UL mp[maxn];
unordered_map<UL,int>M;
UL tmp[maxn],tmp2[maxn];
int main(){
	for(int i=0;i<maxn;i++)
		mp[i]=rnd();
	while(scanf("%d",&n)==1){
		if(!n)break;
		M.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
		}
		int ans=0;
		for(int l=2;l<=n;l++){
			UL cur1=0,cur2=0;
			tmp[0]=0;tmp2[0]=0;
			for(int i=1;i<=l;i++)
				cur1^=mp[a[i]];
			tmp[++tmp[0]]=cur1;
			for(int i=1;i+l<=n;i++){
				cur1^=mp[a[i]];
				cur1^=mp[a[i+l]];
				tmp[++tmp[0]]=cur1;
			}
			sort(tmp+1,tmp+1+tmp[0]);
			
			for(int i=1;i<=l;i++)
				cur2^=mp[b[i]];
			tmp2[++tmp2[0]]=cur2;
			for(int i=1;i+l<=n;i++){
				cur2^=mp[b[i]];
				cur2^=mp[b[i+l]];
				tmp2[++tmp2[0]]=cur2;
			}
			sort(tmp2+1,tmp2+1+tmp2[0]);
			int i = 1;					
			for (int j = 1; j <= tmp2[0]; ++j) {
				while (i < tmp[0] && tmp[i] < tmp2[j]) {
					++i;
				}
				if (i > tmp[0]) {
					break;
				}
				if (tmp[i] == tmp2[j]) {
					++ans;
				}
			}
		}
		
		printf("%d\n",ans);
	}
	return 0;
}

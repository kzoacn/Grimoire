#include<bits/stdc++.h>
#define __advance __attribute__((optimize("O3"))) __inline
using namespace std;
const int maxn=2e5+5;
typedef unsigned int UL;
UL base=10007;
UL h_l[maxn],h[maxn];
UL get(int l,int r){	
	return h[r]-h[l-1]*h_l[r-l+1];
}
char s[maxn];


__advance int Q(int l,int r){
	int x=r-l;
	int ans=0;
	
	int st=1;
	
	int lef=1,rig=x;
	int step=max(300,1);
	for(int i=1;i<=x;i+=step){
		if(get(l,l+i-1)==get(r-i+1,r)){
			st=i;
		}
	}
	
	for(int i=st;i<=x;i++){
		if(get(l,l+i-1)==get(r-i+1,r)){
			ans=i;
		}
	}
	return ans;
}

int mp[555];

int main(){
	srand(time(0));

	int n,q;scanf("%d%d",&n,&q);
	scanf("%s",s+1);
	h_l[0]=1;
	for(int i=1;i<=n;i++){
		h_l[i]=h_l[i-1]*base;
		h[i]=h[i-1]*base+(s[i]+1);
	}
	
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",Q(l,r));
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef unsigned long long UL;
const UL base=233;
UL h_l[maxn],ha[maxn],hb[maxn];

UL get(UL *h,int l,int r){
	return h[r]-h[l-1]*h_l[r-l+1];
}
char a[maxn],b[maxn];
int n,m;

int lcp(int l1,int r1,int l2,int r2){
	int len=min(r1-l1+1,r2-l2+1);
	int l=1,r=len+1;
	while(l<r){
		int mid=(l+r)>>1;
		if(get(ha,l1,l1+mid-1)==get(hb,l2,l2+mid-1))
			l=mid+1;
		else
			r=mid;
	}
	return l-1;
}

bool check(int cura){
	int curb=1;
	int cnt=0;
	while(1){
		int LCP=lcp(cura,n,curb,m);
		if(cnt<=1){
			cura++;
			curb++;
		}
		cura+=LCP;
		curb+=LCP;
		if(curb>m)
			return true;
		if(++cnt==3||cura>n)
			break;
	}
	return false;
}

int solve(){
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1);
	m=strlen(b+1);
	for(int i=1;i<=n;i++)
		ha[i]=ha[i-1]*base+a[i];
	for(int i=1;i<=m;i++)
		hb[i]=hb[i-1]*base+b[i];
	for(int i=1;i+m-1<=n;i++){
		if(check(i)){
			return i-1;
		}
	}
	return -1;
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

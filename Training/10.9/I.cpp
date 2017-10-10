#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef unsigned long long UL;
int m,l,n;
char s[maxn];
int pre[maxn];
map<UL,int>pos;

const UL base=233;

UL h_l[maxn];
UL h[maxn];
UL get(int l,int r){
	return h[r]-h[l-1]*h_l[r-l+1];
}

int a[maxn];
int sz=0;
int calc(){

	for(int i=1;i<=sz;i++){
		a[i]=a[i]/l;
//		cerr<<a[i]<<" ";
	}
//	cerr<<endl;
	int ans=0;
	deque<pair<int,int> >dq;
	for(int i=1;i<=sz;i++){
		while(dq.size()&&dq.front().second<=i-m){
			dq.pop_front();
		}
		while(dq.size()&&dq.back().first<=a[i])
			dq.pop_back();
		dq.push_back(make_pair(a[i],i));
				
		if(i>=m){
			if(dq.size()&&dq.front().first<=i-m){
				ans++;
			}
		}
	}
	return ans;
}
int main(){

	h_l[0]=1;
	for(int i=1;i<maxn;i++)
		h_l[i]=h_l[i-1]*base;

	while(scanf("%d%d",&m,&l)==2){
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int i=1;i<=n;i++){
			h[i]=h[i-1]*base+s[i];
		}
		int ans=0;
		for(int i=0;i<l;i++){
			pos.clear();
			sz=0;
			for(int j=(i==0?l:i);j<=n;j+=l){
				if(j>=l){
					UL h=get(j-l+1,j);
					pre[j]=pos[h];
					pos[h]=j;
				}else{
					pre[j]=0;
				}
				if(j>=l)
					a[++sz]=pre[j];
			}
			ans+=calc();
		}
/*		for(int i=1;i<=n;i++)
			cerr<<pre[i]<<" ";
		cerr<<endl;
*/		
		printf("%d\n",ans);
	}
	return 0;
}

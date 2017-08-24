#include<bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

using namespace std;
const int maxn=1<<22;
int d[maxn];
int sz;
int n,m,p,l;
__advance void add(int x,int y){
	while(x<maxn){
		d[x]+=y;
		x+=x&-x;
	}
}
__advance int find(int k){
	register int cnt=0,ans=0;
	for(register int i=l;i>=0;i--){
		ans+=(1<<i);
		if(ans>=n*m||cnt+d[ans]>=k)ans-=(1<<i);
		else cnt+=d[ans];
	}
	return ans+1;
}

//int mp[1010][1010];
int a[1000*1000+11];

__advance int calc(){
	static int vis[1000*1000+11],T;
	T++;
	int ans=0;
	for(int i=1;i<=sz;i++){
		int x=i;
		if(vis[x]!=T){
			int len=0;
			while(vis[x]!=T){
				vis[x]=T;
				x=a[x];
				len++;
			}
			if(len%2==0)
				ans++;
		}
	}
	return ans;
}

bool solve(int _n,int _m,int _p){
		n=_n;
		m=_m;
		p=_p;
		sz=0;
		l=0;
		while((1<<l)<n*m)l++;
		l++;
		for(int i=0;i<(1<<l);i++)
			d[i]=0;
		for(int i=1;i<n*m;i++)
			add(i,1);
		int rest=n*m-1;
		while(rest){			
			int cnt=1+(rest-1)/p;
			rest-=cnt;
			for(register int k=0;k<cnt;k++){
				a[++sz]=find(1+k*p);
			}
			for(register int k=0;k<cnt;k++){
				add(a[sz-k],-1);
			}
		}

	return calc()%2==0;
}

__advance int main(){


	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>p;
		puts(solve(n,m,p)?"YES":"NO");
		
	}
	return 0;
}

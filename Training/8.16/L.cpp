#include<bits/stdc++.h>
using namespace std;

namespace Reader{
	const int L=(1<<15)+5;
	char buffer[L],*S,*T;
	__inline bool getchar(char &ch){
		if(S==T){
			T=(S=buffer)+fread(buffer,1,L,stdin);
			if(S==T){
				ch=EOF;
				return false;
			}
		}
		ch=*S++;
		return true;	
	}
	
	__inline bool getint(int &x){
		char ch;bool neg=0;
		for(;getchar(ch)&&(ch<'0'||ch>'9');)neg^= ch=='-';
		if(ch==EOF)return false;
		x=ch-'0';
		for(;getchar(ch),ch>='0'&&ch<='9';)
			x=x*10+ch-'0';
		if(neg)x=-x;
		return true;
	}
}
int t[int(5e6+5)];
int tmp[233];
int main(){
	int T;Reader::getint(T);
	for(int tt=1;tt<=T;tt++){
		int n;
		int a,b;
		Reader::getint(n);
		Reader::getint(a);
		Reader::getint(b);
		for(int i=1;i<=n;i++){
			Reader::getint(t[i]);
		}
		long long ans=-(1LL<<61);
		int sz=0;
		if(n<=10){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)if(i!=j){
					ans=max(ans,1ll*a*t[i]*t[i]+1ll*b*t[j]);
				}
			}
		}else{
			const int inf=1e9;
			int mx=-1,mn=-1;
			int mx2=-1,mn2=-1;
		
			for(int i=1;i<=n;i++){
				if(mx==-1||t[i]>=t[mx]){
					mx2=mx;
					mx=i;
				}else if(mx2==-1||t[i]>=t[mx2]){
					mx2=i;
				}
				
				if(mn==-1||t[i]<=t[mn]){
					mn2=mn;
					mn=i;
				}else if(mn2==-1||t[i]<=t[mn2]){
					mn2=i;
				}
				
			}
			for(int i=1;i<=n;i++){
				if(i!=mx)
					ans=max(ans,1ll*a*t[i]*t[i]+1ll*b*t[mx]);
				if(i!=mx2)
					ans=max(ans,1ll*a*t[i]*t[i]+1ll*b*t[mx2]);
				if(i!=mn)
					ans=max(ans,1ll*a*t[i]*t[i]+1ll*b*t[mn]);
				if(i!=mn2)
					ans=max(ans,1ll*a*t[i]*t[i]+1ll*b*t[mn2]);
			}
				
		}
		printf("Case #%d: %lld\n",tt,ans);
	}
	return 0;
}

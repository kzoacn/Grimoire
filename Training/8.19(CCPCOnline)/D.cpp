#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+6;
typedef long long LL;
int nxt[maxn];
char s1[maxn],s2[maxn],t[maxn];
LL cnt[maxn];
int n,m;
const LL mo=1e9+7;
int main(){
	int T;cin>>T;
	for(int tt=1;tt<=T;tt++){
		scanf("%s",s1+1);
		scanf("%s",s2+1);
		n=strlen(s1+1);
		m=strlen(s2+1);
		reverse(s1+1,s1+1+n);
		reverse(s2+1,s2+1+m);

		int sz=0;
		for(int i=1;i<=m;i++)
			t[++sz]=s2[i];
		t[++sz]='#';		
		for(int i=1;i<=n;i++)
			t[++sz]=s1[i];		
		
		for(int i=1;i<=sz;i++){
			nxt[i]=0;
			cnt[i]=0;
		}
		for(int i=2,j=nxt[1]=0;i<=sz;i++){
			while(j&&t[i]!=t[j+1])j=nxt[j];
			nxt[i]=j+=t[i]==t[j+1];
		}
		for(int i=m+2;i<=sz;i++){
			cnt[nxt[i]]++;
		}
		for(int i=m;i>=1;i--)
			cnt[nxt[i]]+=cnt[i];
		
		long long ans=0;
		for(int i=1;i<=m;i++){
			ans=(ans+i*cnt[i]%mo)%mo;
		}
		cout<<ans<<endl;
	}	
	return 0;
}

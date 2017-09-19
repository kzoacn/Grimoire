#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int cnt[maxn];
int d[maxn],can[maxn];
int n,m,q;
char s[maxn],t[maxn];
void add(int x,int y){
	while(x<=n){
		d[x]+=y;
		x+=x&-x;
	}
}
int get(int x){
	int ans=0;
	while(x){
		ans+=d[x];
		x-=x&-x;
	}
	return ans;
}

void dset(int x,int y){
	if(can[x]==y)return;
	if(y==1){
		add(x,1);
	}else{
		add(x,-1);
	}
	can[x]=y;
}

int Q(int l,int r){
	if(l>r)swap(l,r);
	r-=(m-1);
	if(l<=r)	
		return get(r)-get(l-1);
	return 0;
}
void C(int x,char ch){
	if(s[x]==ch)return ;
	for(int i=1;i<=m&&x-i+1>=1;i++){
		if(s[x]==t[i]&&ch!=t[i]){
			cnt[x-i+1]--;
			if(cnt[x-i+1]==m-1)
				dset(x-i+1,0);
		}else
		if(s[x]!=t[i]&&ch==t[i]){
			cnt[x-i+1]++;
			if(cnt[x-i+1]==m)
				dset(x-i+1,1);
		}
	}
	
	s[x]=ch;
}

int main(){
assert(0);
	int T;cin>>T;
	while(T--){
		scanf("%d",&q);
		scanf("%s%s",s+1,t+1);
		n=strlen(s+1);
		m=strlen(t+1);
		for(int i=1;i<=n;i++){
			can[i]=0;
			d[i]=0;
			cnt[i]=0;
		}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(s[i+j-1]==t[j]){
					cnt[i]++;
				}
			}
			if(cnt[i]==m)
				dset(i,1);
		}
		
		while(q--){
			char cmd[3],ss[3];
			int x,y;
			scanf("%s%d",cmd,&x);
			if(cmd[0]=='Q'){
				scanf("%d",&y);
				printf("%d\n",Q(x,y));
			}else{
				scanf("%s",ss);
				C(x,ss[0]);			
			}
		}
		puts("");
	}
	return 0;
}

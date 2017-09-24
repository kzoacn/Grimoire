#include<bits/stdc++.h>
#define rank rnk
using namespace std;
const int maxn=1e6+6;
const int BIT=20;
int n;
int a[maxn],x[maxn],y[maxn],c[maxn],sa[maxn],rank[maxn];
void calc_sa(int n){
	int m=128,k=1;
	memset(c,0,sizeof(*c)*(m+1));
	for(int i=1;i<=n;i++)c[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i;i--)sa[c[x[i]]--]=i;
	for(;k<=n;k<<=1){
		int tot=k;
		for(int i=n-k+1;i<=n;i++)y[i-n+k]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>k)y[++tot]=sa[i]-k;
		memset(c,0,sizeof(*c)*(m+1));
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i;i--)sa[c[x[y[i]]]--]=y[i];
		for(int i=1;i<=n;i++)y[i]=x[i];
		tot=1;x[sa[1]]=1;
		for(int i=2;i<=n;i++){
			if(max(sa[i],sa[i-1])+k>n||y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])
				tot++;
			if(tot==n) break;else m=tot;
		}
	}
}
char s[maxn];

int st[maxn][BIT];
int Log2[maxn];
int Qmax(int l,int r){
	int len=Log2[r-l+1];
	int ans=max(st[l][len],st[r-(1<<len)+1][len]);
	return ans;
}

int main(){
	Log2[0]=-1;
	for(int i=1;i<maxn;i++)
		Log2[i]=Log2[i-1]+((i&-i)==i);
	gets(s+1);
	n=strlen(s+1);
	//reverse(s+1,s+1+n);
	for(int i=1;i<=n;i++)a[i]=s[i];
	calc_sa(n);
	for(int i=1;i<=n;i++)rank[sa[i]]=i;
	
	for(int i=1;i<=n;i++)
		st[i][0]=rank[i];
	for(int j=1;j<BIT;j++)
		for(int i=1;i<=n;i++)
			st[i][j]=max(st[i][j-1],st[min(i+(1<<(j-1)),n)][j-1]);
	int m;scanf("%d",&m);
	while(m--){
		int l,r;scanf("%d%d",&l,&r);
		l=l;r=r;
		if(l>r)swap(l,r);
		int ans=Qmax(l,r);
		printf("%d\n",sa[ans]);
	}
	
	return 0;
}

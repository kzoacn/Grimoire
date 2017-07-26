#include<bits/stdc++.h>
using namespace std;
const int MAXL=2e5+5;
const int MAXN=MAXL*2+1;
const int BIT=20;
int a[MAXN],x[MAXN],y[MAXN],c[MAXN],sa[MAXN],rnk[MAXN],height[MAXN];
void calc_sa(int n){
	int m=26,k=1;
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
			x[sa[i]]=tot;
		}
		if(tot==n)break;else m=tot;
	}
}

int st[MAXN][BIT];
int Log2[MAXN];

void calc_height(int n){
	for(int i=1;i<=n;i++)rnk[sa[i]]=i;
	for(int i=1;i<=n;i++){
		height[rnk[i]]=max(0,height[rnk[i-1]]-1);
		if(rnk[i]==1)continue;
		int j=sa[rnk[i]-1];
		while(max(i,j)+height[rnk[i]]<=n && a[i+height[rnk[i]]]==a[j+height[rnk[i]]])
			++height[rnk[i]];
	}
	for(int i=1;i<=n;i++)
		st[i][0]=height[i];
	for(int j=1;j<BIT;j++){
		for(int i=1;i<=n;i++)
			st[i][j]=min(st[i][j-1],st[min(i+(1<<(j-1)),n)][j-1]);
	}
}

int Qmin(int l,int r){
	int len=Log2[r-l+1];
	int ans=min(st[l][len],st[r-(1<<len)+1][len]);
	return ans;
}
int n;
int lcp(int i,int j){
	if(i==j)return n-i+1;
	i=rnk[i];
	j=rnk[j];
	if(i>j)swap(i,j);
	return Qmin(i+1,j);
}

char s[MAXN],t[MAXN];
int len;
int ql[MAXN],qr[MAXN],q;
int digsum(int x){
	int ans=0;
	while(x>=10)x/=10,ans++;
	return ans+1;
}
int main(){
	Log2[0]=-1;
	for(int i=1;i<MAXN;i++)
		Log2[i]=Log2[i-1]+((i&-i)==i);
	while(scanf("%s",s+1)==1){
		scanf("%d",&q);
		long long ans1=0;
		for(int i=1;i<=q;i++){
			scanf("%d%d",&ql[i],&qr[i]);
			ans1+=qr[i]-ql[i];
			ans1++;
			ql[i]++;qr[i]++;
		}
		
		int len=strlen(s+1);
		n=len;
		for(int i=1;i<=len;i++)	
			a[i]=s[i]-'a'+1;
		calc_sa(len);
		calc_height(len);
		
		

		long long ans2=0;
		
		for(int i=1;i<=q;i++){
			int LCP=0;
			int qlen=qr[i]-ql[i];
			if(i==1){
				LCP=0;
			}else{
				//cerr<<"do"<<endl;
				LCP=lcp(ql[i-1],ql[i]);
				//cerr<<"after"<<endl;
				LCP=min(LCP,qr[i-1]-ql[i-1]);
				LCP=min(LCP,qr[i]-ql[i]);
			}
			ans2+=digsum(LCP)+1+1+(qlen-LCP);
		}		
		
		printf("%lld %lld\n",ans1,ans2);
	}

	return 0;
}

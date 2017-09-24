#include<bits/stdc++.h>
#define deb(x) cerr<< #x <<" = "<<x<<endl
#define rank rnkk
#define L first
#define R second
using namespace std;
const int maxn=4e5+5;
const int BIT=20;
typedef pair<int,int> pii;
int a[maxn],x[maxn],y[maxn],c[maxn],sa[maxn],rank[maxn],height[maxn];

void calc_sa(int n){
	int m=256,k=1;
	memset(c,0,sizeof(*c)*(m+1));
	for(int i=1;i<=n;i++)c[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
	for(;k<=n;k<<=1){
		int tot=k;
		for(int i=n-k+1;i<=n;i++)y[i-n+k]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>k)y[++tot]=sa[i]-k;
		memset(c,0,sizeof(*c)*(m+1));
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
		for(int i=1;i<=n;i++)y[i]=x[i];
		tot=1;x[sa[1]]=1;
		for(int i=2;i<=n;i++){
			if(max(sa[i],sa[i-1])+k>n||y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])++tot;
			x[sa[i]]=tot;
		}
		if(tot==n)break;else m=tot;
	}
}
int st[maxn][BIT];
int Log2[maxn];
void calc_height(int n){
	for(int i=1;i<=n;i++)rank[sa[i]]=i;
	for(int i=1;i<=n;i++){
		height[rank[i]]=max(0,height[rank[i-1]]-1);
		if(rank[i]==1)continue;
		int j=sa[rank[i]-1];
		while(max(i,j)+height[rank[i]]<=n && a[i+height[rank[i]]]==a[j+height[rank[i]]])
			++height[rank[i]];
	}
	for(int i=1;i<=n;i++)
		st[i][0]=height[i];
	for(int j=1;j<BIT;j++)
	for(int i=1;i<=n;i++)
		st[i][j]=min(st[i][j-1],st[min(i+(1<<(j-1)),n)][j-1]);
	
}
int Qmin(int l,int r){
	int len=Log2[r-l+1];
	return min(st[l][len],st[r-(1<<len)+1][len]);
}

int lcp(int l1,int r1,int l2,int r2){
	if(l1==l2)
		return min(r1,r2)-l1+1;
	int x=rank[l1];
	int y=rank[l2];
	if(x>y)swap(x,y);
	int ans=Qmin(x+1,y);
	ans=min(ans,r1-l1+1);
	ans=min(ans,r2-l2+1);
	return ans;
}
int n,k,len;
char s[maxn];

bool cmp(pair<int,int>a,pair<int,int>b){
	if(a.R-a.L!=b.R-b.L)
		return a.R-a.L<b.R-b.L;
	int LCP=lcp(a.L,a.R,b.L,b.R);
	if(LCP==a.R-a.L+1)
		return 0;
	return s[a.L+LCP]<s[b.L+LCP];
}
bool leq(int l1,int r1,int l2,int r2){
	if(r1-l1!=r2-l2)
		return r1-l1<r2-l2;
	int LCP=lcp(l1,r1,l2,r2);
	if(LCP==r1-l1+1)
		return 1;
	return s[l1+LCP]<=s[l2+LCP];
}

bool test(pii x,int st){
	int cur=st;
	
	for(int i=0;i<k;i++){
		int rig=min(cur+len-1,n);
		//cerr<<cur<<" to "<<" "<<rig<<endl; 
		if(leq(cur,rig,x.L,x.R)){
			cur=rig+1;
			//cerr<<"leq "<<endl;
		}else{
			cur=rig;
			//cerr<<"gr "<<endl;
		}
		if(cur-st>=n/2)
			return true;
	}
//	deb(st);
//	deb(cur);
	return cur-st>=n/2;
}

bool check(pii x){
	for(int i=1;i<=len+2&&i<=n/2;i++){
		if(test(x,i))
			return true;
	}
	return false;
}

int main(){
freopen("B.in","r",stdin);
	Log2[0]=-1;
	for(int i=1;i<maxn;i++)
		Log2[i]=Log2[i-1]+(i==(i&-i));
	
	scanf("%d%d",&n,&k);
	len=(n+k-1)/k;
	scanf("%s",s+1);
	if(n==k){
		int mx=0;
		for(int i=1;i<=n;i++)mx=max(mx,s[i]-'0');
		cout<<mx<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++)	
		s[n+i]=s[i];
		
	n*=2;
	for(int i=1;i<=n;i++)
		a[i]=s[i];
	calc_sa(n);
	calc_height(n);
	
	
	
	
	static pii bin[maxn*2];
	int sz=0;
	for(int i=1;i<=n;i++){
		if(i+len-1<=n)
			bin[++sz]=make_pair(i,i+len-1);
//		if(i+len-2<=n)
//			bin[++sz]=make_pair(i,i+len-2);
	}
	
	sort(bin+1,bin+1+sz,cmp);
	
//	cerr<<leq(4,5,2,3)<<endl;
	
/*	
	deb(test({2,3},2));
	
	return 0;
	for(int i=1;i<=sz;i++){
		deb(bin[i].L);
		deb(bin[i].R);
		deb(check(bin[i]));
	}
	
	
	return 0;
*/	
	int l=1,r=sz;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(bin[mid]))
			r=mid;
		else
			l=mid+1;
	}
	for(int i=bin[l].first;i<=bin[l].second;i++)
		putchar(s[i]);
	puts("");
		
	return 0;
}

#include<bits/stdc++.h>
#define deb(x) cerr<<#x" = "<<x<<endl;
#define rank adf__
using namespace std;
const int maxl=1e5+1e4+5;
const int maxn=maxl*2;
const int sep=10;
const int mo=2012;
int inv9;
int a[maxn],x[maxn],y[maxn],c[maxn],sa[maxn],rank[maxn],height[maxn];

void calc_sa(int n){
	int m=11,k=1;
	memset(c,0,sizeof(*c)*(m+1));
	for(int i=1;i<=n;i++)c[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=1;i<=n;i++)sa[c[x[i]]--]=i;
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
			if(max(sa[i],sa[i-1])+k>n||y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])
				++tot;
			x[sa[i]]=tot;
		}
		if(tot==n)break;else m=tot;
	}
}
void calc_height(int n){
	for(int i=1;i<=n;i++)rank[sa[i]]=i;
	for(int i=1;i<=n;i++){
		height[rank[i]]=max(0,height[rank[i-1]]-1);
		if(rank[i]==1)continue;
		int j=sa[rank[i]-1];
		while(max(i,j)+height[rank[i]]<=n&&a[i+height[rank[i]]]==a[j+height[rank[i]]])
			++height[rank[i]];
	}
}

int n;

char s[maxn];

int sum[maxn],h[maxn],h_l[maxn],nxt[maxn],ten[maxn];
int get(int l,int r){
	if(l>r)return 0;
	return (h[r]-h[l-1]*h_l[r-l+1]%mo+mo)%mo;
}
#define S(l,r) (sum[r]-sum[l-1]+mo)%mo

bool solve(){
	if(scanf("%d",&n)!=1||!n)
		return false;
	int m=0;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		int len=strlen(s+1);
		for(int j=1;j<=len;j++)
			a[++m]=s[j]-'0';
		a[++m]=sep;
	}
	
	calc_sa(m);
	calc_height(m);



	for(int i=1;i<=m;i++){
		sum[i]=(sum[i-1]+a[i])%mo;
		h[i]=(h[i-1]*10+a[i])%mo;	
	}
	for(int i=m;i>=1;i--){
		if(a[i]==sep)
			nxt[i]=i;
		else
			nxt[i]=nxt[i+1]; 
	}
	
	/*
	for(int i=1;i<=m;i++)
		printf("%d ",sa[i]);
	puts("");

	for(int i=1;i<=m;i++){
		printf("%d ",a[i]);
	}
	puts("");*/
	
	
	long long ans=0;
	
	for(int i=1;i<=m;i++){
		if(a[i]==0||a[i]==sep)continue;
		int st=i;
		int l=st+height[rank[i]];
		int r=min(nxt[l],nxt[st])-1;
		int len=r-l+1;	
		long long res=0;
//		deb(i);
//		deb(st);
//		deb(l);
//		deb(r);
		if(l>r)continue;
//		deb(get(l,r));
		
		res+=1ll*(ten[len+1]-10+mo)*inv9%mo*get(st,l-1)%mo;
		res+=1ll*(get(l,r)*10%mo-S(l,r)+mo)%mo*inv9%mo;
		
		res+=mo;
		res%=mo;
		
		ans+=res%mo;
		ans%=mo;
//		deb(res);
	}
	ans%=mo;
	while(ans<0)ans+=mo;
	ans%=mo;
	
	printf("%lld\n",ans);
	return true;
}

int main(){
	h_l[0]=1;
	ten[0]=1;
	for(int i=1;i<maxn;i++){
		h_l[i]=h_l[i-1]*10%mo;
		ten[i]=ten[i-1]*10%mo;
	}
	for(int i=1;i<=2012;i++){
		if(i*9%2012==1){
			inv9=i;
			break;
		}
	}

//	int T;cin>>T;
	while(solve());
	
	return 0;
}

#include<bits/stdc++.h>
#define deb(x) cerr<< #x" = "<< x<<endl
using namespace std;
const int maxn=1e5+5;
const int BIT=19;
typedef long long LL;
int n,q;
int f[maxn][BIT],g[maxn][BIT];
int dw,pw,W;
int a[maxn];

LL sum[maxn];

LL cost(int l,int r){
	return sum[r]-sum[l-1]+(r-l);
}

int nxt(int x,int d){
	if(a[x]>d)return x;
	int l=x,r=n+1;
	while(l<r){
		int mid=(l+r)>>1;
		if(cost(x,mid)<=d)
			l=mid+1;
		else
			r=mid;
	}
	return l;
}

int jumpF(int x,int h){
	for(int j=0;j<BIT;j++)if(h>>j&1)
		x=f[x][j];
	return x;
}
int jumpG(int x,int h){
	for(int j=0;j<BIT;j++)if(h>>j&1)
		x=g[x][j];
	return x;
}
int reachG(int x,int ed){
	int ans=0;
	if(x==ed)return 0;
	for(int i=BIT-1;i>=0;i--){
		if(g[x][i]<ed){
			x=g[x][i];
			ans+=(1<<i);
		}
	}
	return ans;
}

int Q(int x,int h){
	int cur=1,nx;
	nx=jumpG(cur,x-1);
	if(nx==n+1){
		return reachG(cur,n+1)+h+1;
	}else cur=nx;
	
	nx=jumpF(cur,h);
	if(nx==n+1){
		return x+h-1;
	}else cur=nx;
	
	return cur+reachG(cur,n+1)+1;
}

void solve(){
	scanf("%d%d%d%d",&n,&W,&pw,&dw);

	for(int i=1;i<=n;i++){
		for(int j=0;j<BIT;j++){
			f[i][j]=0;
			g[i][j]=0;
		}
	}
	
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int j=0;j<BIT;j++){
		f[n+1][j]=n+1;
		g[n+1][j]=n+1;
	}
	
	for(int i=1;i<=n;i++){
		f[i][0]=nxt(nxt(i,dw),W-pw-dw);
		g[i][0]=nxt(i,W);
	}
	for(int j=1;j<BIT;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
			g[i][j]=g[g[i][j-1]][j-1];
		}
	}
	
	scanf("%d",&q);
	while(q--){
		int x,h;
		scanf("%d%d",&x,&h);
		printf("%d\n",Q(x,h));
	}
	
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}


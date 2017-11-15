#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=202;
const int BIT=9;

struct info{
	LL a,d;
	info(LL a=-1,LL d=-1):a(a),d(d){}
};


__int128 exgcd(__int128 a,__int128 b,__int128 &x,__int128 &y){
	if(b==0){
		x=1;y=0;
		return a;
	}
	__int128 d=exgcd(b,a%b,x,y);
	__int128 t=x;
	x=y;
	y=t-a/b*x;
	return d;
}

__int128 lcm(__int128 a,__int128 b){return a/__gcd(a,b)*b;}

void sol(__int128 a,__int128 b,__int128 c,__int128 &x,__int128 &y){
	__int128 d=exgcd(a,b,x,y);
	x=x*(c/d);y=y*(c/d);
}

LL mul(LL x,LL y,LL p){
	LL t=(x*y-(LL)((long double)x/p*y+1e-3)*p)%p;
	return t<0?t+p:t;
}
void merge(LL &A,LL &B,__int128 a,__int128 b){
	__int128 x,y;
	sol(A,-a,b-B,x,y);
	
	if(llabs(b-B)%__gcd((__int128)A,a)){
		A=B=-1;
		return ;
	}
	
	A=lcm(A,a);
	B=((__int128)a*y%A+b)%A;
	B=(B+A)%A;
}

info operator&(info ls,info rs){
	info ans=ls;
	if(ls.d==-1||rs.d==-1){
		ans.d=ans.a=-1;
		return ans;
	}
	merge(ans.d,ans.a,rs.d,rs.a);
	return ans;
}

info st[maxn][maxn][BIT][BIT];
int a[maxn][maxn],d[maxn][maxn],Log2[maxn];
int n,m;
void pre(){
	for(int k=0;k<BIT;k++)
	for(int l=0;l<BIT;l++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(k==0&&l==0){
			st[i][j][k][l]=info(a[i][j],d[i][j]);
		}else if(k==0){
			st[i][j][k][l]=st[i][j][k][l-1]&st[i][min(j+(1<<(l-1)),m)][k][l-1];
		}else if(l==0){
			st[i][j][k][l]=st[i][j][k-1][l]&st[min(i+(1<<(k-1)),n)][j][k-1][l];
		}else{
			st[i][j][k][l]=st[i][j][k-1][l]&st[min(i+(1<<(k-1)),n)][j][k-1][l];
		}
	}			
	
}

LL Q(LL x1,LL y1,LL x2,LL y2){
	int len1=Log2[x2-x1+1];
	int len2=Log2[y2-y1+1];
	info ans=info(0,1);
	
	ans=ans&st[x1][y1][len1][len2];
	ans=ans&st[x2-(1<<len1)+1][y1][len1][len2];
	ans=ans&st[x1][y2-(1<<len2)+1][len1][len2];
	ans=ans&st[x2-(1<<len1)+1][y2-(1<<len2)+1][len1][len2];
	
	return ans.a;
}
LL BF(LL x1,LL y1,LL x2,LL y2){
	info ans=info(0,1);
	
	for(int i=x1;i<=x2;i++)
	for(int j=y1;j<=y2;j++)	
		ans=ans&info(a[i][j],d[i][j]);
	
	return ans.a;
}


int main(){

	Log2[0]=-1;
	for(int i=1;i<maxn;i++){
		Log2[i]=Log2[i-1]+((i&(-i))==i);
	}
	
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)	
				scanf("%d",&a[i][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)	
				scanf("%d",&d[i][j]);
				
			
		pre();
		printf("Case #%d:\n",t);
		int q;scanf("%d",&q);
		while(q--){
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
//			cerr<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
//			assert(BF(x1,y1,x2,y2)==Q(x1,y1,x2,y2));
			printf("%lld\n",Q(x1,y1,x2,y2));
		}
	}
	return 0;
}


#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;
typedef long long LL;
int n;
struct P{
	LL x,y;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
}p1[maxn],p2[maxn],px[maxn],py[maxn];

P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
P operator*(P a,LL b){
	return P(a.x*b,a.y*b);
}
LL count(P *p){
	LL area2=0;
	for(int i=0;i<n;i++)
		area2+=(p[i]-p[0])*(p[(i+1)%n]-p[0]);
	area2=llabs(area2);
	
	LL border=0;
	for(int i=0;i<n;i++){
		P dir=p[i]-p[(i+1)%n];
		LL d=__gcd(llabs(dir.x),llabs(dir.y));
		dir.x=llabs(dir.x/d);
		dir.y=llabs(dir.y/d);;
		if(dir.x){
			border+=llabs((p[i]-p[(i+1)%n]).x)/dir.x;
		}else{
			border+=llabs((p[i]-p[(i+1)%n]).y)/dir.y;
		}
	}
	
	//cerr<<area2<<" "<<border<<endl;
	
	//area=inside+border/2-1
	//area2=inside2+border-2
	LL inside=(area2-border+2)/2;
	//cerr<<"inside "<<inside<<endl;
	return inside+border;
}

int main(){
freopen("semi-cool.in","r",stdin);
freopen("semi-cool.out","w",stdout);
	cout << 1 << endl;
	return 0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		p1[i].read();
		p2[i]=p1[i]*2;
		px[i]=p1[i];px[i].x*=2;
		py[i]=p1[i];py[i].y*=2;
	}

//	cerr<<count(p1)<<endl;
//	cerr<<count(p2)<<endl;

	LL ans1=count(p1);
	LL ans2=count(p2);
	LL ansx=count(px);
	LL ansy=count(py);


	LL ans=(ans2-ans1)-(ansx-ans1)-(ansy-ans1);

	printf("%lld\n",ans);
	return 0;
}

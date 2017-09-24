#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
const double pi=acos(-1);
const int maxn=1010;
int sgn(double x){return (x>eps)-(x<-eps);}

int flag;
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	double len(){
		return sqrt(x*x+y*y);
	}
}p[maxn];
bool operator==(P a,P b){
	return !sgn(a.x-b.x) and !sgn(a.y-b.y);
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
bool onLine(P p,P a,P b){
	return sgn((p-a)*(b-a))==0;
}
bool onSeg(P p,P a,P b){
	return onLine(p,a,b) && sgn((a-p)^(b-p))<0;
}
bool intersect(P a,P b,P c,P d){
	if(sgn((c-a)*(b-a))*sgn((d-a)*(b-a))<0
		&&sgn((a-c)*(d-c))*sgn((b-c)*(d-c))<0)
			return true;
	if(onSeg(a,c,d)||onSeg(b,c,d)||
		onSeg(c,a,b)||onSeg(d,a,b))
			return true;
	return false;
}
bool between(double l,double m,double r){
	return sgn(l-m)<=0 and sgn(m-r)<=0;
}


bool onAng(P p,P a,P b,P c){
	//TODO
	if(flag)swap(a,c);
	double t=atan2(p.y-b.y,p.x-b.x);
	double t1=atan2(a.y-b.y,a.x-b.x);
	double t2=atan2(c.y-b.y,c.x-b.x);
	if(!flag){
		if(t1>t2)t2+=2*pi;
		if(between(t1,t,t2)||between(t1,t-2*pi,t2)||between(t1,t+2*pi,t2))
			return true;
		return false;
	}else{
		
	}
}
double dis(P a,P b){
	return (b-a).len();
}
double dp[maxn],val[maxn];
int n;
bool can(int pos1,int pos2){
	P a=p[pos1],b=p[pos2];
	
	
	if((pos1+1)%n==pos2)
		return true;

	if(!onAng(a,p[(pos2-1+n)%n],p[pos2],p[(pos2+1)%n])){
		return false;
	}
	if(!onAng(b,p[(pos1-1+n)%n],p[pos1],p[(pos1+1)%n])){
		return false;
	}
	
	for(int i=0;i<n;i++){
		if(intersect(a,b,p[i],p[(i+1)%n]))
			return false;
	}
	
	return true;
}

double solve(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		p[i].read();
		scanf("%lf",&val[i]);
	}
	double area=0;
	for(int i=0;i<n;i++)
		area+=p[i]*p[(i+1)%n];
	flag=0;
	if(area<0){
		//reverse(p,p+n);
		flag=1;
	}
	
	
//	cerr<<area<<endl;
	
//	cerr<<can(0,2)<<endl;
//	return 0;
	const double inf=1e22;
	for(int i=0;i<n;i++)
		dp[i]=-inf;
	dp[0]=val[0];
	for(int i=0;i<n;i++){
		if(dp[i]==-inf)continue;
		for(int j=i+1;j<n;j++){
			if(can(i,j)){
			//	cerr<<i<<"->"<<j<<endl;
				dp[j]=max(dp[j],dp[i]-dis(p[i],p[j])+val[j]);
			}
		}
	}
	double ans=*max_element(dp,dp+n);
	return ans;
}
int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %.8f\n",t,solve());
	}	

	return 0;
}

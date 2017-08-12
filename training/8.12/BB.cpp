#include<bits/stdc++.h>
using namespace std;
typedef long double LD;
const LD eps=1e-13;
const LD pi=acos(-1);
int sgn(LD x){
	return (x>eps)-(x<-eps);
}
struct P{
	LD x,y;
	P(){}
	P(LD _x,LD _y):x(_x),y(_y){}
	void read(){
		double tx,ty;
		scanf("%lf%lf",&tx,&ty);
		x=tx;y=ty;
	}
	P rot(LD rad){
		return P(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
	}
	LD len(){
		return sqrt(x*x+y*y);
	}
}p,q;
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LD dis(P a,P b){
	return (b-a).len();
}
LD r;
LD sqr(LD x){return x*x;}
LD mysqrt(LD x){
	if(x < 0)return 0.0;
	return sqrt(x);
}

LD calc(LD x){
	if (x > 1.0) {
		return dis(P(0, r), p) + dis(P(0, r), q);
	}
	if (x < -1.0) {
		return dis(P(0, -r), p) + dis(P(0, -r), q);
	}
	LD y = mysqrt(1.0 - x * x);
	//printf("x and y: %.10f %.10f\n", (double)(x * r), (double)(y * r));
	x *= r;
	y *= r;
	swap(x, y);
	return dis(P(x, y), p) + dis(P(x, y), q);
}


bool solve(LD A,LD B,LD C,LD &x1,LD &x2){
	LD delta=B*B-4*A*C;
	if(sgn(delta)<0)return false;
	
	x1=(-B+mysqrt(delta))/2/A;
	x2=(-B-mysqrt(delta))/2/A;
	return true;
}

void solve(){
	double tr;
	scanf("%lf",&tr);
	r=tr;
	p.read();q.read();
	P O(0,0);
	LD d=dis(p,O);
	if(!sgn(d)){
		printf("%.10f\n",(double)r*2);
		return ;
	}
	
	LD l=dis(p,q);
	LD a=l/2;
	LD b=mysqrt(sqr(d)-sqr(l/2));
	q=P(a,b);	
	p=P(-a,b);	
	
	LD x1,x2,A,B,C;
	
	A=(sqr(a)+sqr(b))*r;
	B=-b*(sqr(a)+sqr(b)+sqr(r));
	C=r*sqr(b);
	
	LD ans=calc(0.0);
	if(solve(A,B,C,x1,x2)){ //x1,x2without r
	//cout << (double)x1 << " " << (double)x2 << endl;
	//printf("%.10f %.10f\n", (double)x1, (double)x2);
		ans=min(ans,calc(x1));	
		ans=min(ans,calc(x2));	
	}
	
	
	printf("%.10f\n",(double)ans);
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();

	return 0;
}

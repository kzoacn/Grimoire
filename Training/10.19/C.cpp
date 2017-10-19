#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
const double pi=acos(-1);
int sgn(double x){return (x>eps)-(x<-eps);}

struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	P rot(double rad){//counter-clock
		return P(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
	}
	double len(){
		return sqrt(x*x+y*y);
	}
	void read(){scanf("%lf%lf",&x,&y);}
};
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



int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		P pivc,pivo,p[4],O;
		double w,h;
		scanf("%lf%lf",&w,&h);
		pivc.read();
		pivo.read();
		double alpha;scanf("%lf",&alpha);
		double _alp=alpha;
		alpha=alpha/360*2*pi;
		double s;scanf("%lf",&s);
		
		p[0]=pivo-pivc;
		p[1]=p[0]+P(w,0);
		p[2]=p[1]+P(0,h);
		p[3]=p[2]+P(-w,0);

		for(int i=0;i<4;i++){
			p[i]=pivo+(p[i]-pivo).rot(alpha);
		}
		for(int i=0;i<4;i++){
			p[i]=pivo+(p[i]-pivo)*s;
		}
		
		O=(p[0]+p[2])/2;
		
		for(int i=0;i<4;i++){
			p[i]=O+(p[i]-O).rot(-alpha);
		}
		
		printf(".item%d {width: %.1fpx; height: %.1fpx; left: %.1fpx; top: %.1fpx; transform: rotate(%.1fdeg); }\n",
				t,(p[0]-p[1]).len(),(p[0]-p[3]).len(),p[0].x,p[0].y,_alp);
	}
	return 0;
}

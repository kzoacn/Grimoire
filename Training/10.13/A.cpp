#include<bits/stdc++.h>
#define deb(x) cerr<<#x" = "<<x<<endl
using namespace std;
const int maxn=44;
const double eps=1e-9;
int sgn(double x,double eps=::eps){return (x>eps)-(x<-eps);}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	double len2(){return (x*x+y*y);}
	P turn90(){return P(-y,x);}
	P norm(){return P(x/len(),y/len());}
	
	void print(){
		printf("(%.4f,%.4f)\n",x,y);
	}
};
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 && sgn(a.y-b.y)==0;
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
struct C{
	P o;
	double r;
};

bool operator==(C a,C b){
	return a.o==b.o && sgn(a.r-b.r)==0;
}

double fix(double x){
	if(x<0)return 0;
	return x;
}
bool intersect(C a,C b,P &p1,P &p2){

	if(a==b){
		p1=p2=a.o+P(a.r,0);
		return true;
	}

	double s1=(a.o-b.o).len();
	if(sgn(s1-a.r-b.r,1e-5)>0||sgn(s1-fabs(a.r-b.r),1e-5)<0)
		return false;
	double s2=(a.r*a.r-b.r*b.r)/s1;
	double aa=(s1+s2)/2,bb=(s1-s2)/2;
	P o=(b.o-a.o)*(aa/(aa+bb))+a.o;
	P delta=(b.o-a.o).norm().turn90()*sqrt(fix(a.r*a.r-aa*aa));
	p1=o+delta;
	p2=o-delta;
	return true;
}
int n;
double l[maxn],rmin[maxn],rmax[maxn];
P tar[maxn];

bool check(){
	tar[0]=P(0,0);	
	bool flag=true;
	for(int i=1;i<=n;i++){
		double d=(tar[i]-tar[i-1]).len();
		//cerr<<d<<" "<<l[i]<<" "<<tar[i].len()<<endl;
		if(fabs(d-l[i])>1e-3||isnan(tar[i].x))
			flag=false;
	}
	return flag;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i];
	}
	cin>>tar[n].x>>tar[n].y;

	rmin[1]=rmax[1]=l[1];
	for(int i=2;i<=n;i++){
		if(sgn(l[i]-rmin[i-1])<=0){
			rmin[i]=rmin[i-1]-l[i];
		}else{
			double lef=rmin[i-1]-l[i];
			double rig=rmax[i-1]-l[i];
			if(sgn(lef)<=0&&sgn(rig)>=0)
				rmin[i]=0;
			else{
				rmin[i]=min(fabs(lef),fabs(rig));
			}
		}
		rmax[i]=rmax[i-1]+l[i];
		
	}
	/*for(int i=1;i<=n;i++){
		deb(i);
		deb(rmin[i]);
		deb(rmax[i]);
	}*/
	
	double d=tar[n].len();
	
	//deb(d);
	
	if(sgn(rmin[n]-d)>0||sgn(d-rmax[n])>0){
	
		if(sgn(d-rmax[n])>0){
			tar[n]=tar[n]*(rmax[n]/tar[n].len());
		}else{
			if(sgn(tar[n].x)==0&&sgn(tar[n].y)==0){
				tar[n]=P(rmin[n],0);
			}else{
				tar[n]=tar[n]*(rmin[n]/tar[n].len());
			}
		}
	}
	
	for(int i=n-1;i>=1;i--){
		C c1,c2;
		c1.o=P(0,0);
		c2.o=tar[i+1];
		
		P p1,p2;
		c1.r=(rmax[i]+rmin[i])/2;
		c2.r=l[i+1];
		
		
		if(intersect(c1,c2,p1,p2)){
			tar[i]=p1;
	//		cerr<<"1"<<endl;
			continue;
		}
		
		c1.r=rmax[i];
		c2.r=l[i+1];
		
		if(intersect(c1,c2,p1,p2)){
			tar[i]=p1;
//			cerr<<"2"<<endl;
			continue;
		}
		
		
		c1.r=rmin[i];
		c2.r=l[i+1];
		
		if(sgn(rmin[i])!=0){
			if(intersect(c1,c2,p1,p2)){
				tar[i]=p1;
	//		cerr<<"3"<<endl;
				continue;
			}
		}else{
			if(sgn(rmin[i]-c2.r)==0){
				tar[i]=P(0,0);
				continue;
			}
		}
		
		tar[i]=tar[i+1]+P(l[i+1],0);
		
		/*if(intersect(c1,c2,p1,p2)){
			tar[i]=p1;
		}else{
			P dir;
			if(sgn(tar[i+1].x)==0&&sgn(tar[i+1].y)==0){
				dir=P(1,0);
			}else{
				if(tar[i+1].len()>(rmin[i]+rmax[i])/2){
					dir=(tar[i+1]*(-1)).norm();
				}else{
					dir=tar[i+1].norm();
				}
			}
			
			tar[i]=tar[i+1]+dir*l[i+1];
		}*/
	}
//	for(int i=1;i<=n;i++)
//		cerr<<tar[i].len()<<" ";cerr<<endl;	
	
	for(int i=1;i<=n;i++)
		printf("%.10f %.10f\n",tar[i].x,tar[i].y);
	assert(check());
	
	
	return 0;
}

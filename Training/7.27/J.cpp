#include<bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

using namespace std;
const int maxn=505;
const double eps=1e-8;
const double pi=acos(-1);


int n;

__advance double form(double x){
	while(x>=2*pi)x-=2*pi;
	while(x<0)x+=2*pi;
	return x;
}
__advance int sgn(double x){return (x>eps)-(x<-eps);}
__advance double sqr(double x){return x*x;}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	__advance double len2(){return x*x+y*y;}
	__advance double len(){return sqrt(len2());}
	__advance P turn90(){
		return P(-y,x);
	}
	__advance P norm(){
		return P(x/len(),y/len());
	}
	__advance P rot(double rad){
		return P(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
	}
	__advance void read(){
		scanf("%lf%lf",&x,&y);
	}
	__advance void print(char c='\n'){
		printf("(%.4f,%.4f)%c",x,y,c);
	}
};
__advance bool operator<(P a,P b){
	return sgn(a.x-b.x) ? a.x<b.x : a.y<b.y;
}
__advance bool operator==(P a,P b){
	return !sgn(a.x-b.x) && !sgn(a.y-b.y);
}
__advance P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
__advance P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
__advance double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
__advance double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
__advance P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
__advance P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
__advance double det(P a,P b,P c){
	return (b-a)*(c-a);
}
__advance double dis(P a,P b){
	return (b-a).len();
}
struct C{
	P o;
	double r;
	__advance P at(double rad){
		return o+P(r,0).rot(rad);
	}
	__advance double ang(P p){
		double t=atan2(p.y-o.y,p.x-o.x);
		return form(t);
	}
};
__advance bool operator==(C a,C b){
	return !sgn(a.r-b.r) && a.o==b.o;
}
__advance bool inC(P p,C c,bool strict){
	if(strict){
		return sgn(dis(p,c.o)-c.r)<0;
	}else{
		return sgn(dis(p,c.o)-c.r)<=0;
	}
}
__advance double fix(double x){return sgn(x)?x:0;}
__advance bool intersect(C a,C b,P &p1,P &p2){
	double s1=(a.o-b.o).len();
	if(sgn(s1-a.r-b.r)>0||sgn(s1-fabs(a.r-b.r))<0)
		return false;
	double s2=(sqr(a.r)-sqr(b.r))/s1;
	double aa=(s1+s2)/2,bb=(s1-s2)/2;
	P o=(b.o-a.o)*(aa/(aa+bb))+a.o;
	P delta=(b.o-a.o).norm().turn90()*sqrt(fix(sqr(a.r)-sqr(aa)));
	p1=o+delta;
	p2=o-delta;
	return true;
}
struct S{
	C c1,c2;
	__advance void read(){
		P o;o.read();
		double D,d;scanf("%lf%lf",&D,&d);
		c1.o=o;c1.r=D+d;
		c2.o=o;c2.r=max(D-d,0.0);
	}
	S(){}
	S(P o,double r1,double r2){
		c1.o=o;c1.r=r1;
		c2.o=o;c2.r=r2;
	}
	__advance void print(char c='\n'){
		c1.o.print(' ');
		printf("%.5f %.5f\n",c1.r,c2.r);
	}
}s[maxn];

__advance bool operator<(S s1,S s2){
	return s1.c1.o<s2.c1.o;
}

__advance bool inS(P p,S s,bool strict){
	if(strict){
		if(inC(p,s.c1,true)&&!inC(p,s.c2,false))
			return true;
		return false;
	}else{
		if(inC(p,s.c1,false)&&!inC(p,s.c2,true))
			return true;
		return false;
	}
}
__advance bool checkin(P p,int id){
	for(register int i=1;i<=n;i++)if(i!=id)
		if(inS(p,s[i],true))
			return true;
	return false;
}
__advance double calc(int id){
	double ans=0;
	vector<double>ang1;
	vector<double>ang2;
	ang1.push_back(0);ang1.push_back(pi);
	ang2.push_back(0);ang2.push_back(pi);
	S ss=s[id];
	for(int i=1;i<=n;i++)if(i!=id){
		register P p1,p2;
		if(intersect(ss.c1,s[i].c1,p1,p2)){
			ang1.push_back(form(ss.c1.ang(p1)));
			
			ang1.push_back(form(ss.c1.ang(p2)));
		}
		if(sgn(s[i].c2.r)&&intersect(ss.c1,s[i].c2,p1,p2)){
			
			ang1.push_back(form(ss.c1.ang(p1)));
			
			ang1.push_back(form(ss.c1.ang(p2)));
		}
		if(sgn(ss.c2.r)&&intersect(ss.c2,s[i].c1,p1,p2)){
			ang2.push_back(form(ss.c2.ang(p1)));
			ang2.push_back(form(ss.c2.ang(p2)));
		}
		if(sgn(ss.c2.r)&&sgn(s[i].c2.r)&&intersect(ss.c2,s[i].c2,p1,p2)){
			ang2.push_back(form(ss.c2.ang(p1)));
			ang2.push_back(form(ss.c2.ang(p2)));
			if(isnan(ss.c2.ang(p2))){
				ss.print();
				s[i].print();
				p2.print();
				exit(0);
			}
		}
	}
	sort(ang1.begin(),ang1.end());
	sort(ang2.begin(),ang2.end());
	for(int i=0;i<ang1.size();i++){
		register double t1=ang1[i],t2=(i+1==ang1.size()?ang1[0]+2*pi:ang1[i+1]);
		P p=ss.c1.at((t1+t2)/2);
		if(!checkin(p,id)){
			double r=ss.c1.r,x0=ss.c1.o.x,y0=ss.c1.o.y;
			ans+=(r*r*(t2-t1)+r*x0*(sin(t2)-sin(t1))-r*y0*(cos(t2)-cos(t1)))/2;
		}
	}
	
	for(int i=0;i<ang2.size();i++){
		register double t1=ang2[i],t2=(i+1==ang2.size()?ang2[0]+2*pi:ang2[i+1]);
		if(isnan(t1)){
			cerr<<i<<" "<<id<<endl;
			cerr<<t1<<endl;
			exit(0);
		}
			
		P p=ss.c2.at((t1+t2)/2);
		if(!checkin(p,id)){
			double r=ss.c2.r,x0=ss.c2.o.x,y0=ss.c2.o.y;
			ans-=(r*r*(t2-t1)+r*x0*(sin(t2)-sin(t1))-r*y0*(cos(t2)-cos(t1)))/2;
		}
	}
	return ans;
}

bool in(pair<double,double>b,pair<double,double>a){
	return a.first-eps<=b.first && b.second <=a.second+eps;
}
bool is(pair<double,double>b,pair<double,double>a){
	return in(make_pair(b.first,b.first),a) || in(make_pair(b.second,b.second),a);
}

__advance double solve(){
	double ans=0;
	scanf("%d",&n);
//	cerr<<n<<endl;
	for(int i=1;i<=n;i++){
		s[i].read();
//		s[i].print();
	}
	sort(s+1,s+1+n);
	
	int nn=0;
	static S nS[maxn];
	for(int i=1,j;i<=n;i=j){
		j=i;
		while(j<=n&&s[i].c1.o==s[j].c1.o)j++;
		vector<pair<double,int> >vec;
		vector<pair<double,double> >tmp,tmp2;
		
		
		for(int k=i;k<j;k++){
			tmp.push_back({s[k].c2.r,-s[k].c1.r});
		}
//		if(j-i>1){cerr<<"merge"<<endl;}
		for(int k=0;k<tmp.size();k++){
			tmp[k].second*=-1;
		
		}
		sort(tmp.begin(),tmp.end());
		tmp2.push_back(tmp[0]);
		
		for(int k=0;k<tmp.size();k++){
			if(j-i>1){
			//	fprintf(stderr,"[%.3f,%.3f]\n",tmp[k].first,tmp[k].second);		
			}
		
		}
		for(int k=1;k<tmp.size();k++){
			if(in(tmp[k],tmp2.back())){
			
			}else if(is(tmp[k],tmp2.back())) {
				tmp2.back().second=max(tmp2.back().second,tmp[k].second);
			}else tmp2.push_back(tmp[k]);
		}
//		if(j-i>1){cerr<<"to"<<endl;}
		for(int k=0;k<tmp2.size();k++){
			++nn;
			nS[nn]=S(s[i].c1.o,tmp2[k].second,tmp2[k].first);
			if(j-i>1){
//				fprintf(stderr,"[%.3f,%.3f]\n",tmp2[k].first,tmp2[k].second);		
			}
		}
	}
	//exit(0);
	n=nn;
//	cerr<<n<<endl;
	for(int i=1;i<=n;i++){
		s[i]=nS[i];
//		s[i].print();
	}
	
	random_shuffle(s+1,s+1+n);
	
	for(int i=1;i<=n;i++){
		ans+=calc(i);
	}
	
	return ans;
}

__advance int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case %d: %.6f\n",t,solve());
	}
	return 0;
}

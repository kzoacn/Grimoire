#include<bits/stdc++.h>
#define deb(x) cerr<<#x" = "<<x<<endl
using namespace std;
const double eps=1e-9;
const double pi=acos(-1);
int sgn(double x){return (x>eps)-(x<-eps);}
const int maxn=1010;
int n;
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len2(){return x*x+y*y;}
	double len(){return sqrt(x*x+y*y);}
	double ang(){return atan2(y,x);}
	P norm(){return P(x/len(),y/len());}	
	P turn90(){return P(-y,x);}
	void read(){scanf("%lf%lf",&x,&y);}
	P rot(double rad){
		return P(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
	}
	
	void print(){
		printf("(%.3f,%.3f)\n",x,y);
	}
};
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double dis(P a,P b){return (b-a).len();}
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
struct L{
	P a,b;
	L(){}
	L(P _a,P _b):a(_a),b(_b){}
	P v(){return b-a;}
};


double dis(P p,L l){
	return fabs((p-l.a)*l.v())/l.v().len();
}
struct C{
	P o;
	double r;
	C(){}
	C(P _o,double _r):o(_o),r(_r){}
	void read(){
		o.read();
		scanf("%lf",&r);
	}
}c[maxn];



double fix(double x){return x<0?0:x;}
bool tang(C c,P p0,P &p1,P &p2){
	double x=(p0-c.o).len2(),d=x-c.r*c.r;
	if(d<eps)return false;
	P p=(p0-c.o)*(c.r*c.r/x);
	P delta=((p0-c.o)*(-c.r*sqrt(d)/x)).turn90();
	p1=c.o+p+delta;
	p2=c.o+p-delta;
	return true;
}

vector<L>extan(C c1,C c2){
	vector<L>ret;
	if(sgn(c1.r-c2.r)==0){
		P dir=c2.o-c1.o;
		dir=(dir*(c1.r/dir.len())).turn90();
		ret.push_back(L(c1.o+dir,c2.o+dir));
		ret.push_back(L(c1.o-dir,c2.o-dir));
	}else{
		P p=(c1.o*-c2.r+c2.o*c1.r)/(c1.r-c2.r);
		P p1,p2,q1,q2;
		if(tang(c1,p,p1,p2)&&tang(c2,p,q1,q2)){
			if(c1.r<c2.r)swap(p1,p2),swap(q1,q2);
			ret.push_back(L(p1,q1));
			ret.push_back(L(p2,q2));
		}
	}
	return ret;
}
vector<L>intan(C c1,C c2){
	vector<L>ret;
	P p=(c1.o*c2.r+c2.o*c1.r)/(c1.r+c2.r);
	P p1,p2,q1,q2;
	if(tang(c1,p,p1,p2)&&tang(c2,p,q1,q2)){
		ret.push_back(L(p1,q1));
		ret.push_back(L(p2,q2));
	}
	return ret;
}

int skip[maxn];


int calc(int pos){
	for(int i=1;i<=n;i++)skip[i]=0;
	
	int ans=1;
	
	set<int>S;
	
	vector<pair<double,int> >vec;
	for(int i=1;i<=n;i++)if(i!=pos){
		if(sgn(c[i].r-c[pos].r)>=0 && sgn(dis(c[i].o,c[pos].o)-(c[i].r-c[pos].r))<=0){
			ans++;
			skip[i]=1;
			continue;
		}
		
		vector<L>tmp,in,out;
		in=intan(c[pos],c[i]);
		out=extan(c[pos],c[i]);
			
		if(out.size()){
			if(sgn(c[pos].r-c[i].r)>=0){
				vec.push_back({(out[0].a-c[pos].o).ang(),-i});
				vec.push_back({(out[1].a-c[pos].o).ang(),+i});
			}else{
				vec.push_back({(out[0].a-c[pos].o).ang(),+i});
				vec.push_back({(out[1].a-c[pos].o).ang(),-i});
			}
		}
		
		if(in.size()){
			vec.push_back({(in[0].a-c[pos].o).ang(),-i});
			vec.push_back({(in[1].a-c[pos].o).ang(),+i});
		}
		
		
	}
	if(vec.size()==0)
		return ans;
	
	
	int m=vec.size();
	for(int i=0;i<m;i++)
		vec.push_back({vec[i].first+2*pi,vec[i].second});
	
	sort(vec.begin(),vec.end(),[](pair<double,int>a,pair<double,int>b){
		return sgn(a.first-b.first) ?a.first<b.first : a.second>b.second;
	});
	
	double ang=-pi,mx=0;
	int st=0;	
	for(int i=0;i+1<m;i++){
		double tmp=(vec[i+1].first-vec[i].first);
		if(tmp>mx){
			mx=tmp;
			ang=(vec[i+1].first+vec[i].first)/2;
			st=i;
		}
	}
	P pt=c[pos].o+P(c[pos].r,0).rot(ang);
	L l=L(pt,pt+(pt-c[pos].o).turn90());
	int cur=0;
	for(int i=1;i<=n;i++)if(i!=pos){
		if(skip[i])continue;
		if(sgn(dis(c[i].o,l)-c[i].r)<=0){
			cur++;
			S.insert(i);
		}
	}
	int res=S.size()+ans;
	for(int i=(st+1)%vec.size();i<vec.size();i++){
	
		
		
		
		if(vec[i].second<0){
			S.erase(-vec[i].second);
		}else{
			S.insert(vec[i].second);
		}
		res=max(res,ans+(int)S.size());
	}
		
	return res;
}

int solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)c[i].read();
	int ans=0;
	
	//return calc(1);
	for(int i=1;i<=n;i++){
		ans=max(ans,calc(i));
	}	
	return ans;
		
}
int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}/*
pos = 1
i = 11
vec[i].first = 2.81984
vec[i].second = -3
2 3 4 
i = 12
vec[i].first = 3.50456
vec[i].second = 3
2 4 
i = 13
vec[i].first = 3.60524
vec[i].second = -4
2 3 4 
i = 14
vec[i].first = 4.06889
vec[i].second = 4
2 3 
i = 15
vec[i].first = 4.71239
vec[i].second = -2
2 3 4 
i = 16
vec[i].first = 5.00214
vec[i].second = 2
3 4 
i = 17
vec[i].first = 5.27672
vec[i].second = -3
2 3 4 
i = 18
vec[i].first = 5.96143
vec[i].second = 3
2 4 
i = 19
vec[i].first = 6.28319
vec[i].second = -4
2 3 4 
i = 20
vec[i].first = 6.74683
vec[i].second = 4
2 3 
i = 21
vec[i].first = 7.56423
vec[i].second = -2
2 3 4 
i = 22
vec[i].first = 7.85398
vec[i].second = 2
3 4 
i = 23
vec[i].first = 9.10303
vec[i].second = -3
2 3 4 
Case #1: 0

*/

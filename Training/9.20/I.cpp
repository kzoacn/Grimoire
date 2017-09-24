#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
const int inf=1e9;
const double eps=1e-9;
const double pi=acos(-1);
int sgn(double x){return (x>eps)-(x<-eps);}


double fix(double x){
	while(x<0)x+=2*pi;
	while(x>2*pi)x-=2*pi;
	return x;
}

struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len2(){return x*x+y*y;}
	double len(){return sqrt(len2());}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	P turn90(){
		return P(-y,x);
	}
}p[maxn];
int n;
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 and sgn(a.y-b.y)==0;
}

P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double v[maxn];

struct C{
	P o;
	double r;
};
bool tang(C c,P p0,P &p1,P &p2){
	double x=(p0-c.o).len2(),d=x-c.r*c.r;
	if(d<eps)return false;
	P p=(p0-c.o)*(c.r*c.r/x);
	P delta=((p0-c.o)*(-c.r*sqrt(d)/x)).turn90();
	p1=c.o+p+delta;
	p2=c.o+p-delta;
	return true;
}

pair<double,double>seg[maxn];

typedef pair<double,double> pdd;
bool cmp(pdd a,pdd b){
	return sgn(a.first-b.first) ?a.first<b.first :a.second>b.second; 
}

int calc(pair<double,double>seg[],int sz,double len){
	sort(seg+1,seg+1+sz,cmp);
/*	
	for(int i=1;i<=sz;i++){
		pdd e=seg[i];	
		cerr<<e.first<<" "<<e.second<<endl;
	}
	cerr<<len<<endl;
	cerr<<endl;
*/
	if (sgn(seg[1].first)!=0)
		return inf;
	double rig=seg[1].second;
	int cnt=1;
	for(int i=2,j;i<=sz;i=j){
		j=i;
		double mx=-100;
		while(j<=sz&&sgn(seg[j].first-rig)<=0){
			mx=max(mx,seg[j].second);
			j++;
		}
		if(mx < -90)
			return inf;
		
		if(sgn(mx-rig)>0){
			rig=mx;
			cnt++;
		}else break;
	}
	
	//cerr<<"sd"<<rig<<endl;
	if(rig < len - eps) {
		return inf;
	}
	//cerr<<cnt<<endl;exit(0);
	return cnt;
}
void solve(){
	scanf("%d",&n);
	scanf("%lf",&v[0]);
	p[0].read();
	for(int i=1;i<=n;i++){
		scanf("%lf",&v[i]);
		p[i].read();
	}
	int sz=0;
	
	
	for(int i=1;i<=n;i++){
		if(sgn(v[i]-v[0])>0||p[i]==p[0]){
			puts("1");
			return ;
		}
		
		if(sgn(v[i]-v[0])==0){
			P dir=p[i]-p[0];
			P p1=dir.turn90()+p[0];
			P p2=dir.turn90().turn90().turn90()+p[0];
			double l=atan2(p2.y-p[0].y,p2.x-p[0].x);
			double r=atan2(p1.y-p[0].y,p1.x-p[0].x);
			if(l>r)r+=2*pi;
			if (l < -eps) {
				l += 2 * pi;
				r += 2 * pi;
			}
			seg[++sz]=make_pair(l,r);
		}else{
			P dir=p[i]-p[0];
			P pnear,pfar;
			pnear=p[0]+dir*(v[i]/(v[i]+v[0]));
			pfar=p[0]+dir*(v[i]/(v[0]-v[i]));
			C c;c.o=(pnear+pfar)/2;
			c.r=(pnear-pfar).len()/2;
			P p1,p2;
			if(tang(c,p[0],p1,p2)){
				double l=atan2(p2.y-p[0].y,p2.x-p[0].x);
				double r=atan2(p1.y-p[0].y,p1.x-p[0].x);
				if(l>r)r+=2*pi;
				if (l < -eps) {
					l += 2 * pi;
					r += 2 * pi;
				}
				seg[++sz]=make_pair(l,r);
			}
		}
	}
	
	if(n==1){
		cout<<0<<endl;
		return ;
	}
	
	static pair<double,double>tmp[maxn];
	
	int ans=inf;
	for(int i=1;i<=n;i++){
		int sz=0;
		double len=2*pi-(seg[i].second-seg[i].first);
		for(int j=1;j<=n;j++)if(i!=j){
			double l=seg[j].first-seg[i].second;
			double r=seg[j].second-seg[i].second;
			while(l<-eps){
				l+=2*pi;
				r+=2*pi;
			}
			while(l>=2*pi){
				l-=2*pi;
				r-=2*pi;
			}
			
			/*cerr<<l<<" "<<r<<endl;
			cerr<<len<<endl;*/
			if(l<len - eps){
//			cerr<<"here"<<endl;
				tmp[++sz] = make_pair(l, min(len, r));
			} else {
				if (r > 2 * pi + eps) {
					tmp[++sz] = make_pair(0, r - 2 * pi);
				}
			}
			continue;/*
			r=min(r,len);
			if(l<=r)
				tmp[++sz]=make_pair(l,r);*/
		}
		ans=min(ans,calc(tmp,sz,len)+1);
		
	}
	if(ans==inf){
		puts("0");
	}else
		printf("%d\n",ans);
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}

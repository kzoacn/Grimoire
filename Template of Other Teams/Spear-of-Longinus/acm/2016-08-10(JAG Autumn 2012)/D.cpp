//20:35 -> ??:??
//id:kzoacn
#include<bits/stdc++.h>
using namespace std;
const int maxn=20;
const double eps=1e-10;
int sgn(double x){return (x>eps)-(x<-eps);}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
}p[maxn];
typedef P V;
bool operator==(P a,P b){
	return !sgn(a.x-b.x) && !sgn(a.y-b.y);
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator*(P a,double p){
	return P(a.x*p,a.y*p);
}
P operator/(P a,double p){
	return P(a.x/p,a.y/p);
}
double dis(P a,P b){
	return (b-a).len();
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
bool para(V v1,V v2){
	return sgn(v1*v2)==0;
}
P intersect(P a,P b,P c,P d){
	double s1=det(a,b,c);
	double s2=det(a,b,d);
	return (d*s1-c*s2)/(s1-s2);
}
int n;
double w,h,r;
V v;

bool OnSeg(P p,P a,P b){
	return sgn((p-a)*(b-a))==0 and sgn((p-b)*(a-b))==0 and sgn((a-p)^(b-p))<=0;
}


//down:P(r,r)->P(w-r,r)
//up:P(r,h-r)->P(w-r,h-r)
//lef:P(r,r)->P(r,h-r)
//rig:P(w-r,r)->P(w-r,h-r)
pair<P,V> f(P p,V v){

	if(p==P(r,r) && sgn(v.x)<0 && sgn(v.y)<0)
		return make_pair(p,V(-v.x,-v.y));
	if(p==P(w-r,r) && sgn(v.x)>0 && sgn(v.y)<0)
		return make_pair(p,V(-v.x,-v.y));
	if(p==P(r,h-r) && sgn(v.x)<0 && sgn(v.y)>0)
		return make_pair(p,V(-v.x,-v.y));
	if(p==P(w-r,h-r) && sgn(v.x)>0 && sgn(v.y)>0)
		return make_pair(p,V(-v.x,-v.y));
	
	P ansp=P(-1,-1);
	
	if(!para(v,P(1,0))){
		if(!OnSeg(p,P(r,r),P(w-r,r))){
			P p1=intersect(p,p+v,P(r,r),P(w-r,r));
			if(OnSeg(p1,P(r,r),P(w-r,r)) and ((p1-p)^v)>0)
				return make_pair(p1,V(v.x,-v.y));
		}else if(sgn(v.y)<0) return make_pair(p,V(v.x,-v.y));
		if(!OnSeg(p,P(r,h-r),P(w-r,h-r))){
			P p2=intersect(p,p+v,P(r,h-r),P(w-r,h-r));
			if(OnSeg(p2,P(r,h-r),P(w-r,h-r)) and ((p2-p)^v)>0)
				return make_pair(p2,V(v.x,-v.y));
		}else if(sgn(v.y)>0) return make_pair(p,V(v.x,-v.y));
	}
	if(!para(v,P(0,1))){
		if(!OnSeg(p,P(r,r),P(r,h-r))){
			P p1=intersect(p,p+v,P(r,r),P(r,h-r));
			if(OnSeg(p1,P(r,r),P(r,h-r)) and ((p1-p)^v)>0)
				return make_pair(p1,V(-v.x,v.y));
		}else if(sgn(v.x)<0) return make_pair(p,V(-v.x,v.y));
		if(!OnSeg(p,P(w-r,r),P(w-r,h-r))){
			P p2=intersect(p,p+v,P(w-r,r),P(w-r,h-r));
			if(OnSeg(p2,P(w-r,r),P(w-r,h-r)) and ((p2-p)^v)>0)
				return make_pair(p2,V(-v.x,v.y));
		}else if(sgn(v.x)>0) return make_pair(p,V(-v.x,v.y));
	}
	
	//return make_pair(p,V(-v.x,-v.y));
	abort();
}
P project(P p,P a,P b){
	double t=((p-a)^(b-a))/(b-a).len();
	return a+(b-a)/(b-a).len()*t;
}
double dis(P p,P a,P b){
	P pr=project(p,a,b);
	if(OnSeg(pr,a,b))
		return dis(p,pr);
	else return min(dis(p,a),dis(p,b));
}
bool can(P a,P b,P p,double rest){

	double ans=0;
	P pr=project(p,a,b);

	double d=dis(p,pr);

	double l;
	if(sgn(2*r*2*r - d*d)>0)
		l=sqrt(2*r*2*r - d*d);
	else l=0;
	
	double d2=dis(a,p);

	ans=sqrt(d2*d2 - d*d)-l;

	return sgn(ans-rest)<0;
}
void deal(P a,P b,vector<int>&ans){
	for(int i=0;i<=5001;i++){
		P p=a+(b-a)*(i/5000.0);
		//printf("(%.3f,%.3f)\n",p.x,p.y);
		for(int j=0;j<ans.size();j++){
			if(dis(p,::p[ans[j]])+eps<2*r){
				ans[0]=ans[j];
				return ;
			}
		}
	}
	ans.clear();
}
int main(){	
	while(scanf("%d",&n)==1){
		if(!n)break;
		scanf("%lf%lf%lf%lf%lf",&w,&h,&r,&v.x,&v.y);
		for(int i=1;i<=n;i++){	
			scanf("%lf%lf",&p[i].x,&p[i].y);
		}
		
		P nowp=p[1];
		V nowv=v;
		
		double curlen=0;
		
		//cerr<<"zuikaku"<<endl;
		
		int TimeMachine = -1;
		//printf("(%.3f,%.3f),(%.3f,%.3f)\n",nowp.x,nowp.y,nowv.x,nowv.y);
		
		while(TimeMachine--){
			//cerr<<"bomb!"<<endl;
			P np,nv;
			
			
			pair<P,V>tmp=f(nowp,nowv);
			np=tmp.first;
			nv=tmp.second;
			//printf("(%.3f,%.3f),(%.3f,%.3f)\n",np.x,np.y,nv.x,nv.y);
			//cerr<< "One More Time One More Chance"<<endl;
			
			vector<int>ans;
			for(int i=2;i<=n;i++){
				if(dis(p[i],nowp,np)+eps<2*r){
					if(!can(nowp,np,p[i],10000-curlen))continue;
					//cerr << i << endl;
					ans.push_back(i);
				}
			}
			deal(nowp,np,ans);
			//return 0;
			
			
			if(!ans.empty()){
				printf("%d\n",ans.front());
				break;
			}
			//cerr << "kancolle" << endl;
			
			curlen+=dis(nowp,np);
			if(curlen>=10000){
				puts("-1");
				break;
			}
			nowp=np;
			nowv=nv;
			//cerr << "ha ? "<<endl;
		}
		
	}
	return 0;
}

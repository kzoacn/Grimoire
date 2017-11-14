int sgn(double x){return (x>eps)-(x<-eps);}
int sgn(double a,double b){return sgn(a-b);}
double sqr(double x){return x*x;}
struct P{
	double x,y;
	P(){}
	P(double x,double y):x(x),y(y){}
	double len2(){
		return sqr(x)+sqr(y);
	}
	double len(){
		return sqrt(len2());
	}
	void print(){
		printf("(%.3f,%.3f)\n",x,y);
	}
	P turn90(){return P(-y,x);}
	P norm(){return P(x/len(),y/len());}
};
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
double operator^(P a,P b){
	return a.x*b.x + a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y - a.y*b.x;
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
double dis(P a,P b){
	return (b-a).len();
}
double Area(vector<P>poly){
	double ans=0;
	for(int i=1;i<poly.size();i++)
		ans+=(poly[i]-poly[0])*(poly[(i+1)%poly.size()]-poly[0]);
	return fabs(ans)/2;
}
struct L{
	P a,b;
	L(){}
	L(P a,P b):a(a),b(b){}
	P v(){return b-a;}
};
bool onLine(P p,L l){
	return sgn((l.a-p)*(l.b-p))==0;
}
bool onSeg(P p,L s){
	return onLine(p,s) and sgn((s.b-s.a)^(p-s.a))>=0 and sgn((s.a-s.b)^(p-s.b))>=0;
}
bool parallel(L l1,L l2){
	return sgn(l1.v()*l2.v())==0;
}
P intersect(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}
P project(P p,L l){
	return l.a+l.v()*((p-l.a)^l.v())/l.v().len2();
}
double dis(P p,L l){
	return fabs((p-l.a)*l.v())/l.v().len();
}
int dir(P p,L l){
	int t=sgn((p-l.b)*(l.b-l.a));
	if(t<0)return -1;
	if(t>0)return 1;
	return 0;
}
bool segIntersect(L l1,L l2){//strictly
	if(dir(l2.a,l1)*dir(l2.b,l1)<0&&dir(l1.a,l2)*dir(l1.b,l2)<0)
		return true;
	return false;
}
bool in_tri(P pt,P *p){//change p
	if((p[1]-p[0])*(p[2]-p[0])<0)
		reverse(p,p+3);
	for(int i=0;i<3;i++){
		if(dir(pt,L(p[i],p[(i+1)%3]))==1)
			return false;
	}
	return true;
}

vector<P> convexCut(const vector<P>&ps, L l) { // 用半平面 l 的逆时针方向去切凸多边形
	vector<P> qs; 
	int n = ps.size();
	for (int i = 0; i < n; ++i) {
		Point p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = sgn(l.b * (p1 - l.a)), d2 = sign(l.b * (p2 - l.a));
		if (d1 >= 0) qs.push_back(p1);
		if (d1 * d2 < 0) qs.push_back(intersect(L(p1, p2 - p1), l));
	}
	return qs;
}

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
const double eps=1e-9;
const int maxn=5e4+4;
int sgn(double x){return (x>eps)-(x<-eps);}
int sgn(double x,double y){return sgn(x-y);}
struct P{
	double x,y;
	bool operator<(const P &oth)const{
		return sgn(x-oth.x)?x<oth.x:y<oth.y;
	}
	P(){}
	P(double _x,double _y){
		x=_x;y=_y;
	}
	double len2(){
		return x*x+y*y;
	}
	void print(){
		printf("%.3f %.3f",x,y);
	}
}p[maxn];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator/(P a,double p){
	return P(a.x/p,a.y/p);
}	
P operator*(P a,double p){
	return P(a.x*p,a.y*p);
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
int n;
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
vector<P> convex_hull(vector<P> &point){
	sort(point.begin(),point.end());
	vector<P>convex;
	{
		vector<P>stack;
		for(int i=0;i<point.size();++i){
			while(stack.size()>=2&&
				sgn(det(stack[stack.size()-2],stack.back(),point[i]))<=0){
					stack.pop_back();
			}
			stack.push_back(point[i]);
		}
		for(int i=0;i<stack.size();++i)
			convex.push_back(stack[i]);
	}
	{
		vector<P>stack;
		for(int i=(int)point.size()-1;i>=0;--i){
			while(stack.size()>=2&&
				sgn(det(stack[stack.size()-2],stack.back(),point[i]))<=0){
					stack.pop_back();
			}
			stack.push_back(point[i]);
		}
		for(int i=1;i+1<stack.size();++i)
			convex.push_back(stack[i]);
	}
	return convex;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lf%lf",&p[i].x,&p[i].y);
		double sum=0;	
		P O=P(0,0);
		for(int i=2;i<n;i++){
			double Area=(p[i]-p[1])*(p[i+1]-p[1]);
			P OO=(p[1]+p[i]+p[i+1]);
			O=O+OO*Area;
			sum+=Area;
		}
		O=O/sum/3;
		
//		O.print();puts("");
		
		vector<P>ch=vector<P>(p+1,p+1+n);
		ch=convex_hull(ch);
		
//		for(int i=0;i<ch.size();i++){
//			ch[i].print();
//			puts("");
//		}
		
		int ans=0;
		for(int i=0;i<ch.size();i++){
			double dot=((O-ch[i])^(ch[(i+1)%ch.size()]-ch[i]));
			
//			if(i==0)cout<<dot<<endl;
			
			if(sgn(dot)<=0||sgn(dot,(ch[(i+1)%ch.size()]-ch[i]).len2())>=0)continue;
//			cerr<<i<<endl;
			ans++;
		}printf("%d\n",ans);
	}
	return 0;
}

#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;

const double eps = 1e-9;
double R;

inline int dcmp(double a)
{
	if (-eps <= a&&a <= eps) return 0;
	else if (a > 0) return 1; else return -1;
}

struct Point
{
	double x,y;
	inline Point() {}
	inline Point(double _x,double _y = 0):x(_x),y(_y) {}
	inline Point unit() const { double len = norm(); return Point(x/len,y/len); }
	inline double norm() const { return sqrt(x*x+y*y); }
	inline void read() { scanf("%lf %lf",&x,&y); }
	friend inline bool operator==(const Point &a,const Point &b) { return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y); }
	friend inline Point operator+(const Point &a,const Point &b) { return Point(a.x+b.x,a.y+b.y); }
	friend inline Point operator-(const Point &a,const Point &b) { return Point(a.x-b.x,a.y-b.y); }
	friend inline Point operator/(const Point &a,const double b) { return Point(a.x/b,a.y/b); }
	friend inline Point operator*(const Point &a,double b) { return Point(a.x*b,a.y*b); }
	friend inline Point operator*(double b,const Point &a) { return Point(a.x*b,a.y*b); }
	inline void print() const { printf("%.5f %.5f\n",x,y); }
}P,Q;

int main()
{
	int T; scanf("%d",&T);
	while (T--)
	{
		scanf("%lf",&R);
		P.read(); Q.read();
		if (P == Point(0,0)) printf("%.6f\n",2*R);
		else
		{
			double l = P.norm();
			Point dP = P.unit(),dQ = Q.unit();
			Point pp = dP*R,qq = dQ*R,v = (pp+qq)/2;
			if (v.norm() <= l)
				printf("%.6f\n",(pp-qq).norm());
			else
			{
				v = (v.unit())*l;
				printf("%.6f\n",(pp-v).norm()+(qq-v).norm());
			}
		}
	}
	return 0;
}

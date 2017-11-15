struct P {
	double x, y, z;
	P(){}
	P(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	double len2(){
		return (x*x+y*y+z*z);
	}
	double len(){
		return sqrt(x*x+y*y+z*z);
	}
};
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 && sgn(a.y-b.y)==0 && sgn(a.z-b.z)==0 ;
}
bool operator<(P a,P b){
	return sgn(a.x-b.x) ? a.x<b.x :(sgn(a.y-b.y)?a.y<b.y :a.z<b.z);
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y,a.z+b.z);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y,a.z-b.z);
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b,a.z*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b,a.z/b);
}
P operator*(const P &a, const P &b) {
	return P(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
double operator^(const P &a, const P &b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

double dis(P a,P b){return (b-a).len();}
double dis2(P a,P b){return (b-a).len2();}


// 平面法向量 : 平面上两个向量叉积
// 点共平面 : 平面上一点与之的向量点积法向量为 0
// 点在线段 ( 直线 ) 上 : 共线且两边点积非正
// 点在三角形内 ( 不包含边界，需再判断是与某条边共线 )
bool in_tri(const P &a, const P &b, const P &c, const P &p) {
	return sgn(((a - b)*(a - c)).len() - ((p - a)*(p - b)).len() - ((p - b)*(p - c)).len() - ((p - c)*(p - a)).len()) == 0;
}
// 共平面的两点是否在这平面上一条直线的同侧
bool sameSide(const P &a, const P &b, const P &p0, const P &p1) {
	return sgn(((a - b)*(p0 - b)) ^ ((a - b)*(p1 - b))) > 0;
}
// 两点在平面同侧 : 点积法向量符号相同
// 两直线平行 / 垂直 : 同二维
// 平面平行 / 垂直 : 判断法向量
// 线面垂直 : 法向量和直线平行
// 判断空间线段是否相交 : 四点共面两线段不平行相互在异侧
// 线段和三角形是否相交 : 线段在三角形平面不同侧 三角形任意两点在线段和第三点组成的平面的不同侧
// 求空间直线交点
P intersect(const P &a0, const P &b0, const P &a1, const P &b1) {

double t = ((a0.x - a1.x) * (a1.y - b1.y) - (a0.y - a1.y) * (a1.x - b1.x)) / ((a0.x - b0.x) * (a1.y - b1.y) - (a0.y - b0.y) * (a1.x - b1.x));

	//double t = ((a0.x - a1.x) * (a1.y - b1.y) - (a0.y - a1.y) * (a1.x - b1.x)) / ((a0.x - b0.x) * (a1.y - b1.y) - (a0.y - b0.y) * (a1.x - b1.x));
	return a0 + (b0 - a0) * t;
}
// 求平面和直线的交点
P intersect(const P &a, const P &b, const P &c, const P &l0, const P &l1) {

	P p = (b-a)*(c-a); // 平面法向量
	double t = (p^(a-l0)) / (p^(l1-l0));
	return l0 + (l1 - l0) * t;
//	P p = pVec(a, b, c); // 平面法向量
//	double t = (p.x * (a.x - l0.x) + p.y * (a.y - l0.y) + p.z * (a.z - l0.z)) / (p.x * (l1.x - l0.x) + p.y * (l1.y - l0.y) + p.z * (l1.z - l0.z));
//	return l0 + (l1 - l0) * t;
}
// 求平面交线 : 取不平行的一条直线的一个交点，以及法向量叉积得到直线方向
// 点到直线距离 : 叉积得到三角形的面积除以底边
// 点到平面距离 : 点积法向量
// 直线间距离 : 平行时随便取一点求距离，否则叉积方向向量得到方向点积计算长度
// 直线夹角 : 点积 平面夹角 : 法向量点积

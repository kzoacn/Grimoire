inline int sign(double x) { return x < -EPS ? -1 : x > EPS; }
inline double sqr(double x) { return x * x; }

struct point {
	double x, y;
	point(double x = 0, double y = 0) : x(x), y(y) {}
	inline double length() const { return sqrt(x * x + y * y); }
	inline double norm() const { return length(); }
	inline double norm2() const { return x * x + y * y; }
	inline point unit() const {
		double len = length();
		return point(x / len, y / len);
	}
	inline point negate() const { return point(-x, -y); }
	inline point rot90() const {	// counter - clockwise
		return point(-y, x);
	}
	inline point _rot90() const {	// clockwise
		return point(y, -x);
	}
	inline point rotate(double theta) const {	// counter - clockwise
		double c = cos(theta), s = sin(theta);
		return point(x * c - y * s, x * s + y * c);
	}
	int get() { return scanf("%lf %lf", &x, &y); }
	void out() { printf("(%.5f, %.5f)\n", x, y); }
};

inline bool operator==(const point &a, const point &b) {
	return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS;
}
inline bool operator!=(const point &a, const point &b) {
	return fabs(a.x - b.x) > EPS || fabs(a.y - b.y) > EPS;
}
inline bool operator<(const point &a, const point &b) {
	if (fabs(a.x - b.x) > EPS) return a.x < b.x;
	return a.y + EPS < b.y;
}
inline point operator+(const point &a, const point &b) {
	return point(a.x + b.x, a.y + b.y);
}
inline point operator-(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline point operator*(const point &a, const double &b) {
	return point(a.x * b, a.y * b);
}
inline point operator/(const point &a, const double &b) {
	return point(a.x / b, a.y / b);
}
inline double det(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}
inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
inline double dis(const point &a, const point &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
struct line {
	point s, t;
	line(point s = point(), point t = point()) : s(s), t(t) {}
	inline double length() const { return dis(s, t); }
};
//线段交点
//注意如果两条线段是共线的且有交点, 那么 intersect_judgement 确实会返回 true,
//但是line_intersect 会求错, 所以这种情况需要特判.
inline bool point_on_line(const point &a, const line &b) {
	return sign(det(a - b.s, b.t - b.s)) == 0 && dot(b.s - a, b.t - a) < EPS;
}
inline bool two_side(const point &a, const point &b, const line &c) {
	return sign(det(a - c.s, c.t - c.s)) * sign(det(b - c.s, c.t - c.s)) < 0;
}
inline bool intersect_judgement(const line &a, const line &b) {
	if (point_on_line(b.s, a) || point_on_line(b.t, a)) return true;
	if (point_on_line(a.s, b) || point_on_line(a.t, b)) return true;
	return two_side(a.s, a.t, b) && two_side(b.s, b.t, a);
}
inline point line_intersect(const line &a, const line &b) {
	double s1 = det(a.t - a.s, b.s - a.s);
	double s2 = det(a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1);
}
//点到直线的距离
double point_to_line(const point &p, const line &l) {
	return fabs(det(l.t - l.s, p - l.s)) / dis(l.s, l.t);
}
inline double min_point_to_line(const point &a, const line &b) {
	if (dot(b.s - a, b.t - a) < EPS)
		return fabs(det(b.s - a, b.t - a) / b.length());
	return min(dis(a, b.s), dis(a, b.t));
}
//点在多边形内
bool in_polygon(const point &p, const vector<point> &poly) {
	int n = (int)poly.size();
	int counter = 0;
	for (int i = 0; i < n; ++i) {
		point a = poly[i], b = poly[(i + 1) % n];
		if (point_on_line(p, line(a, b))) return false;	// bounded excluded
		int x = sign(det(p - a, b - a));
		int y = sign(a.y - p.y);
		int z = sign(b.y - p.y);
		if (x > 0 && y <= 0 && z > 0) counter++;
		if (x < 0 && z <= 0 && y > 0) counter--;
	}
	return counter != 0;
}
//点到直线的投影
point project_to_line(const point &p, const line &l) {
	return l.s + (l.t - l.s) * (dot(p - l.s, l.t - l.s) / (l.t - l.s).norm2());
}
//圆类
struct circle {
	point center;
	double radius;
	circle(point center = point(), double radius = 0)
			: center(center), radius(radius) {}
};
inline bool operator==(const circle &a, const circle &b) {
	return a.center == b.center && fabs(a.radius - b.radius) < EPS;
}
inline bool operator!=(const circle &a, const circle &b) {
	return a.center != b.center || fabs(a.radius - b.radius) > EPS;
}
inline bool in_circle(const point &p, const circle &c) {
	return dis(p, c.center) < c.radius + EPS;
}
//圆的生成函数
circle make_circle(const point &a, const point &b) {
	return circle((a + b) / 2, dis(a, b) / 2);
}
circle make_circle(const point &a, const point &b, const point &c) {
	point center = circumcenter(a, b, c);
	return circle(center, dis(center, a));
}
//点到圆的切线
pair<line, line> tangent(const point &p, const circle &c) {
	circle a = make_circle(p, c.center);
	return make_pair(circle_intersect(a, c), circle_intersect(c, a));
}
//直线与圆的交点
//返回 AB 方向的第一个交点
point line_circle_intersect(const line &l, const circle &c) {
	double x = sqrt(sqr(c.radius) - sqr(point_to_line(c.center, l)));
	return project_to_line(c.center, l) + (l.s - l.t).unit() * x;
}
//圆与圆的交点
point circle_intersect(const circle &a, const circle &b) {	// get another point
	using circle_intersect(b, a) point r = (b.center - a.center).unit();
	double d = dis(a.center, b.center);
	double x = .5 * ((sqr(a.radius) - sqr(b.radius)) / d + d);
	double h = sqrt(sqr(a.radius) - sqr(x));
	return a.center + r * x + r.rot90() * h;
}

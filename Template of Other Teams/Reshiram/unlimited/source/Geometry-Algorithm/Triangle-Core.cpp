//三角形的内心
point incenter(const point &a, const point &b, const point &c) {
	double p = (a - b).length() + (b - c).length() + (c - a).length();
	return (a * (b - c).length() + b * (c - a).length() + c * (a - b).length()) /
				 p;
}
//三角形的外心
point circumcenter(const point &a, const point &b, const point &c) {
	point p = b - a, q = c - a, s(dot(p, p) / 2, dot(q, q) / 2);
	double d = det(p, q);
	return a + point(det(s, point(p.y, q.y)), det(point(p.x, q.x), s)) / d;
}
//三角形的垂心
point orthocenter(const point &a, const point &b, const point &c) {
	return a + b + c - circumcenter(a, b, c) * 2.0;
}

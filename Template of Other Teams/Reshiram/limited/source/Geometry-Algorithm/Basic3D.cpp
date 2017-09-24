struct TPoint{
	double x, y, z;
	TPoint() {}
	TPoint(double x, double y, double z) : x(x), y(y), z(z) {}
	bool operator <(const TPoint &p)const {
		int dX = dcmp(x - p.x), dY = dcmp(y - p.y), dZ = dcmp(z - p.z);
		return dX < 0 || (dX == 0 && (dY < 0 || (dY == 0 && dZ < 0)));
	}
};
double sqrdist(const TPoint &a);
double sqrdist(const TPoint &a, const TPoint &b);
double dist(const TPoint &a);
double dist(const TPoint &a, const TPoint &b);
double dot(const TPoint &a, const TPoint &b);
TPoint det(const TPoint &a, const TPoint &b) {
	TPoint ret;
	ret.x = a.y * b.z - b.y * a.z;
	ret.y = a.z * b.x - b.z * a.x;
	ret.z = a.x * b.y - b.x * a.y;
	return ret;
}
double detdot(const TPoint &a, const TPoint &b, const TPoint &c, const TPoint &d) {
	return dot(det(b - a, c - a), d - a);
}

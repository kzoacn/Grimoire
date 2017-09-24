int sgn(const double &x, const double &eps = 1e-8) {
    return (x < -eps) ? -1 : (x > eps);
}

class Point {
public:
    double x, y;

    Point() {}

    Point(const double &x, const double &y) : x(x), y(y) {}

    double len() const {
        return hypot(x, y);
    }

    friend Point operator + (const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y);
    }

    friend Point operator - (const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }

    friend Point operator * (const Point &a, const double &k) {
        return Point(a.x * k, a.y * k);
    }

    friend Point operator / (const Point &a, const double &k) {
        return Point(a.x / k, a.y / k);
    }

    friend bool operator == (const Point &a, const Point &b) {
        return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
    }

    friend bool operator < (const Point &a, const Point &b) {
        if (sgn(a.x - b.x) == 0) {
            return sgn(a.y - b.y) < 0;
        } else {
            return sgn(a.x - b.x) < 0;
        }
    }

    friend double det(const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
    }

    friend double det(const Point &a, const Point &b, const Point &c) {
        return det(b - a, c - a);
    }

    friend double dot(const Point &a, const Point &b) {
        return a.x * b.x + a.y * b.y;
    }

    friend double dot(const Point &a, const Point &b, const Point &c) {
        return dot(b - a, c - a);
    }

    friend Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
        double s1 = det(a, b, c);
        double s2 = det(a, b, d);
        return (s1 * d - s2 * c) / (s1 - s2);
    }
};
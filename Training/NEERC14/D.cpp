#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const double EPS = 1e-6;
const double pi = acos(-1.0);
const double INF = 1e10;

double r, h, l, d, t;

inline int sgn(double t) {
	if (t < -eps) {
		return -1;
	} else {
		return t > eps;
	}
}

inline double mysqrt(double t) {
	return t < 0.0 ? 0.0 : sqrt(t);
}

inline double myacos(double t) {
	if (t > 1.0) {
		return 0.0;
	}
	if (t < -1.0) {
		return pi;
	}
	return acos(t);
}

inline double myasin(double t) {
	if (t > 1.0) {
		return 0.0;
	}
	if (t < -1.0) {
		return pi;
	}
	return asin(t);
}

inline double fan(double r, double d) {
	if (d < 0.0) {
		return 0.0;
	}
	if (d > r * 2.) {
		return pi * r * r;
	}
	double t = d - r;
	double theta = myacos(t / r);
	return 2 * (0.5 * t * r * sin(theta) + 0.5 * (pi - theta) * r * r);
}

inline double ball_sim(double left, double right) {
	double mid = (left + right) / 2.0;
	double l = right - left;
	double nowans = 1.0 / 6 * fan(mysqrt(r * r - left * left), INF) +
					4.0 / 6 * fan(mysqrt(r * r - mid * mid), INF) +
					1.0 / 6 * fan(mysqrt(r * r - right * right), INF);
	nowans *= l;
	return nowans;
}

inline double get_ball(double left, double right) {   //simpson one!!
	double mid = (left + right) / 2.0;
	double lans = ball_sim(left, mid), rans = ball_sim(mid, right),
			nowans = ball_sim(left, right);
	return fabs(lans + rans - nowans) < EPS ? nowans : get_ball(left, mid) + get_ball(mid, right);
}

inline double area(double x, double h) {
	double r1 = mysqrt(r * r - x * x);
	const double alpha = myacos(d / 2 / r);
	const double theta = myasin(t / l);
	double beta = myacos(x / r);
	double len = (h - r * sin(pi / 2 - alpha + theta) - r * cos(pi / 2 - theta - beta)) / cos(theta);
	return fan(r1, len);
}

inline double half_sim(double left, double right, double h) { 
	double mid = (left + right) / 2.0;
	double l = right - left;
	double nowans = 1.0 / 6 * area(left, h) + 4.0 / 6 * area(mid, h) + 1.0 / 6 * area(right, h);
	nowans *= l;
	return nowans;
}

inline double get_half(double left, double right, double h) { //simpson two!!!
	double mid = (left + right) / 2.0;
	double lans = half_sim(left, mid, h), rans = half_sim(mid, right, h),
			nowans = half_sim(left, right, h);
	return fabs(lans + rans - nowans) < EPS ? nowans : get_half(left, mid, h) + get_half(mid, right, h);
}

inline double circle(double x) {
	const double theta = myasin(t / l);
	double tmp = h - x * sin(theta);
	tmp /= cos(theta);
	return fan(d / 2, tmp);
}

inline double half_cylinder(double left, double right) {  //simpson three!!!
	double mid = (left + right) / 2.0;
	double l = right - left;
	double nowans = 1.0 / 6 * circle(left) + 4.0 / 6 * circle(mid) + 1.0 / 6 * circle(right);
	nowans *= l;
	return nowans;
}

inline double get_cylinder(double left, double right) {
	double mid = (left + right) / 2.0;
	double lans = half_cylinder(left, mid), rans = half_cylinder(mid, right),
			nowans = half_cylinder(left, right);
	return fabs(lans + rans - nowans) < EPS ? nowans : get_cylinder(left, mid) + get_cylinder(mid, right);
}

int main() {
	//freopen("damage.in", "r", stdin);
	//freopen("damage.out", "w", stdout);
	
	cin >> d >> l >> r >> t >> h;
	d /= 100;
	l /= 100;
	r /= 100;
	t /= 100;
	h /= 100;
	
	if (sgn(t - l) == 0) {
		double ans = get_ball(mysqrt(r * r - (d / 2) * (d / 2)), r);
		printf("%.10f\n", ans);
		return 0;
	}
	double theta = myasin(t / l);
	double ans1 = get_half(mysqrt(r * r - (d / 2) * (d / 2)), r, h);
	double ans2 = get_cylinder(0, l);
	double ans3 = get_half(mysqrt(r * r - (d / 2) * (d / 2)), r, INF) - get_half(mysqrt(r * r - (d / 2) * (d / 2)), r, t + d * cos(theta) - h);
	printf("%.10f\n", ans1 + ans2 + ans3);
}

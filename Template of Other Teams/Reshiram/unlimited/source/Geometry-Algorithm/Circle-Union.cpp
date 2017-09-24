struct arc {
	double theta;
	int delta;
	point p;
	arc(){};
	arc(const double &theta, const point &p, int d)
			: theta(theta), p(p), delta(d) {}
};

vector<arc> vec;
vector<double> ans;
vector<point> center;
int cnt = 0;

inline bool operator<(const arc &a, const arc &b) {
	return a.theta + EPS < b.theta;
}

inline void psh(const double t1, const point p1, const double t2,
								const point p2) {
	if (t2 + EPS < t1) cnt++;
	vec.push_back(arc(t1, p1, 1));
	vec.push_back(arc(t2, p2, -1));
}

inline double cub(const double &x) { return x * x * x; }
inline void combine(int d, const double &area, const point &o) {
	if (sign(area) == 0) return;
	center[d] = (center[d] * ans[d] + o * area) * (1 / (ans[d] + area));
	ans[d] += area;
}

void area(vector<circle> &cir) {
	int n = cir.size();
	vector<bool> f;
	f.resize(n);
	vec.clear();
	cnt = 0;
	for (int i = 0; i < n; i++) {
		f[i] = true;
		for (int j = 0; j < n; j++)
			if (i != j) {
				if ((cir[i] == cir[j] && i < j) ||
						(cir[i] != cir[j] && cir[i].radius < cir[j].radius + EPS &&
						 (cir[i].center - cir[j].center).length() <
								 fabs(cir[i].radius - cir[j].radius) + EPS)) {
					f[i] = false;
					break;
				}
			}
	}
	int n1 = 0;
	for (int i = 0; i < n; i++)
		if (f[i]) cir[n1++] = cir[i];
	n = n1;
	ans.clear();
	center.clear();
	ans.resize(n + 1);
	center.resize(n + 1);
	point dvd;
	for (int i = 0; i < n; i++) {
		dvd = cir[i].center - point(cir[i].radius, 0);
		vec.clear();
		vec.push_back(arc(-PI, dvd, 1));
		cnt = 0;
		for (int j = 0; j < n; j++)
			if (j != i) {
				double d = (cir[j].center - cir[i].center).norm2();
				if (d < sqr(cir[j].radius - cir[i].radius) + EPS) {
					if (cir[i].radius + i * EPS < cir[j].radius + j * EPS)
						psh(-PI, dvd, PI, dvd);
				} else if (d + EPS < sqr(cir[j].radius + cir[i].radius)) {
					double lambda =
							0.5 * (1 + (sqr(cir[i].radius) - sqr(cir[j].radius)) / d);
					point cp(cir[i].center + (cir[j].center - cir[i].center) * lambda);
					point nor((cir[j].center - cir[i].center)._rot90().unit() *
										(sqrt(sqr(cir[i].radius) - (cp - cir[i].center).norm2())));
					point frm(cp + nor);
					point to(cp - nor);
					psh(atan2((frm - cir[i].center).y, (frm - cir[i].center).x), frm,
							atan2((to - cir[i].center).y, (to - cir[i].center).x), to);
				}
			}
		sort(vec.begin() + 1, vec.end());
		vec.push_back(arc(PI, dvd, -1));
		for (int j = 0; j + 1 < vec.size(); j++) {
			cnt += vec[j].delta;
			double theta(vec[j + 1].theta - vec[j].theta);
			double area(sqr(cir[i].radius) * theta * 0.5);
			combine(cnt, area, cir[i].center +
														 point(sin(vec[j + 1].theta) - sin(vec[j].theta),
																	 cos(vec[j].theta) - cos(vec[j + 1].theta)) *
																 (1. / area / 3 * cub(cir[i].radius)));
			combine(cnt, -sqr(cir[i].radius) * sin(theta) * 0.5,
							(cir[i].center + vec[j].p + vec[j + 1].p) / 3.);
			combine(cnt, det(vec[j].p, vec[j + 1].p) * 0.5,
							(vec[j].p + vec[j + 1].p) / 3.);
		}
	}
}

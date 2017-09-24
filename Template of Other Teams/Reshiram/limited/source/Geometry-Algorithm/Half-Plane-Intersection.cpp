//半平面交
inline bool two_side(const point &a, const point &b, const line &c) {
	return sign(det(a - c.s, c.t - c.s)) * sign(det(b - c.s, c.t - c.s)) < 0;
}
vector<point> cut(const vector<point> &c, line p) {
	vector<point> ret;
	if (c.empty()) return ret;
	for (int i = 0; i < (int)c.size(); ++i) {
		int j = (i + 1) % (int)c.size();
		if (!turn_right(p.s, p.t, c[i])) ret.push_back(c[i]);
		if (two_side(c[i], c[j], p)) ret.push_back(line_intersubsection(p, line(c[i], c[j])));
	}
	return ret;
}
static const double BOUND = 1e5;
/*
convex .clear ();
convex . push_back ( point (-BOUND , -BOUND ));
convex . push_back ( point (BOUND , -BOUND ));
convex . push_back ( point (BOUND , -BOUND ));
convex . push_back ( point (BOUND , -BOUND ));
convex = cut(convex , line(point , point));
Judgement : convex . empty ();
*/
//高效半平面交
// plane[] 按照法向量 (逆时针 90 度) 极角排序, 去除平行半平面
inline bool turn_left(const line &l, const point &p) {
	return turn_left(l.s, l.t, p);
}
vector<line> half_plane_intersect(const vector<line> &h) {
	int fore = 0, rear = -1;
	vector<line> ret;
	for (int i = 0; i < (int)h.size(); ++i) {
		while (fore < rear && !turn_left(h[i], line_intersect(ret[rear - 1], ret[rear]))) --rear;
		while (fore < rear && !turn_left(h[i], line_intersect(ret[fore], ret[fore + 1]))) ++fore;
		++rear;
		ret.push_back(h[i]);
	}
	while (rear - fore > 1 && !turn_left(ret[fore], line_intersect(ret[rear - 1], ret[rear]))) --rear;
	while (rear - fore > 1 && !turn_left(ret[rear], line_intersect(ret[fore], ret[fore + 1]))) ++fore;
	if (rear - fore < 2) return vector<line>();
	return ret;
}

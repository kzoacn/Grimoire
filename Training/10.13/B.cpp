#include <bits/stdc++.h>

struct vec {
	int x, y;
	
	vec() {}
	vec(int x, int y): x(x), y(y) {}
	
	int halfPlane() {
		if (y == 0) {
			return x > 0 ? 0 : 1;
		}
		return y > 0;
	}
	
	void scan() {
		scanf("%d%d", &x, &y);
	}
};

int XX(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

bool byAngle(vec a, vec b) {
	if (a.halfPlane() ^ b.halfPlane()) {
		return a.halfPlane() < b.halfPlane();
	}
	return XX(a, b) > 0;
}

struct Line {
	int A, B, id;
	vec spec;
	
	Line() {}
	Line(int a, int b, int id, vec sp): A(a), B(b), id(id), spec(sp) {}
	
	bool check(int x, int y) {
		return A * x + B * y >= 0;
	}
	
	bool check(const vec &rhs) {
		return check(rhs.x, rhs.y);
	}
	
	bool operator < (const Line &rhs) const {
		return byAngle(spec, rhs.spec);
	}
	
	bool operator == (const Line &rhs) const {
		return !(*this < rhs) && !(rhs < *this);
	}
	
	void reverse() {
		A = -A; B = -B;
	}
} eq[200005];
int tot;

std::set<int> st;

int solve() {
	st.clear();
	
	std::sort(eq + 1, eq + tot + 1);
	for (int i = 1; i <= tot; ++i) {
		if (eq[i].check(eq[1].spec)) {
			st.insert(eq[i].id);
		}
	}
	
	int res = 0;
	if (eq[1].spec.x >= 0 && eq[1].spec.y >= 0) res = st.size();
	
	for (int i = 2; i <= tot; ++i) {
		int j = i - 1;
		do {
			if (!eq[j].check(eq[i].spec)) st.erase(eq[j].id);
			--j;
		} while (j && eq[j] == eq[i - 1]);
		st.insert(eq[i].id);
		if (eq[i].spec.x >= 0 && eq[i].spec.y >= 0) res = std::max(res, (int)st.size());
	}
	
	return res;
}

int n;

int main() {
	int p, q;
	scanf("%d%d%d", &n, &p, &q);
	
	int tmp = 0;
	
	tot = 0;
	for (int i = 1; i < n; ++i) {
		static int x, y;
		
		scanf("%d%d", &x, &y);
		if (x == p && y == q) {
			++tmp; continue;
		}
		x = p - x, y = q - y;
		
		eq[++tot] = Line(x, y, i, vec(y, -x));
		eq[++tot] = Line(x, y, i, vec(-y, x));
	}
	
	printf("%d ", n - (solve() + tmp));
	
	for (int i = 1; i <= tot; ++i)
		eq[i].reverse();
	
	printf("%d\n", solve() + tmp + 1);
	
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 20 + 5;

const double eps = 1e-10;

inline int sgn(double x) { return x < -eps ? -1 : x > eps; }

int n;

struct Point {
	double x, y;
	
	Point() {}
	Point(double x, double y): x(x), y(y) {}
	
	Point operator + (const Point &oth) const {
		return Point(x + oth.x, y + oth.y);
	}
	
	Point operator - (const Point &oth) const {
		return Point(x - oth.x, y - oth.y);
	}
	
	Point operator / (double t) {
		return Point(x / t, y / t);
	}
	Point operator * (double t) {
		return Point(x * t, y * t);
	}
	
	void scan() {
		scanf("%lf%lf", &x, &y);
	}
} tri[3];

double cross(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}

bool inTriangle(Point p) {
	static int sgns[3];
	
	for (int i = 0; i < 3; ++i)
		sgns[i] = sgn(cross(tri[(i + 1) % 3] - tri[i], p - tri[i]));
	return sgns[0] && sgns[0] == sgns[1] && sgns[1] == sgns[2];
}

bool intersect(Point a1, Point a2, Point b1, Point b2) {
	return sgn(cross(a2 - a1, b1 - a1)) * sgn(cross(a2 - a1, b2 - a1)) == -1 &&
		   sgn(cross(b2 - b1, a1 - b1)) * sgn(cross(b2 - b1, a2 - b1)) == -1;
}

double area;

bool Check(Point a, Point b) {
	assert(sgn(area) > 0) ;
	int T=100;
	for(int i=0;i<=T;i++)
		if(inTriangle(a+(b-a)*i/T))
			return false;
	if (inTriangle(a) || inTriangle(b) || inTriangle((a + b) / 2))
		return 0;
	for (int i = 0; i < 3; ++i)
		if (intersect(a, b, tri[i], tri[(i + 1) % 3]))
			return 0;
	return 1;
}

bool good[MAXN][MAXN];

int id[MAXN][MAXN], tot;

int dist[MAXN * MAXN];

std::vector<int> G[MAXN * MAXN];

inline bool valid(int x) {
	return x >= 0 && x < n;
}

void BFS() {
	static std::queue<int> que;
	
	for (int i = 1; i <= tot; ++i)
		dist[i] = -1;
	dist[1] = 0; que.push(1);
	while (!que.empty()) {
		int now = que.front(); que.pop();
		for (int to: G[now]) {
			if (dist[to] != -1) continue;
			dist[to] = dist[now] + 1;
			que.push(to);
		}
	}
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < 3; ++i)
			tri[i].scan();
		area = std::abs(cross(tri[1] - tri[0], tri[2] - tri[0]) / 2);
		for (int y = n - 1; y >= 0; --y) {
			static char s[MAXN];
			scanf("%s", s);
			for (int x = 0; x < n; ++x)
				good[x][y] = (s[x] == '.');
		}
		
		if (!good[0][0] || !good[n - 1][n - 1]) {
			puts("-1"); continue;
		}
		
		tot = 0;
		for (int x = 0; x < n; ++x)
			for (int y = 0; y < n; ++y) {
				if (good[x][y]) {
					id[x][y] = ++tot;
					G[tot].clear();
				}
				else id[x][y] = 0;
			}
		
//		std::cerr << "inT" << inTriangle(Point(0.5, 0.5)) << std::endl;
		
		for (int x = 0; x < n; ++x)
			for (int y = 0; y < n; ++y) if (good[x][y])
				for (int dx = -1; dx <= 1; ++dx)
					for (int dy = -1; dy <= 1; ++dy) {
						if (!dx && !dy) continue;
						if (!valid(x + dx) || !valid(y + dy) || !good[x + dx][y + dy]) continue;
						if (Check(Point(x, y), Point(x + dx, y + dy))) {
							G[id[x][y]].push_back(id[x + dx][y + dy]);
//							if (x == 0 && y == 0)
//								std::cerr << x + dx << " " << y + dy << std::endl;
						}
					}
		
		BFS();
		printf("%d\n", dist[id[n - 1][n - 1]]);
	}
	
	return 0;
}

#include <bits/stdc++.h>

typedef std::pair<int, int> pii;

const int INF = 0x3f3f3f3f;

struct vec {
	int x, y, z;
	
	vec() {}
	vec(int x, int y, int z): x(x), y(y), z(z) {}
	
	bool operator < (const vec &rhs) const {
		return x == rhs.x ? (y == rhs.y ? z < rhs.z : y < rhs.y) : x < rhs.x;
	}
	
	bool operator == (const vec &rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}
	
	vec &operator += (const vec &rhs) {
		x += rhs.x; y += rhs.y; z += rhs.z;
		return *this;
	}
	
	vec &operator /= (const int &t) {
//		printf("%d %d %d %d\n", x, y, z, t);
		x /= t; y /= t; z /= t;
		return *this;
	}
	
	void scan() {
		scanf("%d%d%d", &x, &y, &z);
	}
};

int n, nx, ny, nz;

struct Peo {
	int mass;
	vec init, now, v;
	
	Peo() {}
	
	bool operator < (const Peo &rhs) const {
		return mass == rhs.mass ? init < rhs.init : mass > rhs.mass;
	}
	
	void scan() {
		scanf("%d", &mass);
		init.scan(); v.scan();
		now = init;
	}
	
	void go(int t) {
		now.x = ((now.x + 1ll * v.x * t) % nx + nx) % nx;
		now.y = ((now.y + 1ll * v.y * t) % ny + ny) % ny;
		now.z = ((now.z + 1ll * v.z * t) % nz + nz) % nz;
	}
	
	void print() {
		printf("%d %d %d %d %d %d %d\n", mass, init.x, init.y, init.z, v.x, v.y, v.z);
	}
}; std::vector<Peo> peo;

bool cmp(const Peo &a, const Peo &b) {
	return a.now < b.now;
}

void exgcd(int A, int B, int C, int &x, int &y) {
	if (A == 0) {
		y = C / B; x = 0;
		return;
	}
	exgcd(B % A, A, C, y, x);
	x -= B / A * y;
}

bool calc(int p1, int v1, int p2, int v2, pii &res, int N) {
	int t, k, gcd = std::__gcd(v2 - v1, N);
	if ((p1 - p2) % gcd != 0) return 0;
	exgcd(v2 - v1, N, p1 - p2, t, k);
	int vt = std::abs(N / gcd);
	t = (t % vt + vt) % vt;
	
	res = std::make_pair(t, vt);
	return 1;
}

pii merge(const pii &a, const pii &b) {
	int k1, k2, gcd = std::__gcd(a.second, b.second);
	exgcd(a.second, -b.second, b.first - a.first, k1, k2);
	int B = b.second / gcd;
	k1 = (k1 % B + B) % B;
	
	int v = a.first + a.second * k1, vt = 1ll * a.second * b.second / gcd;
	return std::make_pair(v % vt, vt);
}

int Calc(const Peo &a, const Peo &b) {
	pii t1, t2, t3;
	
	if (!calc(a.now.x, a.v.x, b.now.x, b.v.x, t1, nx)) return INF;
	if (!calc(a.now.y, a.v.y, b.now.y, b.v.y, t2, ny)) return INF;
	if (!calc(a.now.z, a.v.z, b.now.z, b.v.z, t3, nz)) return INF;
	
	return merge(t1, merge(t2, t3)).first;
}

bool vis[105];

int main() {
	scanf("%d%d%d%d", &n, &nx, &ny, &nz);
	
	Peo temp;
	for (int i = 1; i <= n; ++i) {
		temp.scan();
		peo.push_back(temp);
	}
	
	int mn_T;
	for (int T = 1; T < n; ++T) {
		mn_T = INF;
		for (int i = 0; i < (int)peo.size(); ++i)
			for (int j = i + 1; j < (int)peo.size(); ++j) {
				mn_T = std::min(mn_T, Calc(peo[i], peo[j]));
			}
		if (mn_T == INF) break;
		
		for (int i = 0; i < (int)peo.size(); ++i)
			peo[i].go(mn_T);
		std::sort(peo.begin(), peo.end(), cmp);
		
		memset(vis, 0, sizeof vis);
		int cnt = 1;
		for (int i = 1; i < (int)peo.size(); ++i) {
			if (peo[i].now == peo[i - 1].now) {
				peo[i].mass += peo[i - 1].mass;
				peo[i].init = peo[i].now;
				peo[i].v += peo[i - 1].v;
				++cnt;
				vis[i - 1] = 1;
				
				if (i + 1 == (int)peo.size()) {
					peo[i].v /= cnt;
				}
			}
			else {
				peo[i - 1].v /= cnt;
				cnt = 1;
			}
		}
		
		for (int i = (int)peo.size() - 1; i >= 0; --i) if (vis[i])
			peo.erase(peo.begin() + i);
	}
	
	std::sort(peo.begin(), peo.end());
	printf("%d\n", (int)peo.size());
	for (int i = 0; i < (int)peo.size(); ++i) {
		printf("P%d: ", i);
		peo[i].print();
	}
	
	return 0;
}

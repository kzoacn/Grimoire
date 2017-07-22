#include <bits/stdc++.h>

const double eps = 1e-8;

int sgn(double x) { return x < -eps ? -1 : x > eps; }

int l, s, d, n;

struct Car {
	double pos;
	int v;
	
	Car() {}
	Car(double pos, int v): pos(pos), v(v) {}
	
	void scan() {
		scanf("%lf%d", &pos, &v);
	}
	
	void go(double t) {
		pos += v * t;
	}
} car[105], now;

double tt[105];

int main() {
	int kase = 0;
	while (~scanf("%d%d%d%d", &l, &s, &d, &n) && (l || s || d || n)) {
		++kase;
		
		now = Car(l, s);
		for (int i = 1; i <= n; ++i)
			car[i].scan();
		
		double ans_t = 0;
		while (1) {
			double T = (d - now.pos) / now.v;
			
			double min_t = 1e20;
			for (int i = 1; i <= n; ++i) {
				double tmp = (now.pos - car[i].pos - 1) / (car[i].v - now.v);
				if (sgn(tmp) < 0) tt[i] = 1e20;
				else tt[i] = std::ceil(tmp * 4) / 4.;
				min_t = std::min(min_t, tt[i]);
			}
			
/*			printf("%f -> %d at speed of %d\n", now.pos, d, now.v);
			for (int i = 1; i <= n; ++i)
				printf("location: %f at speed of %d\n", car[i].pos, car[i].v);
			printf("min_t = %f\n", min_t);
			printf("T = %f\n", T);*/
			
			if (sgn(min_t - T) > 0) {
				ans_t += T;
				break;
			}
			ans_t += min_t;
			
			int v_sum = now.v, cnt = 1;
			for (int i = 1; i <= n; ++i)
				if (sgn(tt[i] - min_t) == 0) {
					v_sum += car[i].v;
					++cnt;
				}
			
			now.go(min_t);
			for (int i = 1; i <= n; ++i) car[i].go(min_t);
			
			now.v = v_sum / cnt;
		}
		
		printf("Case %d: Anna reaches her destination at time %.4f at a speed of %d\n", kase, ans_t, now.v);
	}
	
	return 0;
}

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 100005;
const int eps = 1e-7;
int n, Q;
double a[N], b[N], c[N];
void work() {
	double speed = 0;
	scanf("%lf", &speed);
	for(int i = 1; i <= n; i++) {
		scanf("%lf%lf%lf", &a[i], &b[i], &c[i]);
	}
	double ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += 1. * a[i] / b[i];
	}
	ans = ans / speed;
	printf("%d\n", (int)ceil(ans));
	for(int t = 1; t <= Q; t++) {
		int size = 0;
		scanf("%d", &size);
		double left = 0, right = 1e10;
		for(int i = 1; i <= 100; i++) {
			double mid = (left + right) * 0.5;
			double cnt = 0;
			for(int j = 1; j <= n; j++) {
				if((a[j] / b[j]) * mid - c[j] > -eps) {
					cnt += (((a[j] / b[j]) * mid - c[j]) / mid);
				}
			}
			if(cnt < speed * size + eps) {
				left = mid;
			} else {
				right = mid;
			}
		}
		if(left > 100000 + eps) {
			puts("-1.000");
		} else {
			printf("%.10f\n", left);
		}
	}
	return ;
}

int main() {
	scanf("%d%d", &n, &Q);
	int cases = 0;
	while(1) {
		cases++;
		if(n == 0 && Q == 0) {
			break;
		}
		printf("Case %d:\n", cases);
		work();
		scanf("%d%d", &n, &Q);
	}
	return 0;
}

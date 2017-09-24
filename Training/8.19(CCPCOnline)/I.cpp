#include<bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
int cs;
double a, b;

double myacos(double x) {
	if (x > 1.0) {
		return 0.0;
	}
	if (x < -1.0) {
		return pi;
	}
	return acos(x);
}

double angA(double a,double b,double c){
	return acos((b * b + a * a - c * c) / 2.0 / a / b);
}

inline double mysqrt(double x) {
	return x > 0.0 ? sqrt(x) : 0.0;
}

bool check(double x,double a,double b,double c){
	double t1 = angA(b + x, b + c, x + c),
		   t2 = angA(a - b, b + c, a - c);
	double t = t1 + t2;
	double l = sqrt((b + x) * (b + x) + (a - b) * (a - b) - 2 * cos(t) * (b + x) * (a - b));
	return l + x < a;
}

double calc(double a,double b,double c){
	double l=1e-4,r=c;
	
	int TAT=50;
	//while(TAT--){
	while (l + 1e-4 < r) {
		double mid=(l+r)/2;
		if(check(mid,a,b,c))
			l=mid;
		else r=mid;
	}
	return r;
}

int main(){
	cin >> cs;
	for (; cs; --cs) {
		int n;
		scanf("%lf%lf", &a, &b);
		scanf("%d", &n);
		if (a == b) {
			puts("0.00000");
			continue;
		}
		if (a < b) {
			swap(a, b);
		}
		double c = a - b, ans = c * c;
		for (int i = 2; i <= min(4000, n); ++i) {
			double t = c;
			c = calc(a, b, c);
			//cout << c << " " << t << " " << t / c << endl;
			if (c < 1e-3) {
				break;
			}
			ans += c * c;
		}
		ans *= pi;
		printf("%.5f\n", ans);
	}
	return 0;
}

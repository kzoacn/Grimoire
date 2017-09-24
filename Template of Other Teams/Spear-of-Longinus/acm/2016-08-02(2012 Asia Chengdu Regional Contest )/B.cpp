#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 300005;

int n;
double p;

long double f[N];

void work() {
	if(n == 1) {	
		puts("1.00") ;
		return ;
	}
	if(fabs(p - 1) < 1e-7 || fabs(p) < 1e-7) {	
		printf("%d\n", n);
		return ;
	}
	
	long double ans = 0;
	
	f[0] = 1. * (n + 1) * log(p) + log(1. * n);
	for(int i = 1; i <= n - 1; i++) {
		f[i] = f[i - 1];
		
		f[i] += log(1. - p);
		f[i] += log(1. * (n - i)) +  log(1. * (n + i));
		f[i] -= (log(1. * i) + log(1. * n - i + 1));
	}
	for(int i = 0; i <= n - 1; i++) {
		ans += exp(f[i]);
	}
	
	p = 1 - p;
	
	f[0] = 1. * (n + 1) * log(p) + log(1. * n);
	for(int i = 1; i <= n - 1; i++) {
		f[i] = f[i - 1];
		
		f[i] += log(1. - p);
		f[i] += log(1. * (n - i)) +  log(1. * (n + i));
		f[i] -= (log(1. * i) + log(1. * n - i + 1));
	}
	for(int i = 0; i <= n - 1; i++) {
		ans += exp(f[i]);
	}
	printf("%.8f\n", (double)ans);
	return ;
}

int main() {
	int t = 0;
	while(scanf("%d%lf", &n, &p) == 2) {
		printf("Case %d: ", ++t);
		work();
	}
	return 0;
}



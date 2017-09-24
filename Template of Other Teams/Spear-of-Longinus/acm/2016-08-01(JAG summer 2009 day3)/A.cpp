#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int N = 260;
const int M = 256;
const double eps = 1e-10;

int n, s, a, c;
int aa[N];
int b[N];
int cc[M];
double Ans;

int dcmp(double x){
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}

int main(){
	
	while (1){
		scanf("%d", &n);
		if (n == 0) break;
		for (int i = 1; i <= n; i++) scanf("%d", &aa[i]);
		
		Ans = 9999999999.0;
		for (int S = 0; S <= 15; S++)
			for (int A = 0; A <= 15; A++)
				for (int C = 0; C <= 15; C++){
					b[0] = S;
					for (int i = 1; i <= n; i++){
						b[i] = (A * (b[i - 1]) + C) % M;
					}
						
					for (int i = 0; i < M; i++)
						cc[i] = 0;
					
					for (int i = 1; i <= n; i++){
						b[i] = (aa[i] + b[i]) % M;
						cc[b[i]]++;
					}
					
					double Cur = 0.0;
					for (int i = 0; i < M; i++){
						double tmp = 1.0 * cc[i] / n;
						//printf("%.10lf ", tmp);
						if (dcmp(tmp) > 0)
						Cur = Cur - (tmp * log(tmp));
					}
				
					
					if (dcmp(Cur - Ans) < 0){
						//printf("%.10lf\n",Cur);
						Ans = Cur;
						s = S;
						a = A; 
						c = C;
					}
				}
		printf("%d %d %d\n", s, a, c);
	}
	
	return 0;
}

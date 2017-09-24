#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 15;

int n, d, p, l, v;
double Ans;

int main(){
	
	int Case = 0;
	while (1){
		Case++;
		scanf("%d%d", &n, &d);
		if (n == 0 && d == 0) break;
		Ans = 1.0 * d;
		for (int i = 1; i <= n; i ++){
			scanf("%d%d%d", &p, &l, &v);
			Ans = Ans - 1.0 * l;
			Ans = Ans + 2.0 * l / v;
		}
		printf("Case %d: %.3f\n", Case, Ans);
		printf("\n");
	}
	
	return 0;
}

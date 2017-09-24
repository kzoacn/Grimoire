#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 105;

int Case,n,m;
int a[N];

int gcd(int x,int y){
	if (y == 0) return x;
	return gcd(y, x % y);
}

int main(){
	
	scanf("%d", &Case);
	while (Case > 0){
		Case--;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) a[i] = -1;
		for (int i = 1; i <= m; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			a[x] = y;
		}
		
		int Cur = 100;
		for (int i = 1; i <= 2; i ++){
			if (a[i] != -1) {
				Cur = a[i];
				continue;
			}
			a[i] = Cur;
		}
		
		Cur = 0;
		for (int i = n; i >= 3; i--){
			if (a[i] != -1) {
				Cur = a[i];
				continue;
			}
			a[i] = Cur;
		}
		
		int fz = a[1] + a[2];
		int fm = 0;
		for (int i = 1; i <= n; i++)
			fm += a[i];
		int GCD = gcd(fz,fm);
		printf("%d/%d\n",fz / GCD, fm / GCD);
		
	}
	
	return 0;
}

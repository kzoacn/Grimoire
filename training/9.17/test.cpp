#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
	LL cnt = 0;
	
	int w=200;
	for(int a=1;a<=w;a++)
	for(int b=a+1;b<=w;b++)
	for(int c=b+1;c<=w;c++){
		if(__gcd(__gcd(a,b),c)==1&&a*a+b*b==c*c){
			printf("%d %d %d\n",a,b,c);
		}
	}
	
	return 0;
	for (int m = 1; m * m <= 1e2; m ++) {
		for (int n = 1; n <= m; n ++) {
			if (__gcd(n, m) == 1 && n) {
				LL a,b,c;
				a=(m*m-n*n)/2;
				b=m*n;
				c=(m*m+n*n)/2;
				if(a>b)swap(a,b);
				
				if(a<2)continue;
				printf("%lld %lld %lld\n",a,b,c);
				printf("%d %d\n",m,n);
			}
		}
	}
	cout << cnt << endl;
}

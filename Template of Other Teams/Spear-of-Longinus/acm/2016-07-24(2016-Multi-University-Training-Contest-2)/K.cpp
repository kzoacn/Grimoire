#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

int n, m, Case, sum;
int a[N];

int main(){
	scanf("%d", &Case);
	while (Case > 0){
		Case--;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
		}
		m = 0;
		for (int i = 1; i <= n; i++){
			if (a[i] % 2 == 0) continue;
			m++;
			a[i]--;
		}
		
		sum = 0;
		for (int i = 1; i <= n; i++)
			sum += a[i];
		if (m == 0){
			printf("%d\n", sum);
		} else {
			printf("%d\n", ((sum / 2) / m) * 2 + 1);
		}
	}
	return 0;
}

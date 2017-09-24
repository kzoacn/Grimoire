#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 50005;

int n, k;
int m[N];
int cnt[N];
int Case;
LL le,ri,mid;

int Calc(LL p){
	LL t0, t1, t2;
	int Ret = 0;
	t0 = t1 = t2 = 0;
	
	int Back = n;

	for (int i = n; i >= 1; i--){
		if (Back > i){
			while ( (Back - i) * (Back - i) >= p){
				t2 = t2 - 1LL * cnt[Back] * (Back - i - 1) * (Back - i - 1);
				t1 = t1 - 1LL * cnt[Back] * (Back - i - 1);
				t0 = t0 - 1LL * cnt[Back];
				Back--;
			}
		}
		t2 = t2 + 2 * t1 + t0;
		t1 = t1 + t0;
		
		LL Cur = m[i] - p * t0 + t2;
		if (Cur < 0) cnt[i] = 0;
		else cnt[i] = Cur / p + 1;
		
		t0 = t0 + cnt[i];
		Ret = Ret + cnt[i];
	}
	
	return Ret;

}

int main(){
	
	scanf("%d", &Case);
	while (Case > 0){
		--Case;
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d", &m[i]);
		
		le = 1; ri = 1e12;
		while (le < ri){
			mid = (le + ri) >> 1;
			//printf("%lld %lld %lld\n", le, ri, mid);
			if (Calc(mid) <= k) ri = mid;
			else le = mid + 1;
		}
		
		printf("%I64d\n", le);
	}
	
	return 0;
}

#include <bits/stdc++.h>

int n, a[10005];

int less_cnt = 0;

bool less_than(int x, int y) {
	assert(++less_cnt <= 10000);
	
	static char s[5];
	printf("1 %d %d\n", x, y);
	fflush(stdout);
	scanf("%s", s);
	return *s == 'Y';
}

void Sort(int l, int r) {
	static int tmp[10005];
	
	if (l >= r) return;
	
	int mid = (l + r) >> 1;
	Sort(l, mid); Sort(mid + 1, r);
	
	int cur1 = l, cur2 = mid + 1, cur = l;
	
	while (cur1 <= mid && cur2 <= r) {
		if (less_than(a[cur1], a[cur2])) {
			tmp[cur++] = a[cur1++];
		}
		else {
			tmp[cur++] = a[cur2++];
		}
	}
	while (cur1 <= mid) tmp[cur++] = a[cur1++];
	while (cur2 <= r) tmp[cur++] = a[cur2++];
	
	for (int i = l; i <= r; ++i) a[i] = tmp[i];
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) a[i] = i;
	
	Sort(1, n);
	
	printf("0 ");
	for (int i = 1; i <= n; ++i)
		printf("%d%c", a[i], " \n"[i == n]);
	fflush(stdout);
	
	return 0;
}

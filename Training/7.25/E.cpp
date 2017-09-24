#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;
double a[111111];
int n;

int main() {
	cin >> n;
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;
	double mx = -100000000.0, id_mx = 0;
	double mn = 1.0, id_mn = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &a[i]);
		if (a[i] > 1.0 + eps) {
			++s1;
			continue;
		}
		if (a[i] > 0.0 + eps) {
			++s2;
			continue;
		}
		if (a[i] > 0.0 - eps) {
			++s3;
			continue;
		}
		if (a[i] > -1.0 - eps) {
			++s4;
			if (a[i] < mn + eps) {
				mn = a[i];
				id_mn = i;
			}
			continue;
		}
		++s5;
		if (a[i] > mx - eps) {
			mx = a[i];
			id_mx = i;
		}
	}
//	cout << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << endl;
	if (s1 == 0 && s2 == 0 && s4 + s5 <= 1) {
		cout << 1 << endl;
		for (int i = 1; i <= n; ++i) {
			if (a[i] < eps && a[i] > -eps) {
				cout << i << endl;
				return 0;
			}
		}
	}
	if (s1 == 0 && s5 == 0)
	if (s5 == 0) {
		cout << s1 << endl;
		int flag = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] > 1.0 + eps) {
				if (flag) {
					printf(" ");
				} else {
					flag = 1;
				}
				printf("%d", i);
			}
		}
		cout << endl;
		return 0;
	}
	
	double ss1 = fabs(mn), ss2 = fabs(1. / mx);
	//cout << ss1 << " " << ss2 << endl;
	
	if (s4 == 0 || ss2 > ss1 - eps) {
		cout << s1 + s5 - 1 << endl;
		int flag = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] > 1.0 + eps || a[i] < -1.0 - eps && i != id_mx) {
				if (flag) {
					printf(" ");
				} else {
					flag = 1;
				}
				printf("%d", i);
			}
		}
		cout << endl;
	} else {
		cout << s1 + s5 + 1 << endl;
		int flag = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] > 1.0 + eps || a[i] < -1.0 - eps || i == id_mn) {
				if (flag) {
					printf(" ");
				} else {
					flag = 1;
				}
				printf("%d", i);
			}
		}
		cout << endl;
	}
}

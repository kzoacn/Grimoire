#include <bits/stdc++.h>
using namespace std;

const int N = 11111;
int testcase;
char s1[N], s2[N], s3[N];

inline bool isalphabet(char c) {
	return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

int main() {
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%s%s", s1, s2);
		int n = strlen(s1), m = strlen(s2);
		bool f1 = false, f2 = false, f3 = false, f4 = false;
		if (n == m) {
			f1 = true;
			for (int i = 0; i < n; ++i) {
				if (s1[i] != s2[i]) {
					f1 = false;
				}
			}
			if (f1) {
				printf("Case %d: Login successful.\n", cs);
				continue;
			}
		}
		if (n == m) {
			f2 = true;
			for (int i = 0; i < n; ++i) {
				if (!isalphabet(s1[i]) && isalphabet(s2[i])) {
					f2 = false;
					break;
				}
				if (!isalphabet(s1[i])) {
					continue;
				}
				if (s1[i] <= 'Z' && s1[i] - 'A' + 'a' != s2[i] || s1[i] >= 'a' && s1[i] - 'a' + 'A' != s2[i]) {
					f2 = false;
					break;
				}
			}
		}
		int l = 0;
		for (int i = 0; i < n; ++i) {
			if (s1[i] < '0' || s1[i] > '9') {
				s3[l++] = s1[i];
			}
		}
		if (l == m && l < n) {
			f3 = true;
			f4 = true;
			for (int i = 0; i < m; ++i) {
				if (s2[i] != s3[i]) {
					f3 = false;
					break;
				}
			}
			n = l;
			for (int i = 0; i < n; ++i) {
				s1[i] = s3[i];
			}
			for (int i = 0; i < n; ++i) {
				if (!isalphabet(s1[i]) && isalphabet(s2[i])) {
					f4 = false;
					break;
				}
				if (!isalphabet(s1[i])) {
					continue;
				}
				if (s1[i] <= 'Z' && s1[i] - 'A' + 'a' != s2[i] || s1[i] >= 'a' && s1[i] - 'a' + 'A' != s2[i]) {
					f4 = false;
					break;
				}
			}
		}
		printf("Case %d: Wrong password.", cs);
		if (!f2 && !f3 && !f4) {
			puts("");
		} else 
		if (!f2 && f3) {
			puts(" Please, check your num lock key.");
		} else 
		if (f2 && !f3 && !f4) {
			puts(" Please, check your caps lock key.");
		} else 
		if (1) {
			puts(" Please, check your caps lock and num lock keys.");
		}
	}
 }

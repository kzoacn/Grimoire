#include <bits/stdc++.h>
using namespace std;

char s[2111111];
int testcase;

int main() {
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%s", s + 1);
		int l = strlen(s + 1);
		bool flag = true;
		int ss = 0;
		for (int i = 1; i <= l; ++i) {
			if (s[i] != 'c' && s[i] != 'f') {
			//cout << i << " " << s[i] << endl;
				flag = false;
				break;
			}
			ss += s[i] == 'c';
		}
		if (!flag) {
			printf("Case #%d: %d\n", cs, -1);
			continue;
		}
		//cout << ss << endl;
		if (!ss) {
			/* (l > 2) {
				flag = false;
			}
			ss = 1;*/
			ss = (l + 1) / 2;
		} else {
			if (l <= 2) {
				flag = false;
			}
			for (int i = 1; i <= l; ++i) {
				s[i + l] = s[i];
			}
			for (int i = 1; i <= l; ++i) {
				if (s[i] == 'c' && (s[i + 1] == 'c' || s[i + 2] == 'c')) {
					flag = false;
					break;
				}
			}
		}
		printf("Case #%d: %d\n", cs, flag == true ? ss : -1);
	}
}

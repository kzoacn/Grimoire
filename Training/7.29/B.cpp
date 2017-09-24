#include <bits/stdc++.h>

char s1[15], s2[15], ss[15];
int l1, l2, ls;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%s%s", s1, s2);
		l1 = strlen(s1);
		l2 = strlen(s2);
		
		bool flag = 1;
		for (int i = 0; i < l1 || i < l2; ++i)
			if (s1[i] != s2[i]) {
				flag = 0; break;
			}
		
		printf("Case %d: ", kase);
		
		if (flag) {
			puts("Login successful.");
			continue;
		}
		
		// capslock
		
		ls = 0;
		for (int i = 0; i < l1; ++i) {
			ss[ls++] = s1[i];
		}
		ss[ls] = '\0';
		
		for (int i = 0; i < ls; ++i) {
			if (ss[i] >= 'a' && ss[i] <= 'z') ss[i] = ss[i] - 'a' + 'A';
			else if (ss[i] >= 'A' && ss[i] <= 'Z') ss[i] = ss[i] - 'A' + 'a';
		}
		
		flag = 1;
		for (int i = 0; i < ls || i < l2; ++i)
			if (ss[i] != s2[i]) {
				flag = 0; break;
			}
		
		if (flag) {
			puts("Wrong password. Please, check your caps lock key.");
			continue;
		}
		
		// numlock & capslock
		
		ls = 0;
		for (int i = 0; i < l1; ++i) {
			if (s1[i] < '0' || s1[i] > '9')
				ss[ls++] = s1[i];
		}
		ss[ls] = '\0';
		
		for (int i = 0; i < ls; ++i) {
			if (ss[i] >= 'a' && ss[i] <= 'z') ss[i] = ss[i] - 'a' + 'A';
			else if (ss[i] >= 'A' && ss[i] <= 'Z') ss[i] = ss[i] - 'A' + 'a';
		}
		
		flag = 1;
		for (int i = 0; i < ls || i < l2; ++i)
			if (ss[i] != s2[i]) {
				flag = 0; break;
			}
		
		if (flag) {
			puts("Wrong password. Please, check your caps lock and num lock keys.");
			continue;
		}
		
		// numlock
		
		ls = 0;
		for (int i = 0; i < l1; ++i) {
			if (s1[i] < '0' || s1[i] > '9')
				ss[ls++] = s1[i];
		}
		ss[ls] = '\0';
		
		flag = 1;
		for (int i = 0; i < ls || i < l2; ++i)
			if (ss[i] != s2[i]) {
				flag = 0; break;
			}
		
		if (flag) {
			puts("Wrong password. Please, check your num lock key.");
			continue;
		}
		
		puts("Wrong password.");
	}
	
	return 0;
}

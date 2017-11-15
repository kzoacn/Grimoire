#include <bits/stdc++.h>

const int MAXN = 5e6 + 5;

int fail[MAXN];

char w[MAXN], p[MAXN];
int lw, lp;

char stack[MAXN]; int top;
int match[MAXN];

void get_fail() {
	fail[0] = fail[1] = 0;
	for (int i = 2; i <= lw; ++i) {
		int j = fail[i - 1];
		while (j && w[j + 1] != w[i]) j = fail[j];
		fail[i] = j;
		if (w[j + 1] == w[i]) ++fail[i];
	}
}

int main() {
	while (~scanf("%s%s", w + 1, p + 1)) {
		lw = strlen(w + 1);
		lp = strlen(p + 1);
		
		get_fail();
		
		top = 0;
		for (int i = 1; i <= lp; ++i) {
			int j = match[top];
			while (j && w[j + 1] != p[i]) j = fail[j];
			if (w[j + 1] == p[i]) ++j;
			if (j == lw) top -= lw - 1;
			else {
				stack[++top] = p[i];
				match[top] = j;
			}
		}
		
		for (int i = 1; i <= top; ++i)
			putchar(stack[i]);
		putchar('\n');
	}
	
	return 0;
}

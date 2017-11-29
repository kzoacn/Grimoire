#include <bits/stdc++.h>

typedef long long LL;

char num[3][15], opr;

bool appear[10];

inline bool isDigit(char x) {
	if (x >= '0' && x <= '9') appear[x - '0'] = 1;
	return (x >= '0' && x <= '9') || x == '?';
}

void Input() {
	static char ch;
	
	memset(appear, 0, sizeof appear);
	
	int tmp = 0;
	for (ch = getchar(); ~ch && !isDigit(ch); ch = getchar()) if (ch == '-') num[0][tmp++] = '-';
	for (; isDigit(ch); ch = getchar()) num[0][tmp++] = ch;
	num[0][tmp] = '\0';
	
	opr = ch;
	
	tmp = 0;
	for (ch = getchar(); ~ch && !isDigit(ch); ch = getchar()) if (ch == '-') num[1][tmp++] = '-';
	for (; isDigit(ch); ch = getchar()) num[1][tmp++] = ch;
	num[1][tmp] = '\0';
	
	tmp = 0;
	for (ch = getchar(); ~ch && !isDigit(ch); ch = getchar()) if (ch == '-') num[2][tmp++] = '-';
	for (; isDigit(ch); ch = getchar()) num[2][tmp++] = ch;
	num[2][tmp] = '\0';
}

bool Check(int x) {
	static char s[15];
	static LL a[3];
	
	for (int i = 0; i < 3; ++i) {
		memcpy(s, num[i], sizeof num[i]);
		
		for (char *ch = s; *ch; ++ch)
			if (*ch == '?') *ch = x + '0';
		
		if (strlen(s) > 1 && (s[0] == '0' || (s[0] == '-' && s[1] == '0')))
			return 0;
		
		sscanf(s, "%lld", a + i);
	}
	if (opr == '+')
		return a[0] + a[1] == a[2];
	else if (opr == '-')
		return a[0] - a[1] == a[2];
	return a[0] * a[1] == a[2];
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	while (caseCnt--) {
		Input();
		
		int ans = -1;
		for (int i = 0; i <= 9; ++i)
			if (!appear[i] && Check(i)) {
				ans = i; break;
			}
		
		printf("%d\n", ans);
	}
	
	return 0;
}

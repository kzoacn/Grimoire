#include <bits/stdc++.h>

char A[2505], B[2505];
int lena, lenb;

bool dp[2505][2505];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%s%s", A, B);
		lena = strlen(A);
		lenb = strlen(B);
		
		for (int i = 0; i <= lena; ++i)
			memset(dp[i], 0, sizeof(bool) * (lenb + 1));
		
		dp[0][0] = 1;
		for (int i = 0; i <= lena; ++i)
			for (int j = 0; j < lenb; ++j) {
				if (!dp[i][j]) continue;
				
				if (B[j] == '*') {
					dp[i][j + 1] = 1;
					if (i && i < lena && A[i - 1] == A[i])
						dp[i + 1][j] = 1;
				}
				else {
					if (B[j + 1] == '*')
						dp[i][j + 2] = 1;
					if (B[j] == '.')
						dp[i + 1][j + 1] = 1;
					else if (A[i] == B[j])
						dp[i + 1][j + 1] = 1;
				}
			}
		
		puts(dp[lena][lenb] ? "yes" : "no");
	}
	
	return 0;
}

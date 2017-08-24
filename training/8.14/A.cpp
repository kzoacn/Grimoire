#include <bits/stdc++.h>

const int lim = 50000;

int n, m, q;

bool cnta[50005], cntb[50005];

struct Query {
	int x, id;
	
	Query() {
		x = 0;
	}
	
	bool operator < (const Query &rhs) const {
		return x < rhs.x;
	}
	
	void scan(int ID) {
		scanf("%d", &x); id = ID;
	}
} qry[50005];

int ans[50005];

std::bitset<50005> A, B, C;

void print() {
printf("A: ");
	for (int i = 0; i <= 10; ++i) printf("%d%c", (int)A[i], " \n"[i == 10]);
printf("B: ");
	for (int i = 0; i <= 10; ++i) printf("%d%c", (int)B[i], " \n"[i == 10]);
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(cnta, 0, sizeof cnta);
		memset(cntb, 0, sizeof cntb);
		A.reset(); B.reset();
		
		scanf("%d%d%d", &n, &m, &q);
		for (int x, i = 1; i <= n; ++i) {
			scanf("%d", &x); cnta[x] ^= 1;
		}
		for (int x, i = 1; i <= m; ++i) {
			scanf("%d", &x); cntb[x] ^= 1;
		}
		for (int i = 1; i <= q; ++i) qry[i].scan(i);
		
		for (int i = 1; i <= lim; ++i) A[i] = cnta[i];
		for (int i = 1; i <= lim; ++i) if (cntb[i])
			for (int j = 0; j <= lim; j += i)
				B[j] = B[j] ^ 1;
		
		std::sort(qry + 1, qry + q + 1);
		
		int t = 1;
		for (int i = 1; i <= q; ++i) {
			if (i > 1 && qry[i].x == qry[i - 1].x) {
				ans[qry[i].id] = ans[qry[i - 1].id];
				continue;
			}
			
			for (; t <= qry[i].x; ++t) if (cntb[t])
				for (int j = 0; j <= lim; j += t)
					B[j] = B[j] ^ 1;
			
			A >>= (qry[i].x - qry[i - 1].x);
			
			//print();
			
			ans[qry[i].id] = (A & B).count() & 1;
		}
		
		for (int i = 1; i <= q; ++i)
			printf("%d\n", ans[i]);
	}
	
	return 0;
}

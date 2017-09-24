#include <bits/stdc++.h>

namespace SAM {
	int to[100005 << 1][26], parent[100005 << 1], step[100005 << 1], right[100005 << 1], tot;
	int sam_len, root, np;
	
	int newnode(int STEP) {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		parent[tot] = 0;
		step[tot] = STEP;
		right[tot] = 0;
		return tot;
	}
	
	void init() {
		tot = 0;
		sam_len = 0;
		
		root = np = newnode(0);
	}
	
	void extend(char ch) {
		int x = ch - 'a';
		int last = np; np = newnode(++sam_len); right[np] = 1;
		for (; last && !to[last][x]; last = parent[last])
			to[last][x] = np;
		if (!last) parent[np] = root;
		else {
			int q = to[last][x];
			if (step[q] == step[last] + 1) parent[np] = q;
			else {
				int nq = newnode(step[last] + 1);
				memcpy(to[nq], to[q], sizeof to[q]);
				parent[nq] = parent[q];
				parent[q] = parent[np] = nq;
				for (; last && to[last][x] == q; last = parent[last])
					to[last][x] = nq;
			}
		}
	}
	
	int sorted[100005 << 1], cnt[100005];
	
	long long radix_sort(int k) {
		memset(cnt, 0, sizeof cnt);
		memset(sorted, 0, sizeof sorted);
		
		for (int i = 1; i <= tot; ++i) ++cnt[step[i]];
		for (int i = 1; i <= sam_len; ++i) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= tot; ++i) sorted[cnt[step[i]]--] = i;
		
		long long res = 0;
		for (int I = tot; I; --I) {
			int i = sorted[I];
			if (right[i] == k) res += step[i] - step[parent[i]];
			right[parent[i]] += right[i];
		}
		return res;
	}
}

char s[100005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int k;
		
		scanf("%d%s", &k, s + 1);
		int len = strlen(s + 1);
		
		SAM::init();
		for (int i = 1; i <= len; ++i)
			SAM::extend(s[i]);
		
		printf("%lld\n", SAM::radix_sort(k));
	}
	
	return 0;
}

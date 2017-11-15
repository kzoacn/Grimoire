#include <bits/stdc++.h>

const int MAXN = 150005;

int n, m;
int s[MAXN], ansS[MAXN];

namespace SAM {
	int to[MAXN << 1][10], parent[MAXN << 1], step[MAXN << 1], right[MAXN << 1], ends[MAXN << 1], tot;
	int root, np, sam_len;
	
	int newnode(int stp) {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		parent[tot] = 0;
		step[tot] = stp;
		right[tot] = 0;
		ends[tot] = stp;
		return tot;
	}
	
	int newcopy(int smp) {
		++tot;
		memcpy(to[tot], to[smp], sizeof to[smp]);
		parent[tot] = parent[smp];
		step[tot] = step[smp];
		right[tot] = right[smp];
		ends[tot] = ends[smp];
		return tot;
	}
	
	void init() {
		tot = 0;
		root = np = newnode(sam_len = 0);
	}
	
	void extend(int x) {
		int last = np; np = newnode(++sam_len); right[np] = 1;
		for (; last && !to[last][x]; last = parent[last])
			to[last][x] = np;
		if (!last) parent[np] = root;
		else {
			int q = to[last][x];
			if (step[q] == step[last] + 1) parent[np] = q;
			else {
				int nq = newcopy(q); right[nq] = 0; ends[nq] = 0;
				step[nq] = step[last] + 1;
				parent[q] = parent[np] = nq;
				for (; last && to[last][x] == q; last = parent[last])
					to[last][x] = nq;
			}
		}
	}
	
	int sorted[MAXN << 1], cnt[MAXN];
	
	void radix_sort() {
		for (int i = 1; i <= tot; ++i) ++cnt[step[i]];
		for (int i = 1; i <= sam_len; ++i) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= tot; ++i) sorted[cnt[step[i]]--] = i;
	}
	
	std::pair<int, int> solve() {
		std::pair<int, int> res(0, 0);
		int last = 0;
		for (int ii = tot; ii; --ii) {
			int i = sorted[ii];
			if (1LL * right[i] * step[i] > 1LL * res.first * res.second) {
				res = std::make_pair(step[i], right[i]);
				last = ends[i];
			}
			right[parent[i]] += right[i];
			ends[parent[i]] = std::max(ends[parent[i]], ends[i]);
		}
		
		for (int i = last - res.first + 1; i <= last; ++i)
			ansS[i - last + res.first] = s[i];
		return res;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	SAM::init();
	for (int i = 1; i <= n; ++i) {
		scanf("%d", s + i);
		SAM::extend(s[i] - 1);
	}
	
	SAM::radix_sort();
	auto ans = SAM::solve();//
	printf("%lld\n%d\n", 1LL * ans.first * ans.second, ans.first);//
	for (int i = 1; i <= ans.first; ++i)
		printf("%d%c", ansS[i], " \n"[i == ans.first]);
	
	return 0;
}

#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

char s[100005]; int len;

namespace SAM {
	struct Node *pool_pointer;
	struct Node {
		Node *to[26], *p;
		int step, min_r;
		
		Node(int step = 0, int min_r = INF): step(step), min_r(min_r) {
			memset(to, 0, sizeof to); p = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[100005 << 1], *root, *np;
	int sam_len;
	
	void init() {
		pool_pointer = pool;
		root = np = new Node(sam_len = 0);
	}
	
	void extend(char ch) {
		static Node *last, *q, *nq;
		
		int x = ch - 'a';
		last = np;
		++sam_len; np = new Node(sam_len, sam_len);
		for (; last && !last->to[x]; last = last->p)
			last->to[x] = np;
		if (!last) np->p = root;
		else {
			q = last->to[x];
			if (q->step == last->step + 1) np->p = q;
			else {
				nq = new Node(*q);
				nq->step = last->step + 1;
				q->p = np->p = nq;
				for (; last && last->to[x] == q; last = last->p)
					last->to[x] = nq;
			}
		}
	}
	
	Node *sorted[100005 << 1];
	int cnt[100005], tot;
	
	void radix_sort() {
		memset(cnt, 0, sizeof cnt); tot = 0;
		for (Node *k = pool; k != pool_pointer; ++k) ++cnt[k->step], ++tot;
		for (int i = sam_len; i >= 0; --i) cnt[i] += cnt[i + 1];
		for (Node *k = pool; k != pool_pointer; ++k) sorted[--cnt[k->step]] = k;
		
		for (int i = 0; i < tot; ++i) if (sorted[i]->p) sorted[i]->p->min_r = std::min(sorted[i]->p->min_r, sorted[i]->min_r);
	}
	
	std::pair<int, int> run_in_sam(int st) {
		Node *k = root; int length = 0, i = st;
		while (i < len && k->to[s[i] - 'a'] && k->to[s[i] - 'a']->min_r - (length + 1) < st) {
			k = k->to[s[i] - 'a'];
			++length; ++i;
		}
		if (length == 0 || (k->min_r - length >= st)) return std::make_pair(-1, (int)s[st]);
		return std::make_pair(length, k->min_r - length);
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%s", s); len = strlen(s);
		
		SAM::init();
		for (int i = 0; i < len; ++i) SAM::extend(s[i]);
		
		SAM::radix_sort();
		
		printf("Case #%d:\n", kase);
		
		std::pair<int, int> tmp;
		for (int i = 0; i < len; ) {
			tmp = SAM::run_in_sam(i);
			printf("%d %d\n", tmp.first, tmp.second);
			i += std::max(tmp.first, 1);
		}
	}
	
	return 0;
}

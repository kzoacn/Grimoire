#include <bits/stdc++.h>

typedef std::pair<int, int> PII;
#define mkpair std::make_pair

const int MAXN = 1e6 + 5;

char S[MAXN], T[MAXN];
int lenS, lenT;

int F(int l, int r) { // 1-based
	return (r - l + 1) - std::max(l - 1, lenS - r);
}

namespace SAM {
	struct Node *pool_pointer;
	struct Node {
		Node *to[26], *parent;
		int step;
		
		Node(int STEP = 0): step(STEP) {
			memset(to, 0, sizeof to);
			parent = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[MAXN << 1], *root, *np;
	int sam_len;
	
	void init() {
		pool_pointer = pool;
		root = np = new Node(sam_len = 0);
	}
	
	void extend(char ch) {
		static Node *last, *q, *nq;
		
		int x = ch - 'a';
		last = np; np = new Node(++sam_len);
		for (; last && !last->to[x]; last = last->parent)
			last->to[x] = np;
		if (!last) np->parent = root;
		else {
			q = last->to[x];
			if (q->step == last->step + 1) np->parent = q;
			else {
				nq = new Node(*q);
				nq->step = last->step + 1;
				np->parent = q->parent = nq;
				for (; last && last->to[x] == q; last = last->parent)
					last->to[x] = nq;
			}
		}
	}
	
	PII solve() {
		Node *k = root;
		int mx = -0x3f3f3f3f;
		PII ans(0, 0);
		int len = 0;
		for (int i = 1; i <= lenS; ++i) {
			int x = S[i] - 'a';
			while (k != root && !k->to[x])
				k = k->parent;
			len = std::min(len, k->step);
			
			if (k->to[x]) {
				k = k->to[x];
				++len;
			}
			int L = i - len + 1, R = i;
			
//			fprintf(stderr, "(%d, %d)\n", L, R);
			
			if (len && F(L, R) > mx) {
				mx = F(L, R);
				ans = mkpair(L, R);
			}
		}
		return ans;
	}
}

int main() {
	scanf("%s%s", S + 1, T + 1);
	
	lenS = strlen(S + 1);
	lenT = strlen(T + 1);
	
	SAM::init();
	for (int i = 1; i <= lenT; ++i)
		SAM::extend(T[i]);
	
//	std::cerr << "building completed" << std::endl;
	
	PII ans = SAM::solve();
	
	printf("%d %d\n", ans.first - 1, ans.second - 1);
	
	return 0;
}

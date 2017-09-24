#include <bits/stdc++.h>

typedef long long ll;

namespace Splay {
	struct Node *pool_pointer;
	struct Node {
		Node *ch[2], *fa;
		int val, size;
		ll sum;
		bool posi;
		
		Node(int VAL = 0): val(VAL) {
			ch[0] = ch[1] = fa = 0;
			sum = val;
			posi = val > 0;
			size = 1;
		}
		
		int Size() { return this ? size : 0; }
		ll Sum() { return this ? sum : 0; }
		bool Posi() { return this ? posi : 0; }
		
		void update() {
			size = 1 + ch[0]->Size() + ch[1]->Size();
			sum = val + ch[0]->Sum() + ch[1]->Sum();
			posi = (val > 0) | ch[0]->Posi() | ch[1]->Posi();
		}
		
		int which() {
			return !fa ? -1 : fa->ch[1] == this;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[100005 << 1], *root, *posi[100005], *nega[100005];
	
	void init() {
		root = 0;
		memset(posi, 0, sizeof posi);
		memset(nega, 0, sizeof nega);
		pool_pointer = pool;
	}
	
	void print(Node *k) {
		if (!k) return;
		print(k->ch[0]);
		std::cerr << k->val << " ";
		print(k->ch[1]);
	}
	
	void print2(Node *k) {
		if (!k) return;
		std::cerr << k->val << " -> ";
		if (k->ch[0]) std::cerr << k->ch[0]->val << " ";
		if (k->ch[1]) std::cerr << k->ch[1]->val << " ";
		std::cerr << std::endl;
		print2(k->ch[0]);
		print2(k->ch[1]);
	}
	
	// --------
	
	void rotate(Node *k) {
		Node *p = k->fa;
		int l = k->which(), r = l ^ 1;
		
		k->fa = p->fa;
		if (p->fa) p->fa->ch[p->which()] = k;
		p->fa = k;
		
		p->ch[l] = k->ch[r];
		if (k->ch[r]) k->ch[r]->fa = p;
		k->ch[r] = p;
		
		p->update();
		k->update();
	}
	
	void splay(Node *k, Node *aim_fa = 0) {
		while (k->fa != aim_fa) {
			Node *p = k->fa;
			if (p->fa != aim_fa) {
				if (k->which() ^ p->which()) rotate(k);
				else rotate(p);
			}
			rotate(k);
		}
		if (!aim_fa) root = k;
	}
	
	Node *first_posi(Node *k) {
		if (!k || !k->Posi()) return 0;
		if (k->Size() == 1) return k;
		return k->ch[0]->Posi() ? first_posi(k->ch[0]) : (k->val > 0 ? k : first_posi(k->ch[1]));
	}
	
	Node *last(Node *k) {
#ifdef LOCAL
		assert(k->Size() > 0);
#endif
		if (k->ch[1]) return last(k->ch[1]);
		return k;
	}
	
	void insert(Node *&k, Node *fa, int kth, int val) {
		if (!k) {
			k = new Node(val);
			k->fa = fa;
			splay(k);
			return;
		}
		if (kth <= k->ch[0]->Size()) insert(k->ch[0], k, kth, val);
		else insert(k->ch[1], k, kth - k->ch[0]->Size() - 1, val);
	}
	
	void del(Node *k) {
		splay(k);
//		print2(k);
		for (int i = 0; i < 2; ++i) if (!k->ch[i ^ 1]) {
			if (k->ch[i]) {
				k->ch[i]->fa = 0;
				k->ch[i]->update();
			}
			root = k->ch[i];
			return;
		}
		Node *p = last(k->ch[0]);
		splay(p, k);
		
		p->fa = 0;
		
		k->ch[1]->fa = p;
		p->ch[1] = k->ch[1];
		p->update();
		root = p;
	}
	
	// --------
	
	void Insert(int kth, int x) {
		insert(root, 0, kth, x);
		Node *k = root, *p = first_posi(k->ch[1]);
		posi[x] = k;
		if (p) {
//			std::cerr << "p->val = " << p->val << ", p->Size() = " << p->Size() << std::endl;
			p = nega[p->val];
			splay(p);
		}
		int k_rk = kth, p_rk = root->ch[0]->Size();
		if (!p) {
			insert(root, 0, root->Size(), -x);
			nega[x] = root;
		}
		else if (k_rk + 1 > p_rk) {
			insert(root, 0, k_rk + 1, -x);
			nega[x] = root;
		}
		else {
			insert(root, 0, p_rk, -x);
			nega[x] = root;
		}
	}
	
	void Delete(int x) {
		del(posi[x]);
		del(nega[x]);
		
		posi[x] = nega[x] = 0;
	}
	
	ll Query(int x) {
		splay(posi[x]);
		splay(nega[x], root);
		
		return root->ch[1]->ch[0]->Sum();
	}
}

std::set<int> st;

int main() {
	static int n, x, p; static char s[10];
	
	for (int kase = 1; ~scanf("%d", &n); ++kase) {
		Splay::init();
		
		std::set<int>().swap(st);
		for (int i = 1; i <= n + 1; ++i)
			st.insert(i);
		
		printf("Case #%d:\n", kase);
		
		while (n--) {
			scanf("%s%d", s, &x);
			
//			std::cerr << s << " " << x << std::endl;
			
			switch (*s) {
				case 'i':
					p = x; x = *st.begin();
					st.erase(st.begin());
//					std::cerr << "INSERT " << x << " AT " << p << std::endl;
					Splay::Insert(p, x);
					break;
				case 'r':
					Splay::Delete(x);
					st.insert(x);
					break;
				case 'q':
					if (st.count(x))
						puts("0");
					else
						printf("%lld\n", Splay::Query(x));
					break;
			}
			
//			Splay::print(Splay::root);
//			puts("");
//			Splay::print2(Splay::root);
		}
	}
	
	return 0;
}

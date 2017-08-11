#include <bits/stdc++.h>

int n;

struct Peo {
	int h, k;
	
	Peo() {}
	Peo(int h, int k): h(h), k(k) {}
	
	bool operator < (const Peo &rhs) const {
		return h > rhs.h;
	}
	
	void scan() {
		scanf("%d%d", &h, &k);
	}
} peo[100005];

namespace Splay {
	struct Node *pool_pointer;
	struct Node {
		Node *ch[2], *fa;
		int val, sz;
		
		Node(int val = 0): val(val) {
			ch[0] = ch[1] = fa = 0;
			sz = 1;
		}
		
		int size() { return this ? sz : 0; }
		
		void update() {
			sz = ch[0]->size() + ch[1]->size() + 1;
		}
		
		int which() {
			if (!fa) return -1;
			return this == fa->ch[1];
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[100005], *root, *L, *R;
	
	void init() {
		pool_pointer = pool;
		root = new Node(-1);
		root->ch[1] = new Node(-1);
		root->ch[1]->fa = root;
		root->update();
		
		L = root, R = root->ch[1];
	}
	
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
	
	void splay(Node *k, Node *aim_fa) {
		while (k->fa != aim_fa) {
			Node *p = k->fa;
			if (p->fa != aim_fa) {
				if (p->which() != k->which()) rotate(k);
				else rotate(p);
			}
			rotate(k);
		}
		if (!aim_fa) root = k;
	}
	
	Node *kth_node(Node *k, int kth) {
		if (k->ch[0]->size() + 1 == kth) return k;
		if (k->ch[0]->size() + 1 < kth) return kth_node(k->ch[1], kth - k->ch[0]->size() - 1);
		return kth_node(k->ch[0], kth);
	}
	
	void print(Node *k, char endChar) {
		if (!k) return;
		print(k->ch[0], ' ');
		if (k->ch[1]) {
			printf("%d ", k->val);
			print(k->ch[1], endChar);
		}
		else printf("%d%c", k->val, endChar);
	}
	
	//
	
	int cnt() {
		return root->size() - 2;
	}
	
	void insert(int val, int pos) {
		splay(kth_node(root, pos + 1), 0);
		
		Node *k = new Node(val);
		
		k->ch[1] = root->ch[1];
		k->fa = root;
		if (root->ch[1]) root->ch[1]->fa = k;
		root->ch[1] = k;
		k->update();
		root->update();
	}
	
	void print() {
		splay(L, 0);
		splay(R, L);
		print(root->ch[1]->ch[0], '\n');
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) peo[i].scan();
		
		std::sort(peo + 1, peo + n + 1);
		Splay::init();
		
		bool flag = 1;
		
		for (int i = 1; i <= n; ++i) {
			if (peo[i].k > Splay::cnt()) {
				flag = 0; break;
			}
			peo[i].k = std::min(peo[i].k, Splay::cnt() - peo[i].k);
			
			Splay::insert(peo[i].h, peo[i].k);
		}
		
		printf("Case #%d: ", kase);
		if (!flag)
			puts("impossible");
		else
			Splay::print();
	}
	
	return 0;
}

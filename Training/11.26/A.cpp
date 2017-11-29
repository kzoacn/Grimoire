#include <bits/stdc++.h>

using namespace std;

const int MAXL = 1.1e6 + 5;

bool ValidDomain(string s) {
	for (char ch: s)
		if (!islower(ch) && !isdigit(ch) && ch != '.' && ch != '-' && ch != '#' && ch != '*')
			return 0;
	if (s.front() == '.' || s.back() == '.') return 0;
	for (int i = 1; i < s.length(); ++i) {
		if (s[i] == '#' || s[i] == '*')
			return 0;
		if (s[i] == '.' && s[i - 1] == '.')
			return 0;
	}
	if ((s[0] == '#' || s[0] == '*') && s.length() > 1 && s[1] != '.')
		return 0;
	if (s.front() == '-' || s.back() == '-') return 0;
	for (int i = 1; i < s.length() - 1; ++i) {
		if (s[i] == '-' && (!islower(s[i - 1]) || !islower(s[i + 1])))
			return 0;
	}
	return 1;
}

bool ValidVPNName(string s) {
	for (char ch: s)
		if (!islower(ch) && !isdigit(ch) && ch != '-')
			return 0;
	if (!islower(s.front()))
		return 0;
	if (s.back() == '-') return 0;
	for (int i = 1; i < s.length() - 1; ++i)
		if (s[i] == '-' && (!islower(s[i - 1]) || !islower(s[i + 1])))
			return 0;
	return 1;
}

namespace Trie {
	struct Node *pool_pointer;
	struct Node {
		map<string, Node *> sons;
		int cnt, size;
		bool hasStar, hasJing;
		
		Node() {
			sons.clear();
			cnt = size = 0;
			hasStar = hasJing = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[MAXL], *root;
	
	string vec[MAXL]; int tot;
	
	void init() {
		pool_pointer = pool;
		root = new Node();
	}
	
	bool insert(Node *&k, int idx, bool isnew) {
		/*if (!k) {
			k = new Node();
			isnew = 1;
		}
		if (idx == 0) {
			if (isstar && k->size) return 0;
			k->size += (isnew || k->sons.size() || k->sons.count("*"));
			k->cnt = isnew || k->sons.size() || k->sons.count("*");
			return isnew || k->sons.size() || k->sons.count("*");
		}
		if (k->sons.count("*")) return 0;
		k->size += insert(k->sons[vec[idx]], idx - 1, isnew, vec[idx] == "*");*/
		if (!k) {
			k = new Node();
			isnew = 1;
		}
		if (idx == 0) {
			if (isnew || !k->cnt) {
				++k->size;
				++k->cnt;
				return 1;
			}
			return 0;
		}
		if (vec[idx] == "*") {
			if (k->sons.size()) return 0;
			bool tmp = insert(k->sons["*"], idx - 1, 1);
			k->size += tmp;
			return tmp;
		}
		if (k->sons.count("*")) return 0;
		if (vec[1] == "#" && k->sons.count("#")) return 0;
		bool tmp = insert(k->sons[vec[idx]], idx - 1, isnew);
		k->size += tmp;
		return tmp;
	}
	
	bool Insert(string s) {
		static string tmp;
		
		tot = 0;
		tmp = "";
		s.push_back('.');
		
		for (char ch: s) {
			if (ch == '.') {
				vec[++tot] = tmp;
				tmp = "";
			}
			else tmp.push_back(ch);
		}
		return insert(root, tot, 0);
	}
	
	int query(Node *k, int idx) {
		/*if (!k) return 0;
		if (!idx) return k->sons.size() == 0;
		if (vec[idx] == "*") return k->size;
		if (k->sons.count("#")) {
		
		}
		return query(k->sons[vec[idx]], idx - 1);*/
		if (!k) return 0;
		if (vec[idx] == "*") {
			return k->size;
		}
		if (k->sons.count("*")) return 1;
		if (k->sons.count("#")) {
			int tmp = query(k->sons[vec[idx]], idx - 1);
			return tmp ? tmp : 1;
		}
		return query(k->sons[vec[idx]], idx - 1);
	}
	
	int Query(string s) {
		static string tmp;
		
		tot = 0;
		tmp = "";
		s.push_back('.');
		
		for (char ch: s) {
			if (ch == '.') {
				vec[++tot] = tmp;
				tmp = "";
			}
			else tmp.push_back(ch);
		}
		return query(root, tot);
	}
}

int main() {
	int n, m;
	string ss;
	
	while (~scanf("%d", &n)) {
		Trie::init();
		
		int invalid = 0;
		
		for (int i = 1; i <= n; ++i) {
			static char s[MAXL];
			
			scanf("%s", s);
			ss = string(s);
			scanf("%s", s);
			if (ValidDomain(ss) && ValidVPNName(string(s)))
				invalid += !Trie::Insert(ss);
			else ++invalid;
			
//			std::cerr << i << " " << invalid << std::endl;
		}
		
		printf("%d\n", invalid);
		
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) {
			static char s[MAXL];
			
			if (scanf("%s", s) == -1) {
				printf("%d\n", n - invalid);
				continue;
			}
			ss = string(s);
			
			if (!ValidDomain(ss)) {
				puts("0");
				continue;
			}
			printf("%d\n", Trie::Query(ss));
		}
	}
	
	return 0;
}

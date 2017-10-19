#include <bits/stdc++.h>

typedef long long ll;

typedef std::pair<int, int> pii;
#define mkpair std::make_pair

int trans[100];

ll sum = 0;
std::vector<pii> ans;

namespace Trie {
	int head[1000005], nxt[100005];
	
	int to[1000005][4], cnt[1000005], tot;
	int root;
	
	int newnode() {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		cnt[tot] = 0;
		head[tot] = 0;
		return tot;
	}
	
	void init() {
		tot = 0;
		root = newnode();
	}
	
	void insert(int &k, char *s, int id) {
		if (!k) k = newnode();
		++cnt[k];
		if (!*s) {
			nxt[id] = head[k]; head[k] = id;
			return;
		}
		insert(to[k][trans[(int)*s]], s + 1, id);
	}
	
	pii calc(int k, int depth) { // pair(0/1: left, id of the left word)
		if (!k) return mkpair(0, 0);
		
		pii left = mkpair(0, 0), tmp;
		
		for (int i = 0; i < 4; ++i) {
			tmp = calc(to[k][i], depth + 1);
			if (!tmp.first) continue;
			if (!left.first) left = tmp;
			else {
				sum += depth;
				ans.push_back(mkpair(left.second, tmp.second));
				left = mkpair(0, 0);
			}
		}
		for (int i = head[k]; i; i = nxt[i]) {
			if (!left.first) left = mkpair(1, i);
			else {
				sum += depth;
				ans.push_back(mkpair(left.second, i));
				left = mkpair(0, 0);
			}
		}
		return left;
	}
}

int n;
char s[1000005];

int main() {
	trans['A'] = 0;
	trans['C'] = 1;
	trans['G'] = 2;
	trans['T'] = 3;
	
	Trie::init();
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s);
		Trie::insert(Trie::root, s, i);
	}
	
	Trie::calc(Trie::root, 0);
	
	printf("%lld\n", sum);
	for (auto i: ans)
		printf("%d %d\n", i.first, i.second);
	
	return 0;
}

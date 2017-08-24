#include <bits/stdc++.h>

typedef long long ll;

const int Mod = 1e9 + 7;

template <class T>
void scan(T &x) {
	register char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

struct Node {
	int val, cnt;
	
	Node() {}
	Node(int val, int cnt): val(val), cnt(cnt) {}
} deq[250005 << 1]; int head, tail;

int n, a[250005], b[250005];

int main() {
	while (~scanf("%d", &n) && n) {
		head = 1; tail = 0;
		for (int i = 1; i <= n; ++i) {
			scan(a[i]);
			Node tmp(a[i] - i, 1);
			while (head <= tail && tmp.val > deq[tail].val) tmp.cnt += deq[tail--].cnt;
			deq[++tail] = tmp;
		}
		for (int i = 1; i <= n; ++i) scan(b[i]);
		
		std::sort(b + 1, b + n + 1);
		
		int l = 1;
		ll ans = 0;
		for (int i = 1; i <= n; ++i) {
			while (l < b[i]) {
				++l;
				if (!--deq[head].cnt) ++head;
			}
			ans += deq[head].val;
			Node tmp(deq[head].val - (n + i), 1);
			while (head <= tail && tmp.val > deq[tail].val) tmp.cnt += deq[tail--].cnt;
			deq[++tail] = tmp;
		}
		printf("%lld\n", ans % Mod);
	}
	
	return 0;
}

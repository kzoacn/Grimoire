#include <bits/stdc++.h>

using namespace std;

struct BigInteger {
	int bit[505], len;
	
	void reset() {
		memset(bit, 0, sizeof bit);
		len = 0;
	}
	
	BigInteger() {
		reset();
	}
	
	BigInteger &operator *= (int x) {
		for (int i = 0; i < len; ++i)
			bit[i] *= x;
		for (int i = 0; i < len; ++i) {
			bit[i + 1] += bit[i] / 10;
			bit[i] %= 10;
		}
		while (bit[len]) {
			bit[len + 1] = bit[len] / 10;
			bit[len] %= 10;
			++len;
		}
		return *this;
	}
	
	void dec() {
		for (int i = 0; i < len; ++i) {
			if (bit[i] != 0) {
				--bit[i];
				if (i == len - 1 && !bit[i])
					--len;
				return;
			}
			bit[i] = 9;
		}
	}
	
	void ONE() {
		reset();
		len = 1;
		bit[0] = 1;
	}
	
	void print(char end = '\n') {
		for (int i = len - 1; i >= 0; --i)
			putchar(bit[i] + '0');
		putchar(end);
	}
};

pair<string, int> nextVar() {
	static char ch;
	string res = ""; bool nega = 0;
	for (ch = getchar(); ~ch && !isalpha(ch); ch = getchar()) nega |= (ch == '~');
	if (ch == -1) return make_pair(res, -1);
	for (; isalpha(ch); ch = getchar()) res.push_back(ch);
	return make_pair(res, nega);
}

map<string, bool> vars;
bool oppo = 0;

int main() {
#ifndef LOCAL
	freopen("boolean.in", "r", stdin);
	freopen("boolean.out", "w", stdout);
#endif
	
	pair<string, int> var;
	while (~(var = nextVar()).second) {
		if (vars.count(var.first))
			oppo |= (vars[var.first] != var.second);
		else vars[var.first] = var.second;
	}
	
	BigInteger ans; ans.ONE();
	for (int i = vars.size(); i--; )
		ans *= 2;
	
	if (!oppo) ans.dec();
	
	ans.print();
	
	return 0;
}

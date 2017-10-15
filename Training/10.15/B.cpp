#include <bits/stdc++.h>

const char Switch[40] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int n, m, q;

std::bitset<36> a[2005];
std::bitset<1000> tmp[1005], bs[2005];

char ans[1005];
int bit[36];
bool fr[36];

void Gauss() {
	memset(fr, 0, sizeof fr);
	
	int now = 0;
	for (int i = 0; i < n; ++i) {
		int r = -1;
		for (int j = now; j <= q; ++j) if (a[j][i]) {
			r = j; break;
		}
		if (r == -1) {
			fr[i] = 1;
			continue;
		}
		std::swap(a[now], a[r]);
		std::swap(bs[now], bs[r]);
		for (int j = 0; j <= q; ++j) if (j != now && a[j][i]) {
			a[j] ^= a[now];
			bs[j] ^= bs[now];
		}
		bit[now] = i;
		++now;
	}
	/*
	std::cerr << now << std::endl;
	for (int i = 0; i <= q; ++i) {
		for (int j = 0; j < n; ++j)
			std::cerr << a[i][j];
		std::cerr << " ";
		for (int j = 0; j < m; ++j)
			std::cerr << bs[i][j];
		std::cerr << std::endl;
	}
	*/
	for (int i = now - 1; i >= 0; --i) {
		for (int j = bit[i] + 1; j < n; ++j) if (a[i][j] && fr[j]) {
			fr[i] = 1; break;
		}
		if (fr[i]) continue;
		for (int j = 0; j < m; ++j) if (bs[i][j])
			ans[j] = Switch[bit[i]];
	}
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &q) && (n || m || q)) {
		for (int i = 0; i < q; ++i) {
			static char s[1005];
			
			/*a[i].reset();
			bs[i].reset();
			tmp[i].reset();*/
			scanf("%s", s);
			for (int j = 0; j < n; ++j)
				a[i][j] = s[j] - '0';
			
			scanf("%s", s);
			for (int j = 0; j < m; ++j)
				tmp[i][j] = s[j] - '0';
			
			bs[i] = tmp[i];
			if (i) bs[i] ^= tmp[i - 1];
		}
		for (int i = 0; i < q; ++i) {
			a[q + i] = ~a[i];
			bs[q + i] = ~bs[i];
		}
		q <<= 1;
		for (int i = 0; i < n; ++i)
			a[q][i] = 1;
		for (int i = 0; i < m; ++i)
			bs[q][i] = 1;
		
		for (int i = 0; i < m; ++i)
			ans[i] = '?';
		ans[m] = '\0';
		
		Gauss();
		
		puts(ans);
		//std::cerr << std::endl;
	}
	
	return 0;
}

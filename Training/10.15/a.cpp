#include <bits/stdc++.h>
using namespace std;

int f[11111];

#define dp(x,y) f[(x) + (y)]

inline int &dp(int i, int j) {
	return f[i][j];
}

int main() {
	//cout << &dp(-10) << " " << &f[0] << " " << dp(-10) << endl;
}

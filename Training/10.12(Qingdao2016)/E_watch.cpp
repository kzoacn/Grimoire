#include <bits/stdc++.h>

int calc(int p) {
	int res = 1, x = 0, y = 1, z;
	do {
		z = (x + y) % p;
		x = y;
		y = z;
		++res;
	} while (x != 0 || y != 1);
	return res - 1;
}

int main() {
	for (int p = 2; p <= 200000; ++p) {
		if (p % 10000 == 0)
			std::cerr << "p = " << p << std::endl;
		std::cout << p << ": " << calc(p) << std::endl;
	}
	
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int b;
int fun(int a) {
	static int c = 3;
	cout << b << " " << a << " " << c << endl;
	return ((++a) + (++b) + (++c));
}

int main() {
	/*int a = 2;
	cout << fun(a) << endl;
	cout << fun(a) << endl;*/
	int x = -5, y = -1, z = 3, *p[3];
	p[0] = &x;
	p[1] = &y;
	p[2] = &z;
	cout << *++p[0] << endl;
}
